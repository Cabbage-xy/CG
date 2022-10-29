#include "pch.h"
#include "CG2DPolyLine.h"
#include "CGDI2DRenderContext.h"
#include "CGDI2DCamera.h"
#include "CGDI2DView.h"
CG_NAMESPACE_ENTER
IMPLEMENT_SERIAL(CG2DPolyLine, CG2DRenderable, 1)
CG2DPolyLine::CG2DPolyLine()
	: CG2DRenderable(CString("CG2DPolyLine"))
{
	mName.Format(_T("折线-%ld"), sID);
	mPoints.push_back(Vec2d(0, 0));
}
CG2DPolyLine::CG2DPolyLine(const std::vector<Vec2d>& points)
	: CG2DRenderable(CString("CG2DPolyLine")), mPoints(points)
{
	mName.Format(_T("折线-%ld"), sID);
}
CG2DPolyLine::CG2DPolyLine(const CG2DPolyLine& other)
	: CG2DRenderable(CString("CG2DPolyLine")), mPoints(other.mPoints)
{
	mName.Format(_T("折线-%ld"), sID);
}
CG2DPolyLine::~CG2DPolyLine()
{
}
//序列化
void CG2DPolyLine::Serialize(CArchive& ar)
{
	CG2DRenderable::Serialize(ar);
	if (ar.IsStoring())
	{
		for (auto v : mPoints) {
			ar << v.x() << v.y();
		}
	}
	else
	{
		for (auto v : mPoints) {
			ar >> v.x() >> v.y();
		}
	}
}
void CG2DPolyLine::Render(CGRenderContext* pRC, CGCamera* pCamera) //绘制对象，使用指定相机
{
	if (pRC == nullptr || !pRC->IsKindOf(RUNTIME_CLASS(CGDI2DRenderContext)) || pRC->getView() == nullptr)
		return;
	if (pCamera == nullptr || !pCamera->IsKindOf(RUNTIME_CLASS(CGDI2DCamera)))
		return;
#ifdef USEMEMDC
	HDC hDC = ((CGDI2DRenderContext*)pRC)->hmemDC(); //使用双缓存（内存DC）
#else
	HDC hDC = pRC->hdc(); //不使用双缓存（内存DC）
#endif
//绘制线段对象
	std::vector<Vec2i> points;
	for (auto &mp : mPoints) {
		points.push_back(pCamera->WorldtoViewPort(mp));
	}
	int lineAlgorithm = pRC->getView()->LineAlgorithm();
	if (lineAlgorithm == CGRenderContext::aLineCDC) {
		CPen pen(penStyle(), penWidth(), penColor());
		if (hDC != 0)
		{
			HPEN hOldPen = (HPEN)::SelectObject(hDC, pen.GetSafeHandle());
			for (int i = 0; i < points.size() - 1; i++) {
				::MoveToEx(hDC, points[i].x(), points[i].y(), nullptr);
				::LineTo(hDC, points[i + 1].x(), points[i + 1].y());
			}
			::SelectObject(hDC, hOldPen);
		}
		else
		{
			CClientDC dc(pRC->getView());
			CPen* pOldPen = dc.SelectObject(&pen);
			for (int i = 0; i < points.size() - 1; i++) {
				dc.MoveTo(points[i].x(), points[i].y());
				dc.LineTo(points[i + 1].x(), points[i + 1].y());
			}
			dc.SelectObject(pOldPen);
		}
	}
	else if (lineAlgorithm == CGRenderContext::aLineDDA) {
		for (int i = 0; i < points.size() - 1; i++) {
			pRC->DDALine(points[i], points[i + 1], penColor());
		}
	}
	else if (lineAlgorithm == CGRenderContext::aLineMidPoint) {
		for (int i = 0; i < points.size() - 1; i++) {
			pRC->MidPointLine(points[i], points[i + 1], penColor());
		}
	}
	else if (lineAlgorithm == CGRenderContext::aLineBresenham) {
		for (int i = 0; i < points.size() - 1; i++) {
			pRC->BresenhamLine(points[i], points[i + 1], penColor());
		}
	}

	//此处仅以绘制对象包围盒的方式显示对象被选中，也可以自行确定选中显示方式
	if (status() == CGRenderable::sSelected) //对象处于选中状态
	{
		//以包围盒绘制选中状态
		ABox2d abox = BoundingABox(); //计算包围盒，绘制包围盒
		Vec2i v1 = pCamera->WorldtoViewPort(abox.minCorner());
		Vec2i v2 = pCamera->WorldtoViewPort(abox.maxCorner());
		CPen pen(PS_DASHDOT, 1, RGB(0, 0, 255));
		if (hDC != 0)
		{
			HPEN hOldPen = (HPEN)::SelectObject(hDC, pen.GetSafeHandle());
			HBRUSH hOldBrush = (HBRUSH)::SelectObject(hDC, (HBRUSH)GetStockObject(NULL_BRUSH));
			::Rectangle(hDC, v1.x(), v1.y(), v2.x(), v2.y());
			::SelectObject(hDC, hOldPen);
			::SelectObject(hDC, hOldBrush);
		}
		else
		{
			CClientDC dc(pRC->getView()); //不使用双缓存（内存DC），直接使用ClientDC
			CPen* pOldPen = dc.SelectObject(&pen);
			CBrush* pOldBursh = (CBrush*)dc.SelectStockObject(NULL_BRUSH);
			dc.Rectangle(v1.x(), v1.y(), v2.x(), v2.y());
			dc.SelectObject(pOldPen);
			dc.SelectObject(pOldBursh);
		}
	}
}
void CG2DPolyLine::computeBoundingBox() //计算包围盒
{
	mABox.setNull(); //先清空
	for (auto &point : mPoints) {
		mABox.addPoint(point);
	}
	setBoundsDirty(false);
}
bool CG2DPolyLine::Picked(const Vec2d& p, double radius) //是否拾取到
{
	/*
	//（给定位置和范围，范围r可以根据需要设为圆半径或正方形边长的一半）
	ABox2d abox = BoundingABox();
	ABox2d sbox(p, radius);
	if (abox.intersects(sbox)) //如果点在线段包围盒内，进一步判断距离
	{
		//点到直线段的距离
		Vec2d ES = mEnd - mStart;
		Vec2d PS = p - mStart;
		Vec2d PE = p - mEnd;
		double c = ES.dot(PS);
		if (c <= 0) return PS.length();
		double d = ES.lengthSquared();
		if (c >= d) return (PE.length());
		double r = c / d;
		double px = mStart.x() + (mEnd.x() - mStart.x()) * r;
		double py = mStart.y() + (mEnd.y() - mStart.y()) * r;
		Vec2d S = Vec2d(px, py);
		double dis = (p - S).length();
		if (dis <= r)
			return true;
	}*/
	return false;
}
//二维图形对象的几何变换（重写基类的虚函数）
void CG2DPolyLine::Translate(double tx, double ty) //平移
{
	//简单变换，不使用矩阵直接运算
	for (auto& point : mPoints) {
		point.x() += tx;
		point.y() += ty;
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::Rotate(double angle, double cx, double cy) //旋转（逆时针为正，度）
{
	//使用变换矩阵实现
	Mat3d mat = Mat3d::getRotation(angle, Vec2d(cx, cy));
	for (auto& point : mPoints) {
		Vec3d p = operator*(mat, Vec3d(point));
		point = Vec2d(p.x(), p.y());
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::Scale(double sx, double sy) //缩放
{
	//关于坐标原点缩放，简单变换，不使用矩阵直接运算
	for (auto& point : mPoints) {
		point.x() *= sx;
		point.y() *= sy;
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::Scale(double sx, double sy, double cx, double cy) //缩放
{
	//关于指定点缩放，使用矩阵直接运算
	Mat3d mat = Mat3d::getScaling(Vec2d(sx, sy), Vec2d(cx, cy));
	for (auto& point : mPoints) {
		Vec3d p = operator*(mat, Vec3d(point));
		point = Vec2d(p.x(), p.y());
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::Scale(double sx, double sy, double cx, double cy, const Vec2d& xDir) //缩放
{
	//关于指定点缩放，使用矩阵直接运算
	Mat3d mat = Mat3d::getScaling(Vec2d(sx, sy), Vec2d(cx, cy), xDir);
	for (auto& point : mPoints) {
		Vec3d p = operator*(mat, Vec3d(point));
		point = Vec2d(p.x(), p.y());
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::MirrorXAxis() //关于X轴对称（二维、三维）
{
	//简单变换，不使用矩阵直接运算
	for (auto& point : mPoints) {
		point.y() = -point.y();
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::MirrorYAxis() //关于Y轴对称（二维、三维）
{
	//简单变换，不使用矩阵直接运算
	for (auto& point : mPoints) {
		point.x() = -point.x();
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::MirrorYeqPosX() //关于y=x对称（二维、三维）
{
	//简单变换，不使用矩阵直接运算
	for (auto& point : mPoints) {
		double t = point.x();
		point.x() = point.y();
		point.y() = t;
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::MirrorYeNegPX() //关于y=-x对称（二维、三维）
{
	//简单变换，不使用矩阵直接运算
	for (auto& point : mPoints) {
		double t = point.x();
		point.x() = -point.y();
		point.y() = -t;
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::MirrorOrigin() //关于原点对称（二维、三维）
{
	//简单变换，不使用矩阵直接运算
	for (auto& point : mPoints) {
		point.x() = -point.x();
		point.y() = -point.y();
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::ShearXAxis(double shx) //沿X轴错切
{
	//简单变换，不使用矩阵直接运算
	for (auto& point : mPoints) {
		point.x() = point.x() + shx * point.y();
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::ShearYAxis(double shy) //沿Y轴错切
{
	//简单变换，不使用矩阵直接运算
	for (auto& point : mPoints) {
		point.y() = point.y() + shy * point.x();
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::ShearXYAxis(double shx, double shy) //沿X、Y轴错切
{
	//使用变换矩阵实现
	Mat3d mat = Mat3d::getShear(shx, shy);
	for (auto& point : mPoints) {
		Vec3d p = operator*(mat, Vec3d(point));
		point = Vec2d(p.x(), p.y());
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::Transform(const Mat3d& mat) //几何变换（左乘给定矩阵）
{
	for (auto& point : mPoints) {
		Vec3d p = operator*(mat, Vec3d(point));
		point = Vec2d(p.x(), p.y());
	}
	setBoundsDirty(true);
}
CG_NAMESPACE_EXIT
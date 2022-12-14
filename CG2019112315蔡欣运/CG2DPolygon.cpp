#include "pch.h"
#include "CG2DPolygon.h"
#include "CGDI2DRenderContext.h"
#include "CGDI2DCamera.h"
#include "CGDI2DView.h"

CG_NAMESPACE_ENTER
IMPLEMENT_SERIAL(CG2DPolygon, CG2DRenderable, 1)
CG2DPolygon::CG2DPolygon()
	: CG2DRenderable(CString("CG2DPolygon"))
{
	mName.Format(_T("圆-%ld"), sID);
}
CG2DPolygon::CG2DPolygon(const std::vector<Vec2d> points)
	: CG2DRenderable(CString("CG2DPolygon"))
{
	mPoints = points;
	mName.Format(_T("duobianxing-%ld"), sID);
}
CG2DPolygon::CG2DPolygon(const CG2DPolygon& other)
	: CG2DRenderable(CString("CG2DPolygon")), mPoints(other.mPoints)
{
	mName.Format(_T("duobianxing-%ld"), sID);
}
CG2DPolygon::~CG2DPolygon()
{
}
//序列化
void CG2DPolygon::Serialize(CArchive& ar)
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
void CG2DPolygon::Render(CGRenderContext* pRC, CGCamera* pCamera) //绘制对象，使用指定相机
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
	int useBrush = pRC->getView()->UseBrush();
	if (useBrush == true) {//使用填充算法
		int fillAlgorithm = pRC->getView()->FillAlgorithm();
		if (fillAlgorithm == CGRenderContext::aFillCDC) {
			CPen pen(penStyle(), penWidth(), penColor());
			CBrush brush(brushColor());
			CPoint *cpoints = new CPoint[points.size()];
			for (int i = 0; i < points.size(); i++) {
				cpoints[i].x = points[i].x();
				cpoints[i].y = points[i].y();
			}
			if (hDC != 0)
			{
				HPEN hOldPen = (HPEN)::SelectObject(hDC, pen.GetSafeHandle());
				HBRUSH hOldBrush = (HBRUSH)::SelectObject(hDC, brush.GetSafeHandle());
				::Polygon(hDC, cpoints, points.size());
				::SelectObject(hDC, hOldPen);
			}
			else
			{
				CClientDC dc(pRC->getView());
				CPen* pOldPen = dc.SelectObject(&pen);
				CBrush* pOldBrush = dc.SelectObject(&brush);
				dc.Polygon(cpoints, points.size());
				dc.SelectObject(pOldPen);
			}
			delete[] cpoints;
		}
		else if (fillAlgorithm == CGRenderContext::aFillScanlinePolygon) {
			pRC->ScanLinePolygonFill(points, brushColor());
		}
	}
	else {//使用线段绘制算法
		int lineAlgorithm = pRC->getView()->LineAlgorithm();
		if (lineAlgorithm == CGRenderContext::aLineCDC) {
			CPen pen(penStyle(), penWidth(), penColor());
			if (hDC != 0)
			{
				HPEN hOldPen = (HPEN)::SelectObject(hDC, pen.GetSafeHandle());
				for (int i = 0; i < points.size(); i++) {
					int p1 = i, p2 = (i + 1) % points.size();
					::MoveToEx(hDC, points[p1].x(), points[p1].y(), nullptr);
					::LineTo(hDC, points[p2].x(), points[p2].y());
				}
				::SelectObject(hDC, hOldPen);
			}
			else
			{
				CClientDC dc(pRC->getView());
				CPen* pOldPen = dc.SelectObject(&pen);
				for (int i = 0; i < points.size(); i++) {
					int p1 = i, p2 = (i + 1) % points.size();
					dc.MoveTo(points[p1].x(), points[p1].y());
					dc.LineTo(points[p2].x(), points[p2].y());
				}
				dc.SelectObject(pOldPen);
			}
		}
		else if (lineAlgorithm == CGRenderContext::aLineDDA) {
			for (int i = 0; i < points.size(); i++) {
				int p1 = i, p2 = (i + 1) % points.size();
				pRC->DDALine(points[p1], points[p2], penColor());
			}
		}
		else if (lineAlgorithm == CGRenderContext::aLineMidPoint) {
			for (int i = 0; i < points.size(); i++) {
				int p1 = i, p2 = (i + 1) % points.size();
				pRC->MidPointLine(points[p1], points[p2], penColor());
			}

		}
		else if (lineAlgorithm == CGRenderContext::aLineBresenham) {
			for (int i = 0; i < points.size(); i++) {
				int p1 = i, p2 = (i + 1) % points.size();
				pRC->BresenhamLine(points[p1], points[p2], penColor());
			}
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
void CG2DPolygon::computeBoundingBox() //计算包围盒
{
	mABox.setNull(); //先清空
	for (auto& point : mPoints) {
		mABox.addPoint(point);
	}
	setBoundsDirty(false);
}
//二维图形对象的几何变换（重写基类的虚函数）
void CG2DPolygon::Translate(double tx, double ty) //平移
{
	//简单变换，不使用矩阵直接运算
	for (auto& point : mPoints) {
		point.x() += tx;
		point.y() += ty;
	}
	setBoundsDirty(true);
}
void CG2DPolygon::Rotate(double angle, double cx, double cy) //旋转（逆时针为正，度）
{
	//使用变换矩阵实现
	Mat3d mat = Mat3d::getRotation(angle, Vec2d(cx, cy));
	for (auto& point : mPoints) {
		Vec3d p = operator*(mat, Vec3d(point));
		point = Vec2d(p.x(), p.y());
	}
	setBoundsDirty(true);
}
void CG2DPolygon::Scale(double sx, double sy) //缩放
{
	//关于坐标原点缩放，简单变换，不使用矩阵直接运算
	for (auto& point : mPoints) {
		point.x() *= sx;
		point.y() *= sy;
	}
	setBoundsDirty(true);
}
void CG2DPolygon::Scale(double sx, double sy, double cx, double cy) //缩放
{
	//关于指定点缩放，使用矩阵直接运算
	Mat3d mat = Mat3d::getScaling(Vec2d(sx, sy), Vec2d(cx, cy));
	for (auto& point : mPoints) {
		Vec3d p = operator*(mat, Vec3d(point));
		point = Vec2d(p.x(), p.y());
	}
	setBoundsDirty(true);
}
void CG2DPolygon::Scale(double sx, double sy, double cx, double cy, const Vec2d& xDir) //缩放
{
	//关于指定点缩放，使用矩阵直接运算
	Mat3d mat = Mat3d::getScaling(Vec2d(sx, sy), Vec2d(cx, cy), xDir);
	for (auto& point : mPoints) {
		Vec3d p = operator*(mat, Vec3d(point));
		point = Vec2d(p.x(), p.y());
	}
	setBoundsDirty(true);
}
void CG2DPolygon::MirrorXAxis() //关于X轴对称（二维、三维）
{
	//简单变换，不使用矩阵直接运算
	for (auto& point : mPoints) {
		point.y() = -point.y();
	}
	setBoundsDirty(true);
}
void CG2DPolygon::MirrorYAxis() //关于Y轴对称（二维、三维）
{
	//简单变换，不使用矩阵直接运算
	for (auto& point : mPoints) {
		point.x() = -point.x();
	}
	setBoundsDirty(true);
}
void CG2DPolygon::MirrorYeqPosX() //关于y=x对称（二维、三维）
{
	//简单变换，不使用矩阵直接运算
	for (auto& point : mPoints) {
		double t = point.x();
		point.x() = point.y();
		point.y() = t;
	}
	setBoundsDirty(true);
}
void CG2DPolygon::MirrorYeNegPX() //关于y=-x对称（二维、三维）
{
	//简单变换，不使用矩阵直接运算
	for (auto& point : mPoints) {
		double t = point.x();
		point.x() = -point.y();
		point.y() = -t;
	}
	setBoundsDirty(true);
}
void CG2DPolygon::MirrorOrigin() //关于原点对称（二维、三维）
{
	//简单变换，不使用矩阵直接运算
	for (auto& point : mPoints) {
		point.x() = -point.x();
		point.y() = -point.y();
	}
	setBoundsDirty(true);
}
void CG2DPolygon::ShearXAxis(double shx) //沿X轴错切
{
	//简单变换，不使用矩阵直接运算
	for (auto& point : mPoints) {
		point.x() = point.x() + shx * point.y();
	}
	setBoundsDirty(true);
}
void CG2DPolygon::ShearYAxis(double shy) //沿Y轴错切
{
	//简单变换，不使用矩阵直接运算
	for (auto& point : mPoints) {
		point.y() = point.y() + shy * point.x();
	}
	setBoundsDirty(true);
}
void CG2DPolygon::ShearXYAxis(double shx, double shy) //沿X、Y轴错切
{
	//使用变换矩阵实现
	Mat3d mat = Mat3d::getShear(shx, shy);
	for (auto& point : mPoints) {
		Vec3d p = operator*(mat, Vec3d(point));
		point = Vec2d(p.x(), p.y());
	}
	setBoundsDirty(true);
}
void CG2DPolygon::Transform(const Mat3d& mat) //几何变换（左乘给定矩阵）
{
	for (auto& point : mPoints) {
		Vec3d p = operator*(mat, Vec3d(point));
		point = Vec2d(p.x(), p.y());
	}
	setBoundsDirty(true);
}
CG_NAMESPACE_EXIT
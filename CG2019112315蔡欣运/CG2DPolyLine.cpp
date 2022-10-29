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
	mName.Format(_T("����-%ld"), sID);
	mPoints.push_back(Vec2d(0, 0));
}
CG2DPolyLine::CG2DPolyLine(const std::vector<Vec2d>& points)
	: CG2DRenderable(CString("CG2DPolyLine")), mPoints(points)
{
	mName.Format(_T("����-%ld"), sID);
}
CG2DPolyLine::CG2DPolyLine(const CG2DPolyLine& other)
	: CG2DRenderable(CString("CG2DPolyLine")), mPoints(other.mPoints)
{
	mName.Format(_T("����-%ld"), sID);
}
CG2DPolyLine::~CG2DPolyLine()
{
}
//���л�
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
void CG2DPolyLine::Render(CGRenderContext* pRC, CGCamera* pCamera) //���ƶ���ʹ��ָ�����
{
	if (pRC == nullptr || !pRC->IsKindOf(RUNTIME_CLASS(CGDI2DRenderContext)) || pRC->getView() == nullptr)
		return;
	if (pCamera == nullptr || !pCamera->IsKindOf(RUNTIME_CLASS(CGDI2DCamera)))
		return;
#ifdef USEMEMDC
	HDC hDC = ((CGDI2DRenderContext*)pRC)->hmemDC(); //ʹ��˫���棨�ڴ�DC��
#else
	HDC hDC = pRC->hdc(); //��ʹ��˫���棨�ڴ�DC��
#endif
//�����߶ζ���
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

	//�˴����Ի��ƶ����Χ�еķ�ʽ��ʾ����ѡ�У�Ҳ��������ȷ��ѡ����ʾ��ʽ
	if (status() == CGRenderable::sSelected) //������ѡ��״̬
	{
		//�԰�Χ�л���ѡ��״̬
		ABox2d abox = BoundingABox(); //�����Χ�У����ư�Χ��
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
			CClientDC dc(pRC->getView()); //��ʹ��˫���棨�ڴ�DC����ֱ��ʹ��ClientDC
			CPen* pOldPen = dc.SelectObject(&pen);
			CBrush* pOldBursh = (CBrush*)dc.SelectStockObject(NULL_BRUSH);
			dc.Rectangle(v1.x(), v1.y(), v2.x(), v2.y());
			dc.SelectObject(pOldPen);
			dc.SelectObject(pOldBursh);
		}
	}
}
void CG2DPolyLine::computeBoundingBox() //�����Χ��
{
	mABox.setNull(); //�����
	for (auto &point : mPoints) {
		mABox.addPoint(point);
	}
	setBoundsDirty(false);
}
bool CG2DPolyLine::Picked(const Vec2d& p, double radius) //�Ƿ�ʰȡ��
{
	/*
	//������λ�úͷ�Χ����Χr���Ը�����Ҫ��ΪԲ�뾶�������α߳���һ�룩
	ABox2d abox = BoundingABox();
	ABox2d sbox(p, radius);
	if (abox.intersects(sbox)) //��������߶ΰ�Χ���ڣ���һ���жϾ���
	{
		//�㵽ֱ�߶εľ���
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
//��άͼ�ζ���ļ��α任����д������麯����
void CG2DPolyLine::Translate(double tx, double ty) //ƽ��
{
	//�򵥱任����ʹ�þ���ֱ������
	for (auto& point : mPoints) {
		point.x() += tx;
		point.y() += ty;
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::Rotate(double angle, double cx, double cy) //��ת����ʱ��Ϊ�����ȣ�
{
	//ʹ�ñ任����ʵ��
	Mat3d mat = Mat3d::getRotation(angle, Vec2d(cx, cy));
	for (auto& point : mPoints) {
		Vec3d p = operator*(mat, Vec3d(point));
		point = Vec2d(p.x(), p.y());
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::Scale(double sx, double sy) //����
{
	//��������ԭ�����ţ��򵥱任����ʹ�þ���ֱ������
	for (auto& point : mPoints) {
		point.x() *= sx;
		point.y() *= sy;
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::Scale(double sx, double sy, double cx, double cy) //����
{
	//����ָ�������ţ�ʹ�þ���ֱ������
	Mat3d mat = Mat3d::getScaling(Vec2d(sx, sy), Vec2d(cx, cy));
	for (auto& point : mPoints) {
		Vec3d p = operator*(mat, Vec3d(point));
		point = Vec2d(p.x(), p.y());
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::Scale(double sx, double sy, double cx, double cy, const Vec2d& xDir) //����
{
	//����ָ�������ţ�ʹ�þ���ֱ������
	Mat3d mat = Mat3d::getScaling(Vec2d(sx, sy), Vec2d(cx, cy), xDir);
	for (auto& point : mPoints) {
		Vec3d p = operator*(mat, Vec3d(point));
		point = Vec2d(p.x(), p.y());
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::MirrorXAxis() //����X��Գƣ���ά����ά��
{
	//�򵥱任����ʹ�þ���ֱ������
	for (auto& point : mPoints) {
		point.y() = -point.y();
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::MirrorYAxis() //����Y��Գƣ���ά����ά��
{
	//�򵥱任����ʹ�þ���ֱ������
	for (auto& point : mPoints) {
		point.x() = -point.x();
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::MirrorYeqPosX() //����y=x�Գƣ���ά����ά��
{
	//�򵥱任����ʹ�þ���ֱ������
	for (auto& point : mPoints) {
		double t = point.x();
		point.x() = point.y();
		point.y() = t;
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::MirrorYeNegPX() //����y=-x�Գƣ���ά����ά��
{
	//�򵥱任����ʹ�þ���ֱ������
	for (auto& point : mPoints) {
		double t = point.x();
		point.x() = -point.y();
		point.y() = -t;
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::MirrorOrigin() //����ԭ��Գƣ���ά����ά��
{
	//�򵥱任����ʹ�þ���ֱ������
	for (auto& point : mPoints) {
		point.x() = -point.x();
		point.y() = -point.y();
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::ShearXAxis(double shx) //��X�����
{
	//�򵥱任����ʹ�þ���ֱ������
	for (auto& point : mPoints) {
		point.x() = point.x() + shx * point.y();
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::ShearYAxis(double shy) //��Y�����
{
	//�򵥱任����ʹ�þ���ֱ������
	for (auto& point : mPoints) {
		point.y() = point.y() + shy * point.x();
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::ShearXYAxis(double shx, double shy) //��X��Y�����
{
	//ʹ�ñ任����ʵ��
	Mat3d mat = Mat3d::getShear(shx, shy);
	for (auto& point : mPoints) {
		Vec3d p = operator*(mat, Vec3d(point));
		point = Vec2d(p.x(), p.y());
	}
	setBoundsDirty(true);
}
void CG2DPolyLine::Transform(const Mat3d& mat) //���α任����˸�������
{
	for (auto& point : mPoints) {
		Vec3d p = operator*(mat, Vec3d(point));
		point = Vec2d(p.x(), p.y());
	}
	setBoundsDirty(true);
}
CG_NAMESPACE_EXIT
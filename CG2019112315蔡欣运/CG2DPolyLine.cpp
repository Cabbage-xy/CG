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

CG_NAMESPACE_EXIT
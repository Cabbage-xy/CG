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
	mName.Format(_T("Բ-%ld"), sID);
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
//���л�
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
void CG2DPolygon::Render(CGRenderContext* pRC, CGCamera* pCamera) //���ƶ���ʹ��ָ�����
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
			::MoveToEx(hDC, points.back().x(), points.back().y(), nullptr);
			::LineTo(hDC, points.front().x(), points.front().y());
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
			dc.MoveTo(points.back().x(), points.back().y());
			dc.LineTo(points.front().x(), points.front().y());
			dc.SelectObject(pOldPen);
		}
	}
	else if (lineAlgorithm == CGRenderContext::aLineDDA) {
		for (int i = 0; i < points.size() - 1; i++) {
			pRC->DDALine(points[i], points[i + 1], penColor());
		}
		pRC->DDALine(points.back(), points.front(), penColor());
	}
	else if (lineAlgorithm == CGRenderContext::aLineMidPoint) {
		for (int i = 0; i < points.size() - 1; i++) {
			pRC->MidPointLine(points[i], points[i + 1], penColor());
		}
		pRC->MidPointLine(points.back(), points.front(), penColor());

	}
	else if (lineAlgorithm == CGRenderContext::aLineBresenham) {
		for (int i = 0; i < points.size() - 1; i++) {
			pRC->BresenhamLine(points[i], points[i + 1], penColor());
		}
		pRC->BresenhamLine(points.back(), points.front(), penColor());
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
CG_NAMESPACE_EXIT
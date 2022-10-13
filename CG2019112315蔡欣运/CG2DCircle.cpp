#include "pch.h"
#include "CG2DCircle.h"
#include "CGDI2DRenderContext.h"
#include "CGDI2DCamera.h"
#include "CGDI2DView.h"

CG_NAMESPACE_ENTER
IMPLEMENT_SERIAL(CG2DCircle, CG2DRenderable, 1)
CG2DCircle::CG2DCircle()
	: CG2DRenderable(CString("CG2DCircle")), mCenter(0, 0), r(0)
{
	mName.Format(_T("圆-%ld"), sID);
}
CG2DCircle::CG2DCircle(const Vec2d& c, const double r)
	: CG2DRenderable(CString("CG2DCircle")), mCenter(c), r(r)
{
	mName.Format(_T("圆-%ld"), sID);
}
CG2DCircle::CG2DCircle(const Vec2d& m1, const Vec2d& m2)
	: CG2DRenderable(CString("圆-%ld"))
{
	mCenter.x() = (m1.x() + m2.x()) / 2;
	mCenter.y() = (m1.y() + m2.y()) / 2;
	r = (mCenter - m1).length();
	mName.Format(_T("圆-%ld"), sID);
}
CG2DCircle::CG2DCircle(const CG2DCircle& other)
	: CG2DRenderable(CString("CG2DCircle")), mCenter(other.mCenter), r(other.r)
{
	mName.Format(_T("圆-%ld"), sID);
}
CG2DCircle::~CG2DCircle()
{
}
//序列化
void CG2DCircle::Serialize(CArchive& ar)
{
	CG2DRenderable::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << mCenter.x() << mCenter.y() << r;
	}
	else
	{
		ar >> mCenter.x() >> mCenter.y() >> r;
	}
}
void CG2DCircle::Render(CGRenderContext* pRC, CGCamera* pCamera) //绘制对象，使用指定相机
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
//绘制圆对象
	int circleAlgorithm = pRC->getView()->CircleAlgorithm();
	if (circleAlgorithm == CGRenderContext::aCircleCDC) {
		CPen pen(penStyle(), penWidth(), penColor());
		Vec2i v1 = pCamera->WorldtoViewPort(Vec2d(mCenter.x() - r, mCenter.y() - r));
		Vec2i v2 = pCamera->WorldtoViewPort(Vec2d(mCenter.x() + r, mCenter.y() + r));
		if (hDC != 0)
		{
			HPEN hOldPen = (HPEN)::SelectObject(hDC, pen.GetSafeHandle());
			::Ellipse(hDC, v1.x(), v1.y(), v2.x(), v2.y());
			::SelectObject(hDC, hOldPen);
		}
		else
		{
			CClientDC dc(pRC->getView());
			CPen* pOldPen = dc.SelectObject(&pen);
			dc.Ellipse(v1.x(), v1.y(), v2.x(), v2.y());
			dc.SelectObject(pOldPen);
		}
	}
	else if (circleAlgorithm == CGRenderContext::aCrcleMidPoint) {
		Vec2i center = pCamera->WorldtoViewPort(mCenter);
		pRC->MidPointCircle(center, (int)r, penColor());
	}
	else if (circleAlgorithm == CGRenderContext::aCircleBresenham) {
		Vec2i center = pCamera->WorldtoViewPort(mCenter);
		pRC->BresenhamCircle(center, (int)r, penColor());
	}
}
CG_NAMESPACE_EXIT
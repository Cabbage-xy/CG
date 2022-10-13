#include "pch.h"
#include "CG2DEllipse.h"
#include "CGDI2DRenderContext.h"
#include "CGDI2DCamera.h"
#include "CGDI2DView.h"

CG_NAMESPACE_ENTER
IMPLEMENT_SERIAL(CG2DEllipse, CG2DRenderable, 1)
CG2DEllipse::CG2DEllipse()
	: CG2DRenderable(CString("CG2DEllipse")), mLeftTop(0, 0), mRightBottom(0, 0)
{
	mName.Format(_T("椭圆-%ld"), sID);
}
CG2DEllipse::CG2DEllipse(const Vec2d& m1, const Vec2d& m2)
	: CG2DRenderable(CString("CG2DEllipse")), mLeftTop(m1), mRightBottom(m2)
{
	mName.Format(_T("椭圆-%ld"), sID);
}
CG2DEllipse::CG2DEllipse(const CG2DEllipse& other)
	: CG2DRenderable(CString("CG2DEllipse")), mLeftTop(other.mLeftTop), mRightBottom(other.mLeftTop)
{
	mName.Format(_T("椭圆-%ld"), sID);
}
CG2DEllipse::~CG2DEllipse()
{
}
//序列化
void CG2DEllipse::Serialize(CArchive& ar)
{
	CG2DRenderable::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << mLeftTop.x() << mLeftTop.y() << mRightBottom.x() << mRightBottom.y();
	}
	else
	{
		ar >> mLeftTop.x() >> mLeftTop.y() >> mRightBottom.x() >> mRightBottom.y();
	}
}
void CG2DEllipse::Render(CGRenderContext* pRC, CGCamera* pCamera) //绘制对象，使用指定相机
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
	Vec2i v1 = pCamera->WorldtoViewPort(mLeftTop);
	Vec2i v2 = pCamera->WorldtoViewPort(mRightBottom);
	CPen pen(penStyle(), penWidth(), penColor());
	if (hDC != 0)
	{
		HPEN hOldPen = (HPEN)::SelectObject(hDC, pen.GetSafeHandle());
		::Ellipse(hDC, mLeftTop.x(), mLeftTop.y(), mRightBottom.x(), mRightBottom.y());
		::SelectObject(hDC, hOldPen);
	}
	else
	{
		CClientDC dc(pRC->getView());
		CPen* pOldPen = dc.SelectObject(&pen);
		dc.Ellipse(mLeftTop.x(), mLeftTop.y(), mRightBottom.x(), mRightBottom.y());
		dc.SelectObject(pOldPen);
	}
}
CG_NAMESPACE_EXIT
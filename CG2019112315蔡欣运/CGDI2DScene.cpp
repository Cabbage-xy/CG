#include "pch.h"
#include "CGDI2DScene.h"
#include "CG2DRenderable.h"
#include "CGDI2DCamera.h"
#include "CGDI2DRenderContext.h"
#include "CGDI2DView.h"
CG_NAMESPACE_ENTER
IMPLEMENT_SERIAL(CGDI2DScene, CGScene, 1)
CGDI2DScene::CGDI2DScene()
{
}
CGDI2DScene::~CGDI2DScene()
{
}
//序列化
void CGDI2DScene::Serialize(CArchive& ar)
{
	CGScene::Serialize(ar);
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}
//渲染场景到指定客户区（依赖CGDI2DMfcView）
bool CGDI2DScene::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
	if (pRC == nullptr || !pRC->IsKindOf(RUNTIME_CLASS(CGDI2DRenderContext)) || pRC->getView() == nullptr)
		return false;
	if (pCamera == nullptr || !pCamera->IsKindOf(RUNTIME_CLASS(CGDI2DCamera)))
		return false;
	int i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		CGRenderable* r = mRenderables.GetAt(i);
		if (r != nullptr)
		{
			r->Render(pRC, pCamera);
		}
		i++;
	}
	//绘制世界坐标系测试（给定范围）
	Vec2d wxs(-2000, 0), wxe(2000, 0), wys(0, -2000), wye(0, 2000);
	Vec2i vxs = pCamera->WorldtoViewPort(wxs);
	Vec2i vxe = pCamera->WorldtoViewPort(wxe);
	Vec2i vys = pCamera->WorldtoViewPort(wys);
	Vec2i vye = pCamera->WorldtoViewPort(wye);
#ifdef USEMEMDC
	HDC hDC = ((CGDI2DRenderContext*)pRC)->hmemDC(); //使用双缓存（内存DC）
#else
	HDC hDC = pRC->hdc(); //不使用双缓存（内存DC）
#endif
	CPen penr(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN hOldPen = (HPEN)::SelectObject(hDC, penr.GetSafeHandle());
	::MoveToEx(hDC, vxs.x(), vxs.y(), nullptr);
	::LineTo(hDC, vxe.x(), vxe.y());
	::SelectObject(hDC, hOldPen);
	CPen penb(PS_SOLID, 1, RGB(0, 0, 255));
	hOldPen = (HPEN)::SelectObject(hDC, penb.GetSafeHandle());
	::MoveToEx(hDC, vys.x(), vys.y(), nullptr);
	::LineTo(hDC, vye.x(), vye.y());
	::SelectObject(hDC, hOldPen);
#ifdef USEMEMDC
	((CGDI2DRenderContext*)pRC)->SwapBackBuffer(); //交换缓存
#endif
	return true;
}
ABox2d CGDI2DScene::BoundingABox()
{
	ABox2d box;
	int i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		CGRenderable* r = mRenderables.GetAt(i);
		if (r != nullptr)
		{
			box.extend(((CG2DRenderable*)r)->BoundingABox());
		}
		i++;
	}
	return box;
}
CG_NAMESPACE_EXIT

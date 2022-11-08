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
	//测试裁剪用
	int i = 0, cnt = mClipResult.GetSize();
	if (cnt > 0) //如果裁剪结果集不为空，则绘制裁剪结果集中的对象。
	{
		while (i < cnt)
		{
			CGRenderable* r = mClipResult.GetAt(i);
			if (r != nullptr)
			{
				r->Render(pRC, pCamera);
			}
			i++;
		}
	}
	else
	{
		cnt = mRenderables.GetSize();
		while (i < cnt)
		{
			CGRenderable* r = mRenderables.GetAt(i);
			if (r != nullptr)
			{
				r->Render(pRC, pCamera);
			}
			i++;
		}
	}
	//依次访问容器中的图形对象，调用其绘制函数，实现绘制
	//int i = 0, cnt = mRenderables.GetSize();
	//while (i < cnt)
	//{
	//	CGRenderable* r = mRenderables.GetAt(i);
	//	if (r != nullptr)
	//	{
	//		r->Render(pRC, pCamera);
	//	}
	//	i++;
	//}
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
//给定裁剪窗口（矩形范围）左下右上进行采集，裁剪结果不为空时返回true。
bool CGDI2DScene::Clip(double xl, double yb, double xr, double yt, CGCamera* pCamera)
{
	//先删除裁剪结果集中的对象并清空裁剪结果集
	int i = 0, cnt = mClipResult.GetSize();
	while (i < cnt)
	{
		if (mClipResult.GetAt(i))
			delete mClipResult.GetAt(i); //删除前次的裁剪结果。
		i++;
	}
	mClipResult.RemoveAll();
	CTypedPtrArray<CObArray, CGRenderable*> temp; //图形对象的裁剪结果
	bool flag = false; //场景裁剪是否有结果，
	i = 0;
	cnt = mRenderables.GetSize();
	while (i < cnt) //依次取出场景中的对象，裁剪，裁剪有结果则加入裁剪结果集
	{
		CGRenderable* r = mRenderables.GetAt(i);
		if (r != nullptr)
		{
			if (r->Cliped(xl, yb, xr, yt, pCamera, temp)) //如果该图形对象裁剪有结果
			{
				flag = true;
				mClipResult.Append(temp); //加入到场景的裁剪结果集
				temp.RemoveAll(); //清空，用于存放下一个图形对象的裁剪
			}
		}
		i++;
	}
	return flag;
}
CG_NAMESPACE_EXIT

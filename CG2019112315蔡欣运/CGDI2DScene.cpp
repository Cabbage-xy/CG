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
//���л�
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
//��Ⱦ������ָ���ͻ���������CGDI2DMfcView��
bool CGDI2DScene::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
	if (pRC == nullptr || !pRC->IsKindOf(RUNTIME_CLASS(CGDI2DRenderContext)) || pRC->getView() == nullptr)
		return false;
	if (pCamera == nullptr || !pCamera->IsKindOf(RUNTIME_CLASS(CGDI2DCamera)))
		return false;
	//���Բü���
	int i = 0, cnt = mClipResult.GetSize();
	if (cnt > 0) //����ü��������Ϊ�գ�����Ʋü�������еĶ���
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
	//���η��������е�ͼ�ζ��󣬵�������ƺ�����ʵ�ֻ���
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
	//������������ϵ���ԣ�������Χ��
	Vec2d wxs(-2000, 0), wxe(2000, 0), wys(0, -2000), wye(0, 2000);
	Vec2i vxs = pCamera->WorldtoViewPort(wxs);
	Vec2i vxe = pCamera->WorldtoViewPort(wxe);
	Vec2i vys = pCamera->WorldtoViewPort(wys);
	Vec2i vye = pCamera->WorldtoViewPort(wye);
#ifdef USEMEMDC
	HDC hDC = ((CGDI2DRenderContext*)pRC)->hmemDC(); //ʹ��˫���棨�ڴ�DC��
#else
	HDC hDC = pRC->hdc(); //��ʹ��˫���棨�ڴ�DC��
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
	((CGDI2DRenderContext*)pRC)->SwapBackBuffer(); //��������
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
//�����ü����ڣ����η�Χ���������Ͻ��вɼ����ü������Ϊ��ʱ����true��
bool CGDI2DScene::Clip(double xl, double yb, double xr, double yt, CGCamera* pCamera)
{
	//��ɾ���ü�������еĶ�����ղü������
	int i = 0, cnt = mClipResult.GetSize();
	while (i < cnt)
	{
		if (mClipResult.GetAt(i))
			delete mClipResult.GetAt(i); //ɾ��ǰ�εĲü������
		i++;
	}
	mClipResult.RemoveAll();
	CTypedPtrArray<CObArray, CGRenderable*> temp; //ͼ�ζ���Ĳü����
	bool flag = false; //�����ü��Ƿ��н����
	i = 0;
	cnt = mRenderables.GetSize();
	while (i < cnt) //����ȡ�������еĶ��󣬲ü����ü��н�������ü������
	{
		CGRenderable* r = mRenderables.GetAt(i);
		if (r != nullptr)
		{
			if (r->Cliped(xl, yb, xr, yt, pCamera, temp)) //�����ͼ�ζ���ü��н��
			{
				flag = true;
				mClipResult.Append(temp); //���뵽�����Ĳü������
				temp.RemoveAll(); //��գ����ڴ����һ��ͼ�ζ���Ĳü�
			}
		}
		i++;
	}
	return flag;
}
CG_NAMESPACE_EXIT

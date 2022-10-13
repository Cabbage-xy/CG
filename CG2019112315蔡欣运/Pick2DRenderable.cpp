#include "pch.h"
#include "Pick2DRenderable.h"
#include "CGDI2DView.h"
#include "CGRenderContext.h"
CG_NAMESPACE_ENTER
Pick2DRenderable::Pick2DRenderable(CGView* pview/* = nullptr*/)
	:UIEventListener(pview)
{
	mStep = 0;
}
Pick2DRenderable::~Pick2DRenderable()
{
}
int Pick2DRenderable::GetType() //��������
{
	return cmd2dPickRenderable; //�ǳ���Ҫ��Ҫ�붨���ö��ֵһ��
}
int Pick2DRenderable::OnLButtonDown(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr || mView->GetRenderContext() == nullptr)
		return -1;
	mStep++; //ÿ�ε���������ʱ�������������һ
	if (mStep == 1)
	{
		Vec2d p = mView->ViewPortToWorld(pos);
		if (nFlags & MK_CONTROL) //�ٶ���סCtrl��������������ʵ�ֶ�ѡ
			mView->AppendPicked(p, 5); //�ٶ�pick�뾶5����Ҫ��������
		else
			mView->UpdatePicked(p, 5);
		mStep = 0;
	}
	return 0;
}
int Pick2DRenderable::OnMouseMove(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr)
		return -1;
	if (mStep == 0)
	{
		mView->Prompt(_T("�����ͼ�ζ���"));
	}
		return 0;
}
int Pick2DRenderable::Cancel()
{
	if (mView == nullptr)
		return -1;
	mStep = 0;
	mView->Prompt(_T("���ʰȡͼ�ζ������"));
	return 0;
}
CG_NAMESPACE_EXIT
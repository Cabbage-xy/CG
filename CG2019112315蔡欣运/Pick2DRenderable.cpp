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
int Pick2DRenderable::GetType() //命令类型
{
	return cmd2dPickRenderable; //非常重要，要与定义的枚举值一致
}
int Pick2DRenderable::OnLButtonDown(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr || mView->GetRenderContext() == nullptr)
		return -1;
	mStep++; //每次单击鼠标左键时操作步骤计数加一
	if (mStep == 1)
	{
		Vec2d p = mView->ViewPortToWorld(pos);
		if (nFlags & MK_CONTROL) //假定按住Ctrl键并单击鼠标左键实现多选
			mView->AppendPicked(p, 5); //假定pick半径5，需要单独定义
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
		mView->Prompt(_T("鼠标点击图形对象"));
	}
		return 0;
}
int Pick2DRenderable::Cancel()
{
	if (mView == nullptr)
		return -1;
	mStep = 0;
	mView->Prompt(_T("鼠标拾取图形对象就绪"));
	return 0;
}
CG_NAMESPACE_EXIT
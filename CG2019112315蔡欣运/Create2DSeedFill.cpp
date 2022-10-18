#include "pch.h"
#include "Create2DSeedFill.h"
#include "CGDI2DView.h"
#include "CGRenderContext.h"
CG_NAMESPACE_ENTER
int Create2DSeedFill::OnLButtonDown(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr || mView->GetRenderContext() == nullptr)
		return -1;
	mStep++; //每次单击鼠标左键时操作步骤计数加一
	if (mStep == 1) //第一次单击鼠标左键，记录种子点
	{
		int algrithm = mView->SeedAlgorithm();
		if (algrithm == CGRenderContext::aFillSeedBound4)
			mView->GetRenderContext()->BoundFill4(pos.x(), pos.y(), mView->BoundColor(),
				mView->BrushColor());
		else if (algrithm == CGRenderContext::aFillSeedBound8)
			mView->GetRenderContext()->BoundFill8(pos.x(), pos.y(), mView->BoundColor(),
				mView->BrushColor());
		else if (algrithm == CGRenderContext::aFillSeedFlood4)
			mView->GetRenderContext()->FloodFill4(pos.x(), pos.y(), mView->BoundColor(),
				mView->BrushColor());
		else if (algrithm == CGRenderContext::aFillSeedFlood8)
			mView->GetRenderContext()->FloodFill8(pos.x(), pos.y(), mView->BoundColor(),
				mView->BrushColor());
		else //根据需要补充
		{
		}
		mStep = 0; //设为0可重新开始绘制圆
		mView->Prompt(_T("选择种子点"));
	}
	return 0;
}
CG_NAMESPACE_EXIT
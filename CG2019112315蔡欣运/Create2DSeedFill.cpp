#include "pch.h"
#include "Create2DSeedFill.h"
#include "CGDI2DView.h"
#include "CGRenderContext.h"
#include "CGDI2DRenderContext.h"
#define USEMEMDC
CG_NAMESPACE_ENTER
Create2DSeedFill::Create2DSeedFill(CGView* pview) 
	:UIEventListener(pview), mPoint(0, 0)
{
}
Create2DSeedFill::~Create2DSeedFill()
{
}
int Create2DSeedFill::GetType() //命令类型
{
	return cmd2dSeedFill;
}
int Create2DSeedFill::OnLButtonDown(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr || mView->GetRenderContext() == nullptr)
		return -1;
	mStep++; //每次单击鼠标左键时操作步骤计数加一
	if (mStep == 1) //第一次单击鼠标左键，记录种子点
	{
		int algrithm = mView->SeedAlgorithm();
		if (algrithm == CGRenderContext::aFillSeedCDC) {
			//CPen pen(mView->PenStyle(), mView->PenWidth(), mView->BrushColor());
			CBrush brush(mView->BrushColor());
#ifdef USEMEMDC
			HDC hDC = ((CGDI2DRenderContext*)(mView->GetRenderContext()))->hmemDC(); //使用双缓存（内存DC）
#else
			HDC hDC = mView->GetRenderContext()->hdc(); //不使用双缓存（内存DC）
#endif
			if (hDC != 0)
			{
				HBRUSH hOldBrush = (HBRUSH)::SelectObject(hDC, brush.GetSafeHandle());
				::FloodFill(hDC, pos.x(), pos.y(), mView->BoundColor());
				::SelectObject(hDC, hOldBrush);
			}
			else
			{
				CClientDC dc(mView);
				CBrush* pOldBrush = dc.SelectObject(&brush);
				dc.FloodFill(pos.x(), pos.y(), mView->BoundColor());
				dc.SelectObject(pOldBrush);
			}
		}
		else if (algrithm == CGRenderContext::aFillSeedBound4)
			mView->GetRenderContext()->BoundFill4(pos.x(), pos.y(), mView->BoundColor(),
				mView->BrushColor());
		else if (algrithm == CGRenderContext::aFillSeedBound8)
			mView->GetRenderContext()->BoundFill8(pos.x(), pos.y(), mView->BoundColor(),
				mView->BrushColor());
		else if (algrithm == CGRenderContext::aFillSeedFlood4)
			mView->GetRenderContext()->FloodFill4(pos.x(), pos.y(), mView->FloodColor(),
				mView->BrushColor());
		else if (algrithm == CGRenderContext::aFillSeedFlood8)
			mView->GetRenderContext()->FloodFill8(pos.x(), pos.y(), mView->FloodColor(),
				mView->BrushColor());
		else //根据需要补充
		{
		}
#ifdef USEMEMDC
		((CGDI2DRenderContext*)(mView->GetRenderContext()))->SwapBackBuffer();
#endif
		mStep = 0; //设为0可重新开始绘制圆
		//mView->Invalidate();
		//mView->UpdateWindow();
		mView->Prompt(_T("选择种子点"));
	}
	return 0;
}
int Create2DSeedFill::Cancel() {
	if (mView == nullptr)
		return -1;
	mStep = 0;
	mView->Prompt(_T("就绪"));
	return 0;
}
CG_NAMESPACE_EXIT
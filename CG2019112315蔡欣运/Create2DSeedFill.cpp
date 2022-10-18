#include "pch.h"
#include "Create2DSeedFill.h"
#include "CGDI2DView.h"
#include "CGRenderContext.h"
CG_NAMESPACE_ENTER
int Create2DSeedFill::OnLButtonDown(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr || mView->GetRenderContext() == nullptr)
		return -1;
	mStep++; //ÿ�ε���������ʱ�������������һ
	if (mStep == 1) //��һ�ε�������������¼���ӵ�
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
		else //������Ҫ����
		{
		}
		mStep = 0; //��Ϊ0�����¿�ʼ����Բ
		mView->Prompt(_T("ѡ�����ӵ�"));
	}
	return 0;
}
CG_NAMESPACE_EXIT
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
int Create2DSeedFill::GetType() //��������
{
	return cmd2dSeedFill;
}
int Create2DSeedFill::OnLButtonDown(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr || mView->GetRenderContext() == nullptr)
		return -1;
	mStep++; //ÿ�ε���������ʱ�������������һ
	if (mStep == 1) //��һ�ε�������������¼���ӵ�
	{
		int algrithm = mView->SeedAlgorithm();
		if (algrithm == CGRenderContext::aFillSeedCDC) {
			//CPen pen(mView->PenStyle(), mView->PenWidth(), mView->BrushColor());
			CBrush brush(mView->BrushColor());
#ifdef USEMEMDC
			HDC hDC = ((CGDI2DRenderContext*)(mView->GetRenderContext()))->hmemDC(); //ʹ��˫���棨�ڴ�DC��
#else
			HDC hDC = mView->GetRenderContext()->hdc(); //��ʹ��˫���棨�ڴ�DC��
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
		else //������Ҫ����
		{
		}
#ifdef USEMEMDC
		((CGDI2DRenderContext*)(mView->GetRenderContext()))->SwapBackBuffer();
#endif
		mStep = 0; //��Ϊ0�����¿�ʼ����Բ
		//mView->Invalidate();
		//mView->UpdateWindow();
		mView->Prompt(_T("ѡ�����ӵ�"));
	}
	return 0;
}
int Create2DSeedFill::Cancel() {
	if (mView == nullptr)
		return -1;
	mStep = 0;
	mView->Prompt(_T("����"));
	return 0;
}
CG_NAMESPACE_EXIT
#include "pch.h"
#include "CGDI2DView.h"
#include "CGDI2DRenderContext.h"
CG_NAMESPACE_ENTER
IMPLEMENT_DYNCREATE(CGDI2DView, CGView)
CGDI2DView::CGDI2DView()
{
}
CGDI2DView::~CGDI2DView()
{
	if (mRenderContext != nullptr)
	{
		delete mRenderContext;
		mRenderContext = nullptr;
	}
}
void CGDI2DView::OnInitialUpdate()
{
	CGView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
	mRenderContext = new CGDI2DRenderContext(this); //�������ƻ���
}
CG_NAMESPACE_EXIT
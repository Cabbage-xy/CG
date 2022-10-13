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
	// TODO: 在此添加专用代码和/或调用基类
	mRenderContext = new CGDI2DRenderContext(this); //创建绘制环境
}
CG_NAMESPACE_EXIT
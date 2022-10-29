#include "pch.h"
#include "TransformScale2DRenderable.h"
#include "CGDI2DView.h"
#include "CInputDialog1.h"

CG_NAMESPACE_ENTER
TransformScale2DRenderable::TransformScale2DRenderable(CGView* pview/* = nullptr*/)
	:UIEventListener(pview), mCenter(0, 0)
{
	mView->Prompt(_T("点击选择旋转中心点"));
}
TransformScale2DRenderable::~TransformScale2DRenderable()
{
}
int TransformScale2DRenderable::GetType() //命令类型
{
	return cmd2dScaleRenderable;
}

int TransformScale2DRenderable::OnLButtonUp(UINT nFlags, const Pos2i& pos) {
	//获取中心点
	Vec2d center = mView->ViewPortToWorld(pos);
	CInputDialog1 dlg;
	dlg.mTitle = _T("请输入x方向缩放比例"); //根据需要设置对话框标题
	dlg.mValue1 = _T("1");
	INT_PTR isDlg1OK = dlg.DoModal() == IDOK;
	if (!isDlg1OK) return 0;
	double sx = _ttof(dlg.mValue1);
	dlg.mTitle = _T("请输入y方向缩放比例");
	INT_PTR isDlg2OK = dlg.DoModal() == IDOK;
	if (!isDlg2OK) return 0;
	double sy = _ttof(dlg.mValue1);

	mView->Scale(sx, sy, center.x(), center.y());

	mView->Prompt(_T("点击选择缩放中心点"));
	return 0;
}

int TransformScale2DRenderable::Cancel()
{
	if (mView == nullptr)
		return -1;
	//mStep = 0;
	mView->Prompt(_T("就绪"));
	return 0;
}
CG_NAMESPACE_EXIT
#include "pch.h"
#include "TransformRotate2DRenderable.h"
#include "CGDI2DView.h"
#include "CInputDialog1.h"

CG_NAMESPACE_ENTER
TransformRotate2DRenderable::TransformRotate2DRenderable(CGView* pview/* = nullptr*/)
	:UIEventListener(pview), mCenter(0, 0)
{
	mView->Prompt(_T("点击选择旋转中心点"));
}
TransformRotate2DRenderable::~TransformRotate2DRenderable()
{
}
int TransformRotate2DRenderable::GetType() //命令类型
{
	return cmd2dRotateRenderable;
}

int TransformRotate2DRenderable::OnLButtonUp(UINT nFlags, const Pos2i& pos) {
	//获取中心点
	Vec2d center = mView->ViewPortToWorld(pos);
	CInputDialog1 dlg;
	dlg.mTitle = _T("请输入旋转角度(逆时针为正，顺时针为负)"); //根据需要设置对话框标题
	if (dlg.DoModal() == IDOK) //对话框中点击了【确定】按钮，取回输入的数据
	{ 
		//根据实际需要使用输入的数据
		//假如输入的是数值，则将字符串转换为数值
		double degrees = _ttof(dlg.mValue1);
		mView->Rotate(degrees, center.x(), center.y());
	}
	//mView->Invalidate();
	//mView->UpdateWindow();
	mView->Prompt(_T("点击选择旋转中心点"));
	return 0;
}

int TransformRotate2DRenderable::Cancel()
{
	if (mView == nullptr)
		return -1;
	//mStep = 0;
	mView->Prompt(_T("就绪"));
	return 0;
}
CG_NAMESPACE_EXIT
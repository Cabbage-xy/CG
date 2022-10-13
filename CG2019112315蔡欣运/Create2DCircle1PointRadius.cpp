#include "pch.h"
#include "Create2DCircle1PointRadius.h"
#include "CGDI2DView.h"
#include "CG2DCircle.h"
#include "CInputDialog1.h"
CG_NAMESPACE_ENTER
Create2DCircle1PointRadius::Create2DCircle1PointRadius(CGView* pview/* = nullptr*/)
	:UIEventListener(pview), mCenter(0, 0)
{
	mStep = 0;
}
Create2DCircle1PointRadius::~Create2DCircle1PointRadius()
{
}
int Create2DCircle1PointRadius::GetType() //命令类型
{
	return cmd2dCircle1PointRadius;
}
int Create2DCircle1PointRadius::OnLButtonDown(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr)
		return -1;
	mCenter = pos;
	CInputDialog1 dlg;
	dlg.mTitle = _T("请输入半径长度"); //根据需要设置对话框标题
	if (dlg.DoModal() == IDOK) //对话框中点击了【确定】按钮，取回输入的数据
	{ //根据实际需要使用输入的数据
	//假如输入的是数值，则将字符串转换为数值
		double radius = _ttof(dlg.mValue1);
		//
		//此处只显示输入的数据
		//AfxMessageBox(dlg.mValue1);
		Vec2d center = mView->ViewPortToWorld(mCenter);
		CG2DCircle* pCircle = new CG2DCircle(center, radius);
		pCircle->setPenColor(mView->PenColor()); //多态
		pCircle->setPenWidth(mView->PenWidth());
		pCircle->setPenStyle(mView->PenStyle());
		mView->addRenderable(pCircle); //创建成功，添加到场景
		mView->Invalidate();
		mView->UpdateWindow();
	}
	mView->Prompt(_T("请单机输入圆心位置"));
	return 0;
}

int Create2DCircle1PointRadius::OnMouseMove(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr)
		return -1;
	mCenter = pos;
	mView->Prompt(_T("请单机输入圆心位置"));
	return 0;
}
int Create2DCircle1PointRadius::Cancel()
{
	if (mView == nullptr)
		return -1;
	mView->Prompt(_T("就绪"));
	return 0;
}
CG_NAMESPACE_EXIT
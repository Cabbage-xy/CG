#include "pch.h"
#include "Create2DCircle2PointDiameter.h"
#include "CGDI2DView.h"
#include "CG2DCircle.h"
#include "CInputDialog1.h"
CG_NAMESPACE_ENTER
Create2DCircle2PointDiameter::Create2DCircle2PointDiameter(CGView* pview/* = nullptr*/)
	:UIEventListener(pview), mStart(0, 0), mEnd(0, 0)
{
	mStep = 0;
}
Create2DCircle2PointDiameter::~Create2DCircle2PointDiameter()
{
}
int Create2DCircle2PointDiameter::GetType() //命令类型
{
	return cmd2dCircle2PointDiameter;
}
int Create2DCircle2PointDiameter::OnLButtonDown(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr)
		return -1;
	mStep++;
	if (mStep == 1) {
		mStart = mEnd = pos;
		mView->Prompt(_T("请单机输入直径终点")); //通过处理事件的View显示到状态栏
	}
	else if (mStep == 2) {
		//擦除最后橡皮线
		Pos2i radius = (mEnd - mStart) / 2;
		Pos2i center = (mEnd + mStart) / 2;
		Pos2i p1(center.x() - radius.length(), center.y() - radius.length());
		Pos2i p2(center.x() + radius.length(), center.y() + radius.length());
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		dc.SetROP2(R2_NOT);
		dc.Ellipse(p1.x(), p1.y(), p2.x(), p2.y());
		dc.SelectObject(pOldPen);
		//创建圆对象
		Vec2d start = mView->ViewPortToWorld(mStart);
		Vec2d end = mView->ViewPortToWorld(mEnd);
		CG2DCircle* pCircle = new CG2DCircle(start, end);
		pCircle->setPenColor(mView->PenColor()); //多态
		pCircle->setPenWidth(mView->PenWidth());
		pCircle->setPenStyle(mView->PenStyle());
		mView->addRenderable(pCircle); //创建成功，添加到场景
		mView->Invalidate();
		mView->UpdateWindow();
		mStep = 0;
		mView->Prompt(_T("请单机输入直径起点"));
	}
	return 0;
}

int Create2DCircle2PointDiameter::OnMouseMove(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr)
		return -1;
	if (mStep < 1) {
		mView->Prompt(_T("请单机输入直径起点"));
	}
	else if (mStep == 1) {
		//计算橡皮筋线绘制相关参数
		Pos2i prePos, curPos;
		prePos = mEnd;
		Pos2i preRadius = (prePos - mStart) / 2;
		Pos2i preCenter = (prePos + mStart) / 2;
		Pos2i preP1(preCenter.x() - preRadius.length(), preCenter.y() - preRadius.length());
		Pos2i preP2(preCenter.x() + preRadius.length(), preCenter.y() + preRadius.length());
		curPos = pos;
		Pos2i curRadius = (curPos - mStart) / 2;
		Pos2i curCenter = (curPos + mStart) / 2;
		Pos2i curP1(curCenter.x() - curRadius.length(), curCenter.y() - curRadius.length());
		Pos2i curP2(curCenter.x() + curRadius.length(), curCenter.y() + curRadius.length());
		//绘制新橡皮线时先擦除上次的橡皮线
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		dc.SetROP2(R2_NOT); //反色模式
		dc.SelectStockObject(NULL_BRUSH);
		dc.Ellipse(preP1.x(), preP1.y(), preP2.x(), preP2.y());
		//绘制新的橡皮线
		dc.Ellipse(curP1.x(), curP1.y(), curP2.x(), curP2.y());
		dc.SelectObject(pOldPen);
		mEnd = curPos; //记录最新位置，作为终点
	}
	return 0;
}
int Create2DCircle2PointDiameter::Cancel()
{
	if (mView == nullptr)
		return -1;
	mStep = 0;
	mView->Prompt(_T("就绪"));
	return 0;
}
CG_NAMESPACE_EXIT
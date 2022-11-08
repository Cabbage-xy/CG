#include "pch.h"
#include "RectClip2D.h"
#include "CGDI2DView.h"
CG_NAMESPACE_ENTER
RectClip2D::RectClip2D(CGView* pview/* = nullptr*/)
	:UIEventListener(pview), mStart(0, 0), mEnd(0, 0)
{
	mStep = 0;
}
RectClip2D::~RectClip2D()
{
}
int RectClip2D::GetType() //命令类型
{
	return cmd2dRectClip;
}

int RectClip2D::OnLButtonDown(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr)
		return -1;
	mStep++; //每次单击鼠标左键时操作步骤计数加一
	if (mStep == 1) //第一次单击鼠标左键，记录起点
	{
		mStart = mEnd = pos;
		mView->Prompt(_T("请单击输入矩形框另一点")); //通过处理事件的View显示到状态栏
	}
	else if (mStep == 2)
	{
		//擦除最后橡皮线
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		dc.SetROP2(R2_NOT);
		dc.Rectangle(mStart.x(), mStart.y(), mEnd.x(), mEnd.y());
		dc.SelectObject(pOldPen);

		mEnd = pos;

		//获取起点、终点对应的场景坐标
		Vec2d start = mView->ViewPortToWorld(mStart);
		Vec2d end = mView->ViewPortToWorld(mEnd);
		double xl, xr, yb, yt;
		if (start.x() > end.x()) {
			xl = end.x();
			xr = start.x();
		}
		else {
			xl = start.x();
			xr = end.x();
		}
		if (start.y() > end.y()) {
			yt = start.y();
			yb = end.y();
		}
		else {
			yt = end.y();
			yb = start.y();
		}
		mView->Clip(xl, yb, xr, yt);
		mStep = 0; //设为0可重写开始绘制线段
		mView->Prompt(_T("请单击输入矩形框一点"));
	}
	else
	{
	}
	return 0;
}
int RectClip2D::OnMouseMove(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr)
		return -1;
	if (mStep == 0)
	{
		mView->Prompt(_T("请单击输入矩形框一点"));
	}
	else if (mStep == 1) //已经输入了起点后，当前鼠标移动的位置与起点形成橡皮线
	{
		Pos2i prePos, curPos;
		prePos = mEnd;
		curPos = pos;
		//绘制新橡皮线时先擦除上次的橡皮线
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		dc.SetROP2(R2_NOT); //反色模式
		dc.Rectangle(mStart.x(), mStart.y(), prePos.x(), prePos.y());
		//绘制新的橡皮线
		dc.Rectangle(mStart.x(), mStart.y(), curPos.x(), curPos.y());
		dc.SelectObject(pOldPen);
		mEnd = curPos; //记录最新位置，作为终点
	}
	return 0;
}

int RectClip2D::Cancel()
{
	if (mView == nullptr)
		return -1;
	if (mStep == 1) //如果已经单击左键一次，则结束操作前删除橡皮线
	{
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		dc.SetROP2(R2_NOT);
		dc.Rectangle(mStart.x(), mStart.y(), mEnd.x(), mEnd.y());
		dc.SelectObject(pOldPen);
	}
	mStep = 0;
	mView->Prompt(_T("就绪"));
	return 0;
}
CG_NAMESPACE_EXIT
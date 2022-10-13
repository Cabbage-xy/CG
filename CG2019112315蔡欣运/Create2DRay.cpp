#include "pch.h"
#include "Create2DRay.h"
#include "CGDI2DView.h"
#include "CG2DRay.h"
CG_NAMESPACE_ENTER
Create2DRay::Create2DRay(CGView* pview/* = nullptr*/)
	:UIEventListener(pview), mStart(0, 0), mEnd(0, 0)
{
	mStep = 0;
}
Create2DRay::~Create2DRay()
{
}
int Create2DRay::GetType() //命令类型
{
	return cmd2dLine;
}
int Create2DRay::OnLButtonDown(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr)
		return -1;
	mStep++; //每次单击鼠标左键时操作步骤计数加一
	if (mStep == 1) //第一次单击鼠标左键，记录起点
	{
		mStart = mEnd = pos;
		mView->Prompt(_T("请输入直线的另一点")); //通过处理事件的View显示到状态栏
	}
	else if (mStep == 2)
	{
		//擦除最后橡皮线
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		dc.SetROP2(R2_NOT);
		dc.MoveTo(CPoint(mStart.x(), mStart.y()));
		dc.LineTo(CPoint(mEnd.x(), mEnd.y()));
		dc.SelectObject(pOldPen);
		//判断是否按下SHIFT键，绘制水平线或垂直线
		if (nFlags & MK_SHIFT)//按下了MK_SHIFT键
		{
			if (abs(pos.x() - mStart.x()) <= abs(pos.y() - mStart.y())) //x方向变化小，垂直线
			{
				mEnd.x() = mStart.x();
				mEnd.y() = pos.y();
			}
			else //x方向变化大，水平线
			{
				mEnd.x() = pos.x();
				mEnd.y() = mStart.y();
			}
		}
		else
		{
			mEnd = pos;
		}
		//获取起点、终点对应的场景坐标
		Vec2d start = mView->ViewPortToWorld(mStart);
		Vec2d end = mView->ViewPortToWorld(mEnd);
		//创建线段并添加到场景
		CG2DRay* pRay = new CG2DRay(start, end);
		pRay->setPenColor(mView->PenColor()); //多态
		pRay->setPenWidth(mView->PenWidth());
		pRay->setPenStyle(mView->PenStyle());
		mView->addRenderable(pRay); //创建成功，添加到场景
		mView->Invalidate();
		mView->UpdateWindow();
		mStep = 0; //设为0可重写开始绘制线段
		mView->Prompt(_T("请输入直线段的起点"));
	}
	else
	{
	}
	return 0;
}
int Create2DRay::OnMouseMove(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr)
		return -1;
	if (mStep == 0)
	{
		mView->Prompt(_T("请输入直线段的起点"));
	}
	else if (mStep == 1) //已经输入了起点后，当前鼠标移动的位置与起点形成橡皮线
	{
		Pos2i prePos, curPos;
		prePos = mEnd;
		//判断是否按下SHIFT键，绘制水平线或垂直线
		if (nFlags & MK_SHIFT)
		{
			if (abs(pos.x() - mStart.x()) <= abs(pos.y() - mStart.y())) //x方向变化小，垂直线
			{
				curPos.x() = mStart.x();
				curPos.y() = pos.y();
			}
			else
			{
				curPos.x() = pos.x();
				curPos.y() = mStart.y();
			}
		}
		else
		{
			curPos = pos;
		}
		//绘制新橡皮线时先擦除上次的橡皮线
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		dc.SetROP2(R2_NOT); //反色模式
		dc.MoveTo(CPoint(mStart.x(), mStart.y()));
		dc.LineTo(CPoint(prePos.x(), prePos.y()));
		//绘制新的橡皮线
		dc.MoveTo(CPoint(mStart.x(), mStart.y()));
		dc.LineTo(CPoint(curPos.x(), curPos.y()));
		dc.SelectObject(pOldPen);
		mEnd = curPos; //记录最新位置，作为终点
	}
	else
	{
	}
	return 0;
}
int Create2DRay::Cancel()
{
	if (mView == nullptr)
		return -1;
	if (mStep == 1) //如果已经单击左键一次，则结束操作前删除橡皮线
	{
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		dc.SetROP2(R2_NOT); //
		dc.MoveTo(CPoint(mStart.x(), mStart.y()));
		dc.LineTo(CPoint(mEnd.x(), mEnd.y()));
		dc.SelectObject(pOldPen);
	}
	mStep = 0;
	mView->Prompt(_T("就绪"));
	return 0;
}
CG_NAMESPACE_EXIT
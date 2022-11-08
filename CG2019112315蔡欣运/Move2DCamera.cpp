#include "pch.h"
#include "Move2DCamera.h"
#include "CGDI2DView.h"

CG_NAMESPACE_ENTER
Move2DCamera::Move2DCamera(CGView* pview/* = nullptr*/)
	:UIEventListener(pview), mStart(0, 0), mEnd(0, 0)
{
	mStep = 0;
}
Move2DCamera::~Move2DCamera()
{
}
int Move2DCamera::GetType() //命令类型
{
	return cmd2dMoveCamera;
}

int Move2DCamera::OnLButtonDown(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr)
		return -1;
	mStep++;
	mStart = mEnd = pos;
	mView->Prompt(_T("松开左键完成移动"));
	return 0;
}
int Move2DCamera::OnMouseMove(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr)
		return -1;
	if (mStep == 0)
	{
		mView->Prompt(_T("按住左键拖动以移动视口"));
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
	return 0;
}
int Move2DCamera::OnLButtonUp(UINT nFlags, const Pos2i& pos) {
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
	Vec2d moveVec = end - start;
	mView->Move2DCamera(-moveVec.x(), -moveVec.y());
	mView->Invalidate();
	mView->UpdateWindow();
	mStep = 0; //设为0可重写开始绘制线段
	mView->Prompt(_T("按住左键拖动以移动视口"));
	return 0;
}

int Move2DCamera::Cancel()
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

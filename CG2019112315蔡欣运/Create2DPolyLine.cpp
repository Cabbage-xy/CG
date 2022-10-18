#include "pch.h"
#include "Create2DPolyLine.h"
#include "CGDI2DView.h"
#include "CG2DLineSegment.h"
#include "CG2DPolyLine.h"
CG_NAMESPACE_ENTER
Create2DPolyLine::Create2DPolyLine(CGView* pview/* = nullptr*/)
	:UIEventListener(pview)
{
	mPoints.push_back(Pos2i(0, 0));
	mStep = 0;
}
Create2DPolyLine::~Create2DPolyLine()
{
}
int Create2DPolyLine::GetType() //命令类型
{
	return cmd2dPolyline;
}
int Create2DPolyLine::OnLButtonDown(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr)
		return -1;
	mStep++; //每次单击鼠标左键时操作步骤计数加一
	if (mStep == 1) //第一次单击鼠标左键，记录起点
	{
		if (mPoints.empty()) {
			mPoints.push_back(pos);
		}
		mPoints[0] = pos;
		mView->Prompt(_T("请单机输入折线段的下一点，或回车输入折线段终点")); //通过处理事件的View显示到状态栏
	}
	else if (mStep >= 2)
	{
		//擦除最后橡皮线
		
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		dc.SetROP2(R2_NOT);
		dc.MoveTo(CPoint(mPoints[mStep - 2].x(), mPoints[mStep - 2].y()));
		dc.LineTo(CPoint(mPoints[mStep - 1].x(), mPoints[mStep - 1].y()));
		dc.MoveTo(CPoint(mPoints[mStep - 2].x(), mPoints[mStep - 2].y()));
		dc.LineTo(CPoint(pos.x(), pos.y()));
		dc.SelectObject(pOldPen);
		if (mPoints.size() < mStep) {
			mPoints.push_back(pos);
		}
		//判断是否按下SHIFT键，绘制水平线或垂直线
		if (nFlags & MK_SHIFT)//按下了MK_SHIFT键
		{
			if (abs(pos.x() - mPoints[mStep - 2].x()) <= abs(pos.y() - mPoints[mStep - 2].y())) //x方向变化小，垂直线
			{
				mPoints[mStep - 1].x() = mPoints[mStep - 2].x();
				mPoints[mStep - 1].y() = pos.y();
			}
			else //x方向变化大，水平线
			{
				mPoints[mStep - 1].x() = pos.x();
				mPoints[mStep - 1].y() = mPoints[mStep - 2].y();
			}
		}
		else
		{
			mPoints[mStep - 1] = pos;
		}
	}
	mPoints.push_back(pos);
	return 0;
}
//双击结束绘制
int Create2DPolyLine::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (mView == nullptr)
		return -1;
	//按下回车时完成绘制
	if (nChar == VK_RETURN) {
		if (mStep >= 1) {
			CClientDC dc(mView);
			CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
			CPen* pOldPen = dc.SelectObject(&pen);
			dc.SetROP2(R2_NOT); //
			for (int i = 1; i < mPoints.size(); i++) {
				dc.MoveTo(CPoint(mPoints[i - 1].x(), mPoints[i - 1].y()));
				dc.LineTo(CPoint(mPoints[i].x(), mPoints[i].y()));
			}
			dc.SelectObject(pOldPen);
			//获取各点对应的场景坐标
			std::vector<Vec2d> points;
			for (auto &v : mPoints) {
				points.push_back(mView->ViewPortToWorld(v));
			}
			//创建线段并添加到场景
			CG2DPolyLine* pPolyLine = new CG2DPolyLine(points);
			pPolyLine->setPenColor(mView->PenColor()); //多态
			pPolyLine->setPenWidth(mView->PenWidth());
			pPolyLine->setPenStyle(mView->PenStyle());
			mView->addRenderable(pPolyLine); //创建成功，添加到场景
			mView->Invalidate();
			mView->UpdateWindow();
		}
		mStep = 0;
		while (!mPoints.empty()) {
			mPoints.pop_back();
		}
		mPoints.push_back(Pos2i(0, 0));
		mView->Prompt(_T("就绪"));
	}
	return 0;
}
int Create2DPolyLine::OnMouseMove(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr)
		return -1;
	if (mStep == 0)
	{
		mView->Prompt(_T("请输入折线的起点"));
	}
	else if (mStep >= 1) //已经输入了起点后，当前鼠标移动的位置与起点形成橡皮线
	{
		if (mPoints.size() < mStep + 1) {
			mPoints.push_back(pos);
		}
		Pos2i prePos, curPos;
		prePos = mPoints[mStep];
		//判断是否按下SHIFT键，绘制水平线或垂直线
		if (nFlags & MK_SHIFT)
		{
			if (abs(pos.x() - mPoints[mStep - 1].x()) <= abs(pos.y() - mPoints[mStep - 1].y())) //x方向变化小，垂直线
			{
				curPos.x() = mPoints[mStep - 1].x();
				curPos.y() = pos.y();
			}
			else
			{
				curPos.x() = pos.x();
				curPos.y() = mPoints[mStep - 1].y();
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
		dc.MoveTo(CPoint(mPoints[mStep - 1].x(), mPoints[mStep - 1].y()));
		dc.LineTo(CPoint(prePos.x(), prePos.y()));
		//绘制新的橡皮线
		dc.MoveTo(CPoint(mPoints[mStep - 1].x(), mPoints[mStep - 1].y()));
		dc.LineTo(CPoint(curPos.x(), curPos.y()));
		dc.SelectObject(pOldPen);
		mPoints[mStep] = curPos; //记录最新位置，作为终点
	}
	else
	{
	}
	return 0;
}
int Create2DPolyLine::Cancel()
{
	if (mView == nullptr)
		return -1;
	if (mStep >= 1) //如果已经单击左键一次，则结束操作前删除橡皮线
	{
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		dc.SetROP2(R2_NOT); //
		for (int i = 1; i < mPoints.size(); i++) {
			dc.MoveTo(CPoint(mPoints[i - 1].x(), mPoints[i - 1].y()));
			dc.LineTo(CPoint(mPoints[i].x(), mPoints[i].y()));
		}
		dc.SelectObject(pOldPen);
	}
	mStep = 0;
	while (!mPoints.empty()) {
		mPoints.pop_back();
	}
	mPoints.push_back(Pos2i(0, 0));
	mView->Prompt(_T("就绪"));
	return 0;
}
CG_NAMESPACE_EXIT
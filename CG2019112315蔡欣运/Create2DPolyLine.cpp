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
int Create2DPolyLine::GetType() //��������
{
	return cmd2dPolyline;
}
int Create2DPolyLine::OnLButtonDown(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr)
		return -1;
	mStep++; //ÿ�ε���������ʱ�������������һ
	if (mStep == 1) //��һ�ε�������������¼���
	{
		if (mPoints.empty()) {
			mPoints.push_back(pos);
		}
		mPoints[0] = pos;
		mView->Prompt(_T("�뵥���������߶ε���һ�㣬��س��������߶��յ�")); //ͨ�������¼���View��ʾ��״̬��
	}
	else if (mStep >= 2)
	{
		//���������Ƥ��
		
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
		//�ж��Ƿ���SHIFT��������ˮƽ�߻�ֱ��
		if (nFlags & MK_SHIFT)//������MK_SHIFT��
		{
			if (abs(pos.x() - mPoints[mStep - 2].x()) <= abs(pos.y() - mPoints[mStep - 2].y())) //x����仯С����ֱ��
			{
				mPoints[mStep - 1].x() = mPoints[mStep - 2].x();
				mPoints[mStep - 1].y() = pos.y();
			}
			else //x����仯��ˮƽ��
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
//˫����������
int Create2DPolyLine::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (mView == nullptr)
		return -1;
	//���»س�ʱ��ɻ���
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
			//��ȡ�����Ӧ�ĳ�������
			std::vector<Vec2d> points;
			for (auto &v : mPoints) {
				points.push_back(mView->ViewPortToWorld(v));
			}
			//�����߶β���ӵ�����
			CG2DPolyLine* pPolyLine = new CG2DPolyLine(points);
			pPolyLine->setPenColor(mView->PenColor()); //��̬
			pPolyLine->setPenWidth(mView->PenWidth());
			pPolyLine->setPenStyle(mView->PenStyle());
			mView->addRenderable(pPolyLine); //�����ɹ�����ӵ�����
			mView->Invalidate();
			mView->UpdateWindow();
		}
		mStep = 0;
		while (!mPoints.empty()) {
			mPoints.pop_back();
		}
		mPoints.push_back(Pos2i(0, 0));
		mView->Prompt(_T("����"));
	}
	return 0;
}
int Create2DPolyLine::OnMouseMove(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr)
		return -1;
	if (mStep == 0)
	{
		mView->Prompt(_T("���������ߵ����"));
	}
	else if (mStep >= 1) //�Ѿ����������󣬵�ǰ����ƶ���λ��������γ���Ƥ��
	{
		if (mPoints.size() < mStep + 1) {
			mPoints.push_back(pos);
		}
		Pos2i prePos, curPos;
		prePos = mPoints[mStep];
		//�ж��Ƿ���SHIFT��������ˮƽ�߻�ֱ��
		if (nFlags & MK_SHIFT)
		{
			if (abs(pos.x() - mPoints[mStep - 1].x()) <= abs(pos.y() - mPoints[mStep - 1].y())) //x����仯С����ֱ��
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
		//��������Ƥ��ʱ�Ȳ����ϴε���Ƥ��
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		dc.SetROP2(R2_NOT); //��ɫģʽ
		dc.MoveTo(CPoint(mPoints[mStep - 1].x(), mPoints[mStep - 1].y()));
		dc.LineTo(CPoint(prePos.x(), prePos.y()));
		//�����µ���Ƥ��
		dc.MoveTo(CPoint(mPoints[mStep - 1].x(), mPoints[mStep - 1].y()));
		dc.LineTo(CPoint(curPos.x(), curPos.y()));
		dc.SelectObject(pOldPen);
		mPoints[mStep] = curPos; //��¼����λ�ã���Ϊ�յ�
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
	if (mStep >= 1) //����Ѿ��������һ�Σ����������ǰɾ����Ƥ��
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
	mView->Prompt(_T("����"));
	return 0;
}
CG_NAMESPACE_EXIT
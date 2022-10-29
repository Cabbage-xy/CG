#include "pch.h"
#include "TransformMirror2DRenderable.h"
#include "CGDI2DView.h"

CG_NAMESPACE_ENTER
TransformMirror2DRenderable::TransformMirror2DRenderable(CGView* pview/* = nullptr*/)
	:UIEventListener(pview), mStart(0, 0), mEnd(0, 0)
{
	mStep = 0;
}
TransformMirror2DRenderable::~TransformMirror2DRenderable()
{
}
int TransformMirror2DRenderable::GetType() //��������
{
	return cmd2dMirrorRenderable;
}

int TransformMirror2DRenderable::OnLButtonDown(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr)
		return -1;
	mStep++;
	mStart = mEnd = pos;
	mView->Prompt(_T("���ƺ��ɿ����"));
	return 0;
}
int TransformMirror2DRenderable::OnMouseMove(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr)
		return -1;
	if (mStep == 0)
	{
		mView->Prompt(_T("��ס�����������"));
	}
	else if (mStep == 1) //�Ѿ����������󣬵�ǰ����ƶ���λ��������γ���Ƥ��
	{
		Pos2i prePos, curPos;
		prePos = mEnd;
		//�ж��Ƿ���SHIFT��������ˮƽ�߻�ֱ��
		if (nFlags & MK_SHIFT)
		{
			if (abs(pos.x() - mStart.x()) <= abs(pos.y() - mStart.y())) //x����仯С����ֱ��
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
		//��������Ƥ��ʱ�Ȳ����ϴε���Ƥ��
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		dc.SetROP2(R2_NOT); //��ɫģʽ
		dc.MoveTo(CPoint(mStart.x(), mStart.y()));
		dc.LineTo(CPoint(prePos.x(), prePos.y()));
		//�����µ���Ƥ��
		dc.MoveTo(CPoint(mStart.x(), mStart.y()));
		dc.LineTo(CPoint(curPos.x(), curPos.y()));
		dc.SelectObject(pOldPen);
		mEnd = curPos; //��¼����λ�ã���Ϊ�յ�
	}
	return 0;
}
int TransformMirror2DRenderable::OnLButtonUp(UINT nFlags, const Pos2i& pos) {
	//���������Ƥ��
	CClientDC dc(mView);
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* pOldPen = dc.SelectObject(&pen);
	dc.SetROP2(R2_NOT);
	dc.MoveTo(CPoint(mStart.x(), mStart.y()));
	dc.LineTo(CPoint(mEnd.x(), mEnd.y()));
	dc.SelectObject(pOldPen);
	//�ж��Ƿ���SHIFT��������ˮƽ�߻�ֱ��
	if (nFlags & MK_SHIFT)//������MK_SHIFT��
	{
		if (abs(pos.x() - mStart.x()) <= abs(pos.y() - mStart.y())) //x����仯С����ֱ��
		{
			mEnd.x() = mStart.x();
			mEnd.y() = pos.y();
		}
		else //x����仯��ˮƽ��
		{
			mEnd.x() = pos.x();
			mEnd.y() = mStart.y();
		}
	}
	else
	{
		mEnd = pos;
	}
	//��ȡ��㡢�յ��Ӧ�ĳ�������
	Vec2d start = mView->ViewPortToWorld(mStart);
	Vec2d end = mView->ViewPortToWorld(mEnd);
	//TODO
	//mView->Mirror(start, end);
	mStep = 0; //��Ϊ0����д��ʼ�����߶�
	mView->Prompt(_T("��ס�����������"));
	return 0;
}

int TransformMirror2DRenderable::Cancel()
{
	if (mView == nullptr)
		return -1;
	if (mStep == 1) //����Ѿ��������һ�Σ����������ǰɾ����Ƥ��
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
	mView->Prompt(_T("����"));
	return 0;
}
CG_NAMESPACE_EXIT
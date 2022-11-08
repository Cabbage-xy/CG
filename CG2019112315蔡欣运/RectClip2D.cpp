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
int RectClip2D::GetType() //��������
{
	return cmd2dRectClip;
}

int RectClip2D::OnLButtonDown(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr)
		return -1;
	mStep++; //ÿ�ε���������ʱ�������������һ
	if (mStep == 1) //��һ�ε�������������¼���
	{
		mStart = mEnd = pos;
		mView->Prompt(_T("�뵥��������ο���һ��")); //ͨ�������¼���View��ʾ��״̬��
	}
	else if (mStep == 2)
	{
		//���������Ƥ��
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		dc.SetROP2(R2_NOT);
		dc.Rectangle(mStart.x(), mStart.y(), mEnd.x(), mEnd.y());
		dc.SelectObject(pOldPen);

		mEnd = pos;

		//��ȡ��㡢�յ��Ӧ�ĳ�������
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
		mStep = 0; //��Ϊ0����д��ʼ�����߶�
		mView->Prompt(_T("�뵥��������ο�һ��"));
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
		mView->Prompt(_T("�뵥��������ο�һ��"));
	}
	else if (mStep == 1) //�Ѿ����������󣬵�ǰ����ƶ���λ��������γ���Ƥ��
	{
		Pos2i prePos, curPos;
		prePos = mEnd;
		curPos = pos;
		//��������Ƥ��ʱ�Ȳ����ϴε���Ƥ��
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		dc.SetROP2(R2_NOT); //��ɫģʽ
		dc.Rectangle(mStart.x(), mStart.y(), prePos.x(), prePos.y());
		//�����µ���Ƥ��
		dc.Rectangle(mStart.x(), mStart.y(), curPos.x(), curPos.y());
		dc.SelectObject(pOldPen);
		mEnd = curPos; //��¼����λ�ã���Ϊ�յ�
	}
	return 0;
}

int RectClip2D::Cancel()
{
	if (mView == nullptr)
		return -1;
	if (mStep == 1) //����Ѿ��������һ�Σ����������ǰɾ����Ƥ��
	{
		CClientDC dc(mView);
		CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);
		dc.SetROP2(R2_NOT);
		dc.Rectangle(mStart.x(), mStart.y(), mEnd.x(), mEnd.y());
		dc.SelectObject(pOldPen);
	}
	mStep = 0;
	mView->Prompt(_T("����"));
	return 0;
}
CG_NAMESPACE_EXIT
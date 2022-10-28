#include "pch.h"
#include "Create2DCircle3Point.h"
#include "CGDI2DView.h"
#include "CG2DCircle.h"
CG_NAMESPACE_ENTER
Create2DCircle3Point::Create2DCircle3Point(CGView* pview/* = nullptr*/)
	:UIEventListener(pview), mFirst(0, 0), mSecond(0, 0), mThird(0, 0)
{
	mStep = 0;
}
Create2DCircle3Point::~Create2DCircle3Point()
{
}
int Create2DCircle3Point::GetType() //��������
{
	return cmd2dCircle3Point;
}
int Create2DCircle3Point::OnLButtonDown(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr)
		return -1;
	mStep++;
	if (mStep == 1) {
		mFirst = mSecond = mThird = pos;
		mView->Prompt(_T("�뵥������ڶ�����")); //ͨ�������¼���View��ʾ��״̬��
	}
	else if (mStep == 2) {
		mSecond = mThird = pos;
		mView->Prompt(_T("�뵥�������������")); //ͨ�������¼���View��ʾ��״̬��
	}
	else if (mStep == 3) {
		mThird = pos;
		//����Բ�ġ��뾶
		int x1 = mFirst.x(), x2 = mSecond.x(), x3 = mThird.x();
		int y1 = mFirst.y(), y2 = mSecond.y(), y3 = mThird.y();
		int a = x1 - x2;
		int b = y1 - y2;
		int c = x1 - x3;
		int d = y1 - y3;
		double e = ((x1 * x1 - x2 * x2) + (y1 * y1 - y2 * y2)) / 2.0;
		double f = ((x1 * x1 - x3 * x3) + (y1 * y1 - y3 * y3)) / 2.0;
		double det = b * c - a * d;
		double radius;
		if (fabs(det) < 1e-5)//�ж��Ƿ����㹲��
		{
			radius = -1;
			AfxMessageBox(_T("���㲻�ܹ��ߣ�"));
			Cancel();
			return 0;
		}
		int x0 = round(-(d * e - b * f) / det);
		int y0 = round(-(a * f - c * e) / det);
		radius = hypot(x1 - x0, y1 - y0);
		//����Բ����
		Pos2i center(x0, y0);
		CG2DCircle* pCircle = new CG2DCircle(mView->ViewPortToWorld(center), radius);
		pCircle->setPenColor(mView->PenColor()); //��̬
		pCircle->setPenWidth(mView->PenWidth());
		pCircle->setPenStyle(mView->PenStyle());
		pCircle->setBrushColor(mView->BrushColor());
		pCircle->setBrushUse(mView->UseBrush());
		mView->addRenderable(pCircle); //�����ɹ�����ӵ�����
		mView->Invalidate();
		mView->UpdateWindow();
		mStep = 0;
		mView->Prompt(_T("�뵥�������һ����"));
	}
	return 0;
}

int Create2DCircle3Point::OnMouseMove(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr)
		return -1;
	if (mStep < 1) {
		mView->Prompt(_T("�뵥�������һ����"));
	}
	else if (mStep == 1) {
		
		mSecond = pos; //��¼����λ�ã���Ϊ�յ�
	}
	else if (mStep == 2) {
		mThird = pos;
	}
	return 0;
}
int Create2DCircle3Point::Cancel()
{
	if (mView == nullptr)
		return -1;
	mFirst = mSecond = mThird = Pos2i(0, 0);
	mStep = 0;
	mView->Prompt(_T("����"));
	return 0;
}
CG_NAMESPACE_EXIT
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
int Create2DCircle1PointRadius::GetType() //��������
{
	return cmd2dCircle1PointRadius;
}
int Create2DCircle1PointRadius::OnLButtonDown(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr)
		return -1;
	mCenter = pos;
	CInputDialog1 dlg;
	dlg.mTitle = _T("������뾶����"); //������Ҫ���öԻ������
	if (dlg.DoModal() == IDOK) //�Ի����е���ˡ�ȷ������ť��ȡ�����������
	{ //����ʵ����Ҫʹ�����������
	//�������������ֵ�����ַ���ת��Ϊ��ֵ
		double radius = _ttof(dlg.mValue1);
		//
		//�˴�ֻ��ʾ���������
		//AfxMessageBox(dlg.mValue1);
		Vec2d center = mView->ViewPortToWorld(mCenter);
		CG2DCircle* pCircle = new CG2DCircle(center, radius);
		pCircle->setPenColor(mView->PenColor()); //��̬
		pCircle->setPenWidth(mView->PenWidth());
		pCircle->setPenStyle(mView->PenStyle());
		mView->addRenderable(pCircle); //�����ɹ�����ӵ�����
		mView->Invalidate();
		mView->UpdateWindow();
	}
	mView->Prompt(_T("�뵥������Բ��λ��"));
	return 0;
}

int Create2DCircle1PointRadius::OnMouseMove(UINT nFlags, const Pos2i& pos)
{
	if (mView == nullptr)
		return -1;
	mCenter = pos;
	mView->Prompt(_T("�뵥������Բ��λ��"));
	return 0;
}
int Create2DCircle1PointRadius::Cancel()
{
	if (mView == nullptr)
		return -1;
	mView->Prompt(_T("����"));
	return 0;
}
CG_NAMESPACE_EXIT
#include "pch.h"
#include "TransformRotate2DRenderable.h"
#include "CGDI2DView.h"
#include "CInputDialog1.h"

CG_NAMESPACE_ENTER
TransformRotate2DRenderable::TransformRotate2DRenderable(CGView* pview/* = nullptr*/)
	:UIEventListener(pview), mCenter(0, 0)
{
	mView->Prompt(_T("���ѡ����ת���ĵ�"));
}
TransformRotate2DRenderable::~TransformRotate2DRenderable()
{
}
int TransformRotate2DRenderable::GetType() //��������
{
	return cmd2dRotateRenderable;
}

int TransformRotate2DRenderable::OnLButtonUp(UINT nFlags, const Pos2i& pos) {
	//��ȡ���ĵ�
	Vec2d center = mView->ViewPortToWorld(pos);
	CInputDialog1 dlg;
	dlg.mTitle = _T("��������ת�Ƕ�(��ʱ��Ϊ����˳ʱ��Ϊ��)"); //������Ҫ���öԻ������
	if (dlg.DoModal() == IDOK) //�Ի����е���ˡ�ȷ������ť��ȡ�����������
	{ 
		//����ʵ����Ҫʹ�����������
		//�������������ֵ�����ַ���ת��Ϊ��ֵ
		double degrees = _ttof(dlg.mValue1);
		mView->Rotate(degrees, center.x(), center.y());
	}
	//mView->Invalidate();
	//mView->UpdateWindow();
	mView->Prompt(_T("���ѡ����ת���ĵ�"));
	return 0;
}

int TransformRotate2DRenderable::Cancel()
{
	if (mView == nullptr)
		return -1;
	//mStep = 0;
	mView->Prompt(_T("����"));
	return 0;
}
CG_NAMESPACE_EXIT
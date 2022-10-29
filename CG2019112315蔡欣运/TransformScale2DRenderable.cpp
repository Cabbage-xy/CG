#include "pch.h"
#include "TransformScale2DRenderable.h"
#include "CGDI2DView.h"
#include "CInputDialog1.h"

CG_NAMESPACE_ENTER
TransformScale2DRenderable::TransformScale2DRenderable(CGView* pview/* = nullptr*/)
	:UIEventListener(pview), mCenter(0, 0)
{
	mView->Prompt(_T("���ѡ����ת���ĵ�"));
}
TransformScale2DRenderable::~TransformScale2DRenderable()
{
}
int TransformScale2DRenderable::GetType() //��������
{
	return cmd2dScaleRenderable;
}

int TransformScale2DRenderable::OnLButtonUp(UINT nFlags, const Pos2i& pos) {
	//��ȡ���ĵ�
	Vec2d center = mView->ViewPortToWorld(pos);
	CInputDialog1 dlg;
	dlg.mTitle = _T("������x�������ű���"); //������Ҫ���öԻ������
	dlg.mValue1 = _T("1");
	INT_PTR isDlg1OK = dlg.DoModal() == IDOK;
	if (!isDlg1OK) return 0;
	double sx = _ttof(dlg.mValue1);
	dlg.mTitle = _T("������y�������ű���");
	INT_PTR isDlg2OK = dlg.DoModal() == IDOK;
	if (!isDlg2OK) return 0;
	double sy = _ttof(dlg.mValue1);

	mView->Scale(sx, sy, center.x(), center.y());

	mView->Prompt(_T("���ѡ���������ĵ�"));
	return 0;
}

int TransformScale2DRenderable::Cancel()
{
	if (mView == nullptr)
		return -1;
	//mStep = 0;
	mView->Prompt(_T("����"));
	return 0;
}
CG_NAMESPACE_EXIT
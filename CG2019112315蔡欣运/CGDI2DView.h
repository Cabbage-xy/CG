#ifndef _CGDI2DVIEW_H_INCLUDED
#define _CGDI2DVIEW_H_INCLUDED
#include "CGView.h"
CG_NAMESPACE_ENTER
class CGDI2DView : public CGView
{
	DECLARE_DYNCREATE(CGDI2DView)
protected: // �������л�����
	CGDI2DView();
	// ����
public:
	// ʵ��
public:
	virtual ~CGDI2DView();
	// ��д
public:
	virtual void OnInitialUpdate(); // ��д�Դ������ƻ���
};
CG_NAMESPACE_EXIT
#endif //_CGDI2DVIEW_H_INCLUDED
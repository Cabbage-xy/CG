#ifndef _CREATE2DCIRCLE2POINTDIAMETER_H_INCLUDED
#define _CREATE2DCIRCLE2POINTDIAMETER_H_INCLUDED
#include "UIEventListener.h"
CG_NAMESPACE_ENTER
class Create2DCircle2PointDiameter : public UIEventListener
{
	friend class CGDI2DView;
public:
	Create2DCircle2PointDiameter(CGView* pview = nullptr);
	~Create2DCircle2PointDiameter();
	virtual int GetType(); //��������
	//�ٶ�����������ʰȡֱ�����㣬�ƶ����ʱ����Ƥ����
	virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
	virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
	//ȡ������ִ�е�����簴ESC����
	virtual int Cancel();
protected:
	Pos2i mStart, mEnd; //ֱ��������յ�
};
CG_NAMESPACE_EXIT
#endif //_CREATE2DCIRCLE2POINTDIAMETER_H_INCLUDED
#ifndef _CREATE2DCIRCLE1POINTRADIUS_H_INCLUDED
#define _CREATE2DCIRCLE1POINTRADIUS_H_INCLUDED
#include "UIEventListener.h"
CG_NAMESPACE_ENTER
class Create2DCircle1PointRadius : public UIEventListener
{
	friend class CGDI2DView;
public:
	Create2DCircle1PointRadius(CGView* pview = nullptr);
	~Create2DCircle1PointRadius();
	virtual int GetType(); //��������
	//�ٶ�����������ʰȡԲ��
	virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
	virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
	//ȡ������ִ�е�����簴ESC����
	virtual int Cancel();
protected:
	Pos2i mCenter; //Բ��
};
CG_NAMESPACE_EXIT
#endif //_CREATE2DCIRCLE1POINTRADIUS_H_INCLUDED
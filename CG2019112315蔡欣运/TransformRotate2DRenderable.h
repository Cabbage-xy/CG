#ifndef _TRANSFORMROTATE2DRENDERABLE_H_INCLUDED
#define _TRANSFORMROTATE2DRENDERABLE_H_INCLUDED
#include "UIEventListener.h"
CG_NAMESPACE_ENTER
class TransformRotate2DRenderable :
	public UIEventListener
{
	friend class CGDI2DView;
public:
	TransformRotate2DRenderable(CGView* pview = nullptr);
	~TransformRotate2DRenderable();
	virtual int GetType(); //��������
	//�ٶ�����������ʰȡ�߶���㡢�յ㣬�ƶ����ʱ����Ƥ����
	virtual int OnLButtonUp(UINT nFlags, const Pos2i& pos);
	//ȡ������ִ�е�����簴ESC����
	virtual int Cancel();
protected:
	Pos2i mCenter; //����ѡ�����ת���ĵ�
};
CG_NAMESPACE_EXIT
#endif //_TRANSFORMROTATE2DRENDERABLE_H_INCLUDED
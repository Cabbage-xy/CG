#ifndef _TRANSFORMSCALE2DRENDERABLE_H_INCLUDED
#define _TRANSFORMSCALE2DRENDERABLE_H_INCLUDED
#include "UIEventListener.h"
CG_NAMESPACE_ENTER
class TransformScale2DRenderable :
	public UIEventListener
{
	friend class CGDI2DView;
public:
	TransformScale2DRenderable(CGView* pview = nullptr);
	~TransformScale2DRenderable();
	virtual int GetType(); //��������
	//�ٶ�����������ʰȡ�߶���㡢�յ㣬�ƶ����ʱ����Ƥ����
	virtual int OnLButtonUp(UINT nFlags, const Pos2i& pos);
	//ȡ������ִ�е�����簴ESC����
	virtual int Cancel();
protected:
	Pos2i mCenter; //����ѡ�����ת���ĵ�
};
CG_NAMESPACE_EXIT
#endif //_TRANSFORMSCALE2DRENDERABLE_H_INCLUDED
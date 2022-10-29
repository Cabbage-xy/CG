#ifndef _TRANSFORMMIRROR2DRENDERABLE_H_INCLUDED
#define _TRANSFORMMIRROR2DRENDERABLE_H_INCLUDED
#include "UIEventListener.h"
CG_NAMESPACE_ENTER
class TransformMirror2DRenderable :
	public UIEventListener
{
	friend class CGDI2DView;
public:
	TransformMirror2DRenderable(CGView* pview = nullptr);
	~TransformMirror2DRenderable();
	virtual int GetType(); //��������
	//�ٶ�����������ʰȡ�߶���㡢�յ㣬�ƶ����ʱ����Ƥ����
	virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
	virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
	virtual int OnLButtonUp(UINT nFlags, const Pos2i& pos);
	//ȡ������ִ�е�����簴ESC����
	virtual int Cancel();
protected:
	Pos2i mStart; //�ƶ�ʸ�����
	Pos2i mEnd; //�ƶ�ʸ���յ�
};
CG_NAMESPACE_EXIT
#endif //_TRANSFORMMIRROR2DRENDERABLE_H_INCLUDED



#ifndef _PICK2DRENDERABLE_H_INCLUDED
#define _PICK2DRENDERABLE_H_INCLUDED
#include "UIEventListener.h"
CG_NAMESPACE_ENTER
class Pick2DRenderable : public UIEventListener
{
	friend class CGDI2DView;
public:
	Pick2DRenderable(CGView* pview = nullptr);
	~Pick2DRenderable();
	virtual int GetType(); //命令类型
	//鼠标事件（鼠标左键单击用于拾取）
	virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
	virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
	//取消Esc
	virtual int Cancel();
protected:
};
CG_NAMESPACE_EXIT
#endif //_PICK2DRENDERABLE_H_INCLUDED
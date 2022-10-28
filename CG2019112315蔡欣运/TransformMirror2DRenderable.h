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
	virtual int GetType(); //命令类型
	//假定鼠标左键单击拾取线段起点、终点，移动鼠标时画橡皮筋线
	virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
	virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
	virtual int OnLButtonUp(UINT nFlags, const Pos2i& pos);
	//取消正在执行的命令（如按ESC键）
	virtual int Cancel();
protected:
	Pos2i mStart; //移动矢量起点
	Pos2i mEnd; //移动矢量终点
};
CG_NAMESPACE_EXIT
#endif //_TRANSFORMMIRROR2DRENDERABLE_H_INCLUDED



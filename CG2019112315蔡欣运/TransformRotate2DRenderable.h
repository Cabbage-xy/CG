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
	virtual int GetType(); //命令类型
	//假定鼠标左键单击拾取线段起点、终点，移动鼠标时画橡皮筋线
	virtual int OnLButtonUp(UINT nFlags, const Pos2i& pos);
	//取消正在执行的命令（如按ESC键）
	virtual int Cancel();
protected:
	Pos2i mCenter; //单机选择的旋转中心点
};
CG_NAMESPACE_EXIT
#endif //_TRANSFORMROTATE2DRENDERABLE_H_INCLUDED
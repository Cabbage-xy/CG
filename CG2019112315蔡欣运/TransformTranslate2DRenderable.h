#ifndef _TRANSFORMTRANSLATE2DRENDERABLE_H_INCLUDED
#define _TRANSFORMTRANSLATE2DRENDERABLE_H_INCLUDED
#include "UIEventListener.h"
CG_NAMESPACE_ENTER
class TransformTranslate2DRenderable :
    public UIEventListener
{
	friend class CGDI2DView;
public:
	TransformTranslate2DRenderable(CGView* pview = nullptr);
	~TransformTranslate2DRenderable();
	virtual int GetType(); //命令类型
	//假定鼠标左键单击拾取线段起点、终点，移动鼠标时画橡皮筋线
	virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
	virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
	virtual int OnLButtonUp(UINT nFlags, const Pos2i& pos);
	//取消正在执行的命令（如按ESC键）
	virtual int Cancel();
protected:
	Pos2i mStart; //轴线起点
	Pos2i mEnd; //轴线终点
};
CG_NAMESPACE_EXIT
#endif //_TRANSFORMTRANSLATE2DRENDERABLE_H_INCLUDED


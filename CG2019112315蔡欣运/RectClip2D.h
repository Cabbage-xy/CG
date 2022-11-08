#ifndef _RECTCLIP2D_H_INCLUDED
#define _RECTCLIP2D_H_INCLUDED
#include "UIEventListener.h"
CG_NAMESPACE_ENTER
class RectClip2D :
    public UIEventListener
{
	friend class CGDI2DView;
public:
	RectClip2D(CGView* pview = nullptr);
	~RectClip2D();
	virtual int GetType(); //命令类型
	//假定鼠标左键单击拾取线段起点、终点，移动鼠标时画橡皮筋线
	virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
	virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
	//取消正在执行的命令（如按ESC键）
	virtual int Cancel();
protected:
	Pos2i mStart; //点击的第一点作为线段起点
	Pos2i mEnd; //点击的第二点作为线段终点
};
CG_NAMESPACE_EXIT
#endif //_RECTCLIP2D_H_INCLUDED
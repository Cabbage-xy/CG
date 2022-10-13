#ifndef _CREATE2DRAY_H_INCLUDED
#define _CREATE2DRAY_H_INCLUDED
#include "UIEventListener.h"
CG_NAMESPACE_ENTER
class Create2DRay : public UIEventListener
{
	friend class CGDI2DView;
public:
	Create2DRay(CGView* pview = nullptr);
	~Create2DRay();
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
#endif //_Create2DRay_H_INCLUDED
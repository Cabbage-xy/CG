#ifndef _CREATE2DCIRCLE2POINTDIAMETER_H_INCLUDED
#define _CREATE2DCIRCLE2POINTDIAMETER_H_INCLUDED
#include "UIEventListener.h"
CG_NAMESPACE_ENTER
class Create2DCircle2PointDiameter : public UIEventListener
{
	friend class CGDI2DView;
public:
	Create2DCircle2PointDiameter(CGView* pview = nullptr);
	~Create2DCircle2PointDiameter();
	virtual int GetType(); //命令类型
	//假定鼠标左键单击拾取直径两点，移动鼠标时画橡皮筋线
	virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
	virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
	//取消正在执行的命令（如按ESC键）
	virtual int Cancel();
protected:
	Pos2i mStart, mEnd; //直径起点与终点
};
CG_NAMESPACE_EXIT
#endif //_CREATE2DCIRCLE2POINTDIAMETER_H_INCLUDED
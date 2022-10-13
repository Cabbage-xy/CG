#ifndef _CREATE2DCIRCLE1POINTRADIUS_H_INCLUDED
#define _CREATE2DCIRCLE1POINTRADIUS_H_INCLUDED
#include "UIEventListener.h"
CG_NAMESPACE_ENTER
class Create2DCircle1PointRadius : public UIEventListener
{
	friend class CGDI2DView;
public:
	Create2DCircle1PointRadius(CGView* pview = nullptr);
	~Create2DCircle1PointRadius();
	virtual int GetType(); //命令类型
	//假定鼠标左键单击拾取圆心
	virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
	virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
	//取消正在执行的命令（如按ESC键）
	virtual int Cancel();
protected:
	Pos2i mCenter; //圆心
};
CG_NAMESPACE_EXIT
#endif //_CREATE2DCIRCLE1POINTRADIUS_H_INCLUDED
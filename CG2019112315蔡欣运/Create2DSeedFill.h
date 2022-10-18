#ifndef _CREATE2DSEEDFILL_H_INCLUDED
#define _CREATE2DSEEDFILL_H_INCLUDED
#include "UIEventListener.h"
CG_NAMESPACE_ENTER
class Create2DSeedFill : public UIEventListener
{
	friend class CGDI2DView;
public:
	Create2DSeedFill(CGView* pview = nullptr);
	~Create2DSeedFill();
	virtual int GetType(); //命令类型
	//假定鼠标左键单击拾取线段起点、终点，移动鼠标时画橡皮筋线
	virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
	//virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
	//取消正在执行的命令（如按ESC键）
	virtual int Cancel();
protected:
	//Pos2i
};
CG_NAMESPACE_EXIT
#endif //_CREATE2DSEEDFILL_H_INCLUDED
#ifndef _CREATE2DPOLYGON_H_INCLUDED
#define _CREATE2DPOLYGON_H_INCLUDED
#include "UIEventListener.h"
CG_NAMESPACE_ENTER
class Create2DPolygon : public UIEventListener
{
	friend class CGDI2DView;
public:
	Create2DPolygon(CGView* pview = nullptr);
	~Create2DPolygon();
	virtual int GetType(); //命令类型
	//假定鼠标左键单击拾取线段起点、终点，移动鼠标时画橡皮筋线
	virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
	virtual int OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
	//取消正在执行的命令（如按ESC键）
	virtual int Cancel();
protected:
	std::vector<Pos2i> mPoints; //点击的点依次连成折线段
};
CG_NAMESPACE_EXIT
#endif //_CREATE2DPOLYGON_H_INCLUDED
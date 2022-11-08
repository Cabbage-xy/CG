#ifndef _UIEVENTLISTENER_H_INCLUDED
#define _UIEVENTLISTENER_H_INCLUDED
#include "Vector2.h"
#include "CGObject.h"
CG_NAMESPACE_ENTER
enum CommandType
{
	cmdNone = 0, //无，显示鼠标指针，不交互画图
	cmd2dLineSegment = 1, //利用起点、终点绘制直线段
	cmd2dLine = 2, //启用两点绘制无限长直线
	cmd2dRay = 3, //利用起点、方向（第二点确定）绘制射线
	cmd2dPolyline = 4, //折线连续相连的直线段形成
	cmd2dCircle1PointRadius = 5, //一点+输入半径画圆
	cmd2dCircle2PointRadius = 6, //两点为半径画圆
	cmd2dCircle2PointDiameter = 7, //两点为直径画圆
	cmd2dCircle3Point = 8, //三点外接圆
	cmd2dPolygon = 9, //绘制一般多边形
	cmd2dSeedFill = 10, //种子填充
	//二维变换指令
	cmd2dTranslateRenderable = 100, //自由平移
	cmd2dRotateRenderable = 101, //绕选点旋转
	cmd2dScaleRenderable = 102, //指定点，指定方向缩放
	cmd2dMirrorRenderable = 103, //指定轴线对称
	//二维观察指令
	cmd2dMoveCamera = 110,
	cmd2dPickRenderable = 1000, //拾取图形
};
//使用命令模式，简化CGView派生类中键盘、鼠标事件的处理
class UIEventListener : public CGObject
{
	friend class CGView;
public:
	UIEventListener(CGView* pview = nullptr); //使用命令对象的View对象（CGView派生类）
	~UIEventListener();
	virtual int GetType() = 0; //命令类型，必须在派生类中重写
	//鼠标事件（都只给出默认实现，派生类根据需要重写相应的函数）
	virtual int OnLButtonUp(UINT nFlags, const Pos2i& pos);
	virtual int OnLButtonDown(UINT nFlags, const Pos2i& pos);
	virtual int OnLButtonDblClk(UINT nFlags, const Pos2i& pos);
	virtual int OnMouseMove(UINT nFlags, const Pos2i& pos);
	virtual int OnMouseWheel(UINT nFlags, short zDelta, Pos2i pt);
	virtual int OnMButtonUp(UINT nFlags, const Pos2i& pos);
	virtual int OnMButtonDown(UINT nFlags, const Pos2i& pos);
	virtual int OnMButtonDblClk(UINT nFlags, const Pos2i& pos);
	virtual int OnRButtonUp(UINT nFlags, const Pos2i& pos);
	virtual int OnRButtonDown(UINT nFlags, const Pos2i& pos);
	virtual int OnRButtonDblClk(UINT nFlags, const Pos2i& pos);
	//键盘事件
	virtual int OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual int OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual int OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual int OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual int OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//取消命令（按ESC键中断当前命令的执行），必须在派生类中重写
	virtual int Cancel() = 0;
	//CGRenderContext* RenderContext(); //
protected:
	int mStep; // 命令操作计数
	CGView* mView; // 处理事件的窗口
};
CG_NAMESPACE_EXIT
#endif //_UIEVENTLISTENER_H_INCLUDED
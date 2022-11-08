#ifndef _CGVIEW_H_INCLUDED
#define _CGVIEW_H_INCLUDED
#include <afxwin.h>
#include "Vector2.h"
CG_NAMESPACE_ENTER
class CGRenderContext;//如果类的声明中只需要对象指针，则考虑类预声明。
class UIEventListener;//命令模式下键盘鼠标交互的用到的基类
class CGRenderable; //图形对象（几何、变换、属性）基类
class CGView : public CView
{
	DECLARE_DYNCREATE(CGView)
protected: // 仅从序列化创建，不能是抽象类
	CGView();
	// 操作
public:
	CGRenderContext* GetRenderContext(); //获取或更新渲染环境
	//需要在派生类中重写的函数
	virtual bool RenderScene();
	//图形对象添加到场景，用于交互创建对象
	virtual bool addRenderable(CGRenderable* r);
	virtual bool delReaderable(CGRenderable* r);
	//画笔属性
	virtual COLORREF PenColor() const;
	virtual int PenWidth() const;
	virtual int PenStyle() const;
	//画刷属性
	virtual bool UseBrush() const;
	virtual COLORREF BrushColor() const;
	virtual int BrushIndex() const;
	//画线算法
	virtual int LineAlgorithm() const;
	//圆弧算法
	virtual int CircleAlgorithm() const;
	//填充算法
	virtual int FillAlgorithm() const;
	virtual int SeedAlgorithm() const;
	//点阵区域的边界颜色
	virtual COLORREF BoundColor() const;
	//点阵区域的内点颜色
	virtual COLORREF FloodColor() const;
	//显示提示信息
	virtual void Prompt(const CString& str);
	//根据视口坐标获取对应场景坐标（二维）
	virtual Vec2d ViewPortToWorld(const Vec2i& p);
	virtual Vec2i WorldToViewPort(const Vec2d& p);
	//图形对象的拾取（二维图形）
	virtual void UpdatePicked(const Vec2d& p, double radius); //更新选择
	virtual void AppendPicked(const Vec2d& p, double radius); //添加选择
	//二维图形对象的几何变换（针对选择集中的对象）
	virtual void Translate(double tx, double ty); //平移
	virtual void Rotate(double angle, double cx, double cy); //旋转（逆时针为正，度）
	virtual void Scale(double sx, double sy); //缩放
	virtual void Scale(double sx, double sy, double cx, double cy); //缩放（关于指定参考点缩放）
	virtual void Scale(double sx, double sy, double cx, double cy, const Vec2d& xDir); //缩放（指定参考点，缩放方向）
	virtual void ShearXYAxis(double shx, double shy); //沿X、Y轴错切
	// 实现
public:
	virtual ~CGView();
	// 重写
public:
	virtual void OnDraw(CDC* pDC); // 基类中是纯虚函数，必须在派生类中重写以绘制该视图
protected:
	CGRenderContext * mRenderContext; //渲染环境
	UIEventListener* mCommand; //交互命令
};
CG_NAMESPACE_EXIT
#endif //_CGVIEW_H_INCLUDED
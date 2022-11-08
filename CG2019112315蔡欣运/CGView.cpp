#include "pch.h"
#include "CGView.h"
#include "CGRenderContext.h"
#include "UIEventListener.h"
#include "CGRenderable.h"
CG_NAMESPACE_ENTER
IMPLEMENT_DYNCREATE(CGView, CView)
CGView::CGView()
{
	mRenderContext = nullptr; // 派生类中初始化 new CGRenderContext(this);
	mCommand = nullptr;
}
CGView::~CGView()
{
	if (mRenderContext != nullptr)
	{
		delete mRenderContext;
		mRenderContext = nullptr;
	}
	if (mCommand != nullptr)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
}
void CGView::OnDraw(CDC* pDC)
{
	//派生类中实现
}
CGRenderContext* CGView::GetRenderContext()
{
	return mRenderContext;
}
bool CGView::RenderScene()
{
	//派生类中实现
	return false;
}
//图形对象添加到场景
bool CGView::addRenderable(CGRenderable * r)
{
	//派生类中实现
	return false;
}
bool CGView::delReaderable(CGRenderable* r)
{
	//派生类中实现
	return false;
}
//画笔属性
COLORREF CGView::PenColor() const
{
	//派生类中实现
	return RGB(0, 0, 0);
}
int CGView::PenWidth() const
{
	//派生类中实现
	return 1;
}
int CGView::PenStyle() const
{
	//派生类中实现
	return PS_SOLID;
}
//画刷属性
bool CGView::UseBrush() const
{
	//派生类中实现
	return false;
}
COLORREF CGView::BrushColor() const
{
	//派生类中实现
	return RGB(255, 255, 255);
}
int CGView::BrushIndex() const
{
	//派生类中实现
	return 0;
}
//画线算法
int CGView::LineAlgorithm() const
{
	//派生类中实现
	return 0;
}
//圆弧算法
int CGView::CircleAlgorithm() const
{
	//派生类中实现
	return 0;
}
//填充算法
int CGView::FillAlgorithm() const
{
	//派生类中实现
	return 0;
}
int CGView::SeedAlgorithm() const
{
	//派生类中实现
	return 0;
}
//点阵区域的边界颜色
COLORREF CGView::BoundColor() const
{
	//派生类中实现
	return RGB(0, 0, 0);
}
//点阵区域的内点颜色
COLORREF CGView::FloodColor() const
{
	//派生类中实现
	return RGB(255, 255, 255);
}
void CGView::Prompt(const CString& str)
{
	//派生类中实现
	UNUSED(str);
}
//根据视口坐标获取对应场景坐标（二维）
Vec2d CGView::ViewPortToWorld(const Vec2i& p)
{
	//派生类中实现
	return Vec2d();
}
Vec2i CGView::WorldToViewPort(const Vec2d& p)
{
	//派生类中实现
	return Vec2i();
}
//图形对象的拾取（二维图形）
void CGView::UpdatePicked(const Vec2d& p, double radius) //更新选择
{
	//派生类中实现
}
void CGView::AppendPicked(const Vec2d& p, double radius) //添加选择
{
	//派生类中实现
}
//二维图形对象的几何变换（针对选择集中的对象）
void CGView::Translate(double tx, double ty) //平移
{
	//派生类中实现
}
void CGView::Rotate(double angle, double cx, double cy) //旋转（逆时针为正，度）
{
	//派生类中实现
}
void CGView::Scale(double sx, double sy) //缩放
{
	//派生类中实现
}
void CGView::Scale(double sx, double sy, double cx, double cy) //缩放（关于指定参考点缩放）
{
	//派生类中实现
}
void CGView::Scale(double sx, double sy, double cx, double cy, const Vec2d& xDir) //缩放（指定参考点，缩放方向）
{
	//派生类中实现
}
void CGView::ShearXYAxis(double shx, double shy) //沿X、Y轴错切
{
	//派生类中实现
}
CG_NAMESPACE_EXIT
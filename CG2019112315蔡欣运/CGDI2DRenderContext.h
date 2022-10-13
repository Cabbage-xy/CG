#ifndef _CGDI2DRENDERCONTEXT_H_INCLUDED
#define _CGDI2DRENDERCONTEXT_H_INCLUDED
#define USEMEMDC //二维图形是否使用内存DC（双缓存）
#include "CGRenderContext.h"
CG_NAMESPACE_ENTER
class CGDI2DView; //实验中二维视图类的基类，如果类的声明中只需要对象指针，则考虑类预声明。
class CGDI2DRenderContext : public CGRenderContext
{
public:
	CGDI2DRenderContext();
	CGDI2DRenderContext(CGDI2DView* pView);
	virtual ~CGDI2DRenderContext();
	//自定义内容
	virtual void setView(CGView* pView); //覆盖基类setView
#ifdef USEMEMDC
	HDC hmemDC() const { return mMemDC; }
	HBITMAP hmemBMP() const { return mMemBMP; }
	void SwapBackBuffer();
#endif
public:
	//直线段绘制算法
	virtual void DDALine(const Vec2i& start, const Vec2i& end, unsigned long color);
	virtual void DDALine(const Vec2i& start, const Vec2i& end, unsigned long color, int width);
	virtual void DDALine(const Vec2i& start, const Vec2i& end, unsigned long color, int width, int style);
	virtual void MidPointLine(const Vec2i& start, const Vec2i& end, unsigned long color);
	virtual void MidPointLine(const Vec2i& start, const Vec2i& end, unsigned long color, int width);
	virtual void MidPointLine(const Vec2i& start, const Vec2i& end, unsigned long color, int width, int style);
	virtual void BresenhamLine(const Vec2i& start, const Vec2i& end, unsigned long color);
	virtual void BresenhamLine(const Vec2i& start, const Vec2i& end, unsigned long color, int width);
	virtual void BresenhamLine(const Vec2i& start, const Vec2i& end, unsigned long color, int width, int style);
	
	//圆绘制算法
	void CirclePlot(const Vec2i& center, int x, int y, unsigned long color); //用于在MidPoint和Bresenham中绘制八个对称位置的像素
	virtual void MidPointCircle(const Vec2i& center, int radius, unsigned long color);
	virtual void BresenhamCircle(const Vec2i& center, int radius, unsigned long color);
	/*
	virtual void CircleArc(const Vec2i& center, int radius, unsigned long color, float startAngle, float sweepAngle); //逆时针
	//椭圆绘制算法（轴对齐椭圆）
	virtual void MidPointEllipse(const Vec2i& center, int a, int b, unsigned long color);
	virtual void EllipseArc(const Vec2i& center, int a, int b, unsigned long color, float startAngle, float sweepAngle); //逆时针
	//有效边表多边形扫描线填充算法
	virtual void ScanLinePolygonFill(const Vec2iArray& pnts, unsigned long fillcolor);
	//边界表示的种子填充算法
	virtual void BoundFill4(int x, int y, unsigned long boundcolor, unsigned long fillcolor);
	virtual void BoundFill8(int x, int y, unsigned long boundcolor, unsigned long fillcolor);
	//内点表示的种子填充算法
	virtual void FloodFill4(int x, int y, unsigned long innercolor, unsigned long fillcolor);
	virtual void FloodFill8(int x, int y, unsigned long innercolor, unsigned long fillcolor);
	//扫描线种子填充算法
	virtual void ScanLineSeedFill(int x, int y, unsigned long boundcolor, unsigned long fillcolor);*/
protected:
#ifdef USEMEMDC
	//二维图形用（双缓存支持）
	HDC mMemDC;
	HBITMAP mMemBMP;
#endif
};
CG_NAMESPACE_EXIT
#endif //_CGDI2DRENDERCONTEXT_H_INCLUDED
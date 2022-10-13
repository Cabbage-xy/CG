#ifndef _CGRENDERCONTEXT_H_INCLUDED
#define _CGRENDERCONTEXT_H_INCLUDED
#include "Vector2.h"
#include "CGObject.h"
CG_NAMESPACE_ENTER
class CGView;//实验中视图类的基类，如果类的声明中只需要对象指针，则考虑类预声明。
class CGRenderContext : public CGObject
{
public:
	CGRenderContext();
	CGRenderContext(CGView* pView);
	virtual ~CGRenderContext();
	virtual void setView(CGView* pView);
	CGView* getView() const;
	//辅助函数
	HWND hwnd() const { return mHWND; }
	HDC hdc() const { return mHDC; }
	HGLRC hglrc() const { return mHGLRC; }
	int width() const { return mWidth; }
	int height() const { return mHeight; }
public:
	//算法定义
	//直线绘制算法
	static const int aLineCDC = 0; //使用CDC类的直线绘制函数
	static const int aLineDDA = 1; //DDA画线算法
	static const int aLineMidPoint = 2; //中点画线算法
	static const int aLineBresenham = 3; //Bresenham画线算法
	//圆绘制算法
	static const int aCircleCDC = 0; //使用CDC类的画圆函数
	static const int aCrcleMidPoint = 1; //中点画圆算法
	static const int aCircleBresenham = 2; //Bresenham画圆算法
	static const int aCirclePolygon = 3; //多边形逼近画圆
	//椭圆绘制算法
	static const int aEllipseCDC = 0; //使用CDC类的画椭圆函数
	static const int aEllipseMidPoint = 1; //中点画椭圆算法
	//多边形填充算法
	static const int aFillCDC = 0; //使用CDC类的填充函数
	static const int aFillScanlinePolygon = 1; //扫描线多边形填充算法
	//点阵区域填充
	static const int aFillSeedCDC = 0; //使用CDC类的填充函数
	static const int aFillSeedBound4 = 1; //4联通边界种子填充算法
	static const int aFillSeedBound8 = 2; //8联通边界种子填充算法
	static const int aFillSeedFlood4 = 3; //4联通内点种子填充算法
	static const int aFillSeedFlood8 = 4; //8联通内点种子填充算法
	static const int aFillSeedScanline = 5; //扫描线种子填充算法
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
	CGView* mView; //通过视图类可以访问程序主框架中的一些设置，比如当前线型、线宽等。
	HWND mHWND; //通过mView设置
	HDC mHDC; //通过mView设置
	HGLRC mHGLRC;//通过mView设置，三维图形用
	int mWidth, mHeight; //视图客户区（绘图窗口的宽、高）
};
CG_NAMESPACE_EXIT
#endif //_CGRENDERCONTEXT_H_INCLUDED
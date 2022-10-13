#include "pch.h"
#include "CG2DRenderable.h"
CG_NAMESPACE_ENTER
IMPLEMENT_SERIAL(CG2DRenderable, CGRenderable, 1)
CG2DRenderable::CG2DRenderable()
	:CGRenderable(CString("CG2DRenderable"))
	, mPenColor(RGB(0, 0, 0)), mPenWidth(1), mPenStyle(PS_SOLID)
	, mBrushUse(false), mBrushColor(RGB(0, 0, 0)), mBrushIndex(-1)
{
}
CG2DRenderable::CG2DRenderable(const CString & name)
	: CGRenderable(CString(name))
	, mPenColor(RGB(0, 0, 0)), mPenWidth(1), mPenStyle(PS_SOLID)
	, mBrushUse(false), mBrushColor(RGB(0, 0, 0)), mBrushIndex(-1)
{
}
CG2DRenderable::~CG2DRenderable()
{
}
//序列化
void CG2DRenderable::Serialize(CArchive& ar)
{
	CGRenderable::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << mPenColor << mPenWidth << mPenStyle << mBrushUse << mBrushColor << mBrushIndex;
	}
	else
	{
		ar >> mPenColor >> mPenWidth >> mPenStyle >> mBrushUse >> mBrushColor >> mBrushIndex;
	}
}
void CG2DRenderable::setPenColor(COLORREF color)
{
	mPenColor = color;
}
COLORREF CG2DRenderable::penColor() const
{
	return mPenColor;
}
void CG2DRenderable::setPenWidth(int width)
{
	mPenWidth = width;
}
int CG2DRenderable::penWidth() const
{
	return mPenWidth;
}
void CG2DRenderable::setPenStyle(int style)
{
	mPenStyle = style;
}
int CG2DRenderable::penStyle() const
{
	return mPenStyle;
}
void CG2DRenderable::setBrushUse(bool use)
{
	mBrushUse = use;
}
bool CG2DRenderable::brushUse() const
{
	return mBrushUse;
}
void CG2DRenderable::setBrushColor(COLORREF color)
{
	mBrushColor = color;
}
COLORREF CG2DRenderable::brushColor() const
{
	return mBrushColor;
}
void CG2DRenderable::setBrushIndex(int index)
{
	mBrushIndex = index;
}
int CG2DRenderable::brushIndex() const
{
	return mBrushIndex;
}
void CG2DRenderable::Render(CGRenderContext* pRC, CGCamera* pCamera) //绘制对象，使用指定相机
{
	//可根据属性准备绘制工具（画笔画刷）
	//派生类中实现
}
ABox2d& CG2DRenderable::BoundingABox() //AABB包围盒，可用于设置
{
	if (boundsDirty())
	{
		computeBoundingBox();
	}
	return mABox;
}
void CG2DRenderable::computeBoundingBox() //计算包围盒，需要在派生类中实现
{
	//派生类中实现，然后要调用如下函数
	setBoundsDirty(false);
}
bool CG2DRenderable::Picked(const Vec2d& p, double radius) //（二维）是否拾取到
{ //此处只是简单根据包围盒是否相交进行判断，要更精确判定，则应在派生类中重写
	ABox2d abox = BoundingABox();
	ABox2d sbox(p, radius);
	if (abox.intersects(sbox))
		return true;
	return false;
}
CG_NAMESPACE_EXIT
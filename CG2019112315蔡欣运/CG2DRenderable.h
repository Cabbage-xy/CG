#ifndef _CG2DRENDERABLE_H_INCLUDED
#define _CG2DRENDERABLE_H_INCLUDED
#include "AABBox2.h"
#include "CGRenderable.h"
CG_NAMESPACE_ENTER
class CG2DRenderable : public CGRenderable
{
	DECLARE_SERIAL(CG2DRenderable)
public:
	CG2DRenderable();
	CG2DRenderable(const CString& name);
	virtual ~CG2DRenderable();
	//序列化
	virtual void Serialize(CArchive& ar);
	//一般二维图形属性（线宽、线型、颜色）
	void setPenColor(COLORREF color);
	COLORREF penColor() const;
	void setPenWidth(int width);
	int penWidth() const;
	void setPenStyle(int style);
	int penStyle() const;
	//二维封闭图形填充属性
	void setBrushUse(bool use);
	bool brushUse() const;
	void setBrushColor(COLORREF color);
	COLORREF brushColor() const;
	void setBrushIndex(int index);
	int brushIndex() const;
public:
	virtual void Render(CGRenderContext* pRC, CGCamera* pCamera); //绘制对象，使用指定相机
	//二维图形对象包围盒
	ABox2d& BoundingABox(); //AABB包围盒，可用于设置
	virtual void computeBoundingBox(); //计算包围盒，需要在派生类中实现
	virtual bool Picked(const Vec2d& p, double radius); //（二维）是否拾取到
protected:
	COLORREF mPenColor; //轮廓颜色
	int mPenWidth; //轮廓线宽
	int mPenStyle; //轮廓线型
	bool mBrushUse; //是否填充
	COLORREF mBrushColor; //画刷颜色
	int mBrushIndex; //画刷索引
	ABox2d mABox;//轴对齐矩形包围盒，需要根据mBoundsDirty判断是否重新计算
};
CG_NAMESPACE_EXIT
#endif //_CG2DRENDERABLE_H_INCLUDED
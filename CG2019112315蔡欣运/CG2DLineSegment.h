#ifndef _CG2DLINESEGMENT_H_INCLUDED
#define _CG2DLINESEGMENT_H_INCLUDED
#include "Vector2.h"
#include "CG2DRenderable.h"
CG_NAMESPACE_ENTER
class CG2DLineSegment : public CG2DRenderable
{
	DECLARE_SERIAL(CG2DLineSegment)
public:
	CG2DLineSegment();
	CG2DLineSegment(const Vec2d& s, const Vec2d& e); //根据两点构建
	CG2DLineSegment(const Vec2d& s, const Vec2d& dir, double length); //根据起点、方向、长度构建
	CG2DLineSegment(const CG2DLineSegment& other);
	virtual ~CG2DLineSegment();
	//序列化
	virtual void Serialize(CArchive& ar);
public:
	virtual void Render(CGRenderContext* pRC, CGCamera* pCamera); //绘制对象，使用指定相机
	virtual void computeBoundingBox(); //计算包围盒
	virtual bool Picked(const Vec2d& p, double radius); //是否拾取到
protected:
	Vec2d mStart, mEnd; //起点、终点坐标
};
CG_NAMESPACE_EXIT
#endif //_CG2DLINESEGMENT_H_INCLUDED
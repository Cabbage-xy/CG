#ifndef _CG2DRay_H_INCLUDED
#define _CG2DRay_H_INCLUDED
#include "Vector2.h"
#include "CG2DRenderable.h"
CG_NAMESPACE_ENTER
class CG2DRay : public CG2DRenderable
{
	DECLARE_SERIAL(CG2DRay)
public:
	CG2DRay();
	CG2DRay(const Vec2d& s, const Vec2d& e); //根据两点构建
	//CG2DRay(const Vec2d& s, const Vec2d& dir); //根据起点、方向构建
	CG2DRay(const CG2DRay& other);
	virtual ~CG2DRay();
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
#endif //_CG2DRay_H_INCLUDED
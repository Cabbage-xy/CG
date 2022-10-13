#ifndef _CG2DPOLYLINE_H_INCLUDED
#define _CG2DPOLYLINE_H_INCLUDED
#include "Vector2.h"
#include "CG2DRenderable.h"
CG_NAMESPACE_ENTER
class CG2DPolyLine : public CG2DRenderable
{
	DECLARE_SERIAL(CG2DPolyLine)
public:
	CG2DPolyLine();
	CG2DPolyLine(const std::vector<Vec2d>& points); //根据点集按顺序构建
	CG2DPolyLine(const CG2DPolyLine& other);
	virtual ~CG2DPolyLine();
	//序列化
	virtual void Serialize(CArchive& ar);
public:
	virtual void Render(CGRenderContext* pRC, CGCamera* pCamera); //绘制对象，使用指定相机
	virtual void computeBoundingBox(); //计算包围盒
	virtual bool Picked(const Vec2d& p, double radius); //是否拾取到
protected:
	std::vector<Vec2d> mPoints; //折线点坐标集合
};
CG_NAMESPACE_EXIT
#endif //_CG2DPOLYLINE_H_INCLUDED
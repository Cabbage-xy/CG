#ifndef _CG2DPOLYGON_H_INCLUDED
#define _CG2DPOLYGON_H_INCLUDED

#include "Vector2.h"
#include "CG2DRenderable.h"
CG_NAMESPACE_ENTER
class CG2DPolygon : public CG2DRenderable
{
	DECLARE_SERIAL(CG2DPolygon)
public:
	CG2DPolygon();
	CG2DPolygon(const std::vector<Vec2d> points); //根据圆心和半径构建
	CG2DPolygon(const CG2DPolygon& other);
	virtual ~CG2DPolygon();
	//序列化
	virtual void Serialize(CArchive& ar);
public:
	virtual void Render(CGRenderContext* pRC, CGCamera* pCamera); //绘制对象，使用指定相机
protected:
	std::vector<Vec2d> mPoints; //
};
CG_NAMESPACE_EXIT
#endif //_CG2DPOLYGON_H_INCLUDED
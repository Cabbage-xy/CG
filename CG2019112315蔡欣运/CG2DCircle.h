#ifndef _CG2DCIRCLE_H_INCLUDED
#define _CG2DCIRCLE_H_INCLUDED

#include "Vector2.h"
#include "CG2DRenderable.h"
CG_NAMESPACE_ENTER
class CG2DCircle : public CG2DRenderable
{
	DECLARE_SERIAL(CG2DCircle)
public:
	CG2DCircle();
	CG2DCircle(const Vec2d& c, const double r); //根据圆心和半径构建
	CG2DCircle(const Vec2d& m1, const Vec2d& m2); //以直线段为直径构建
	CG2DCircle(const CG2DCircle& other);
	virtual ~CG2DCircle();
	//序列化
	virtual void Serialize(CArchive& ar);
public:
	virtual void Render(CGRenderContext* pRC, CGCamera* pCamera); //绘制对象，使用指定相机
protected:
	Vec2d mCenter; //圆心坐标
	double r;	//半径
};
CG_NAMESPACE_EXIT
#endif //_CG2DCIRCLE_H_INCLUDED
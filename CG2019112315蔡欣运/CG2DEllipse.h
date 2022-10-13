#ifndef _CG2DEllipse_H_INCLUDED
#define _CG2DEllipse_H_INCLUDED

#include "Vector2.h"
#include "CG2DRenderable.h"
CG_NAMESPACE_ENTER
class CG2DEllipse : public CG2DRenderable
{
	DECLARE_SERIAL(CG2DEllipse)
public:
	CG2DEllipse();
	CG2DEllipse(const Vec2d& m1, const Vec2d& m2); //矩形盒对角两点
	CG2DEllipse(const CG2DEllipse& other);
	virtual ~CG2DEllipse();
	//序列化
	virtual void Serialize(CArchive& ar);
public:
	virtual void Render(CGRenderContext* pRC, CGCamera* pCamera); //绘制对象，使用指定相机
protected:
	Vec2d mLeftTop, mRightBottom;
};
CG_NAMESPACE_EXIT
#endif //_CG2DEllipse_H_INCLUDED
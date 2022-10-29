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
public:
	//二维图形对象的几何变换（需要在派生具体类中重写）
	virtual void Translate(double tx, double ty); //平移
	virtual void Rotate(double angle, double cx, double cy); //旋转（逆时针为正，度）
	virtual void Scale(double sx, double sy); //缩放（关于坐标原点缩放）
	virtual void Scale(double sx, double sy, double cx, double cy); //缩放（关于指定参考点缩放）
	virtual void Scale(double sx, double sy, double cx, double cy, const Vec2d& xDir); //缩放（指定参考点，缩放方向）
	virtual void MirrorXAxis(); //关于X轴对称（二维、三维）
	virtual void MirrorYAxis(); //关于Y轴对称（二维、三维）
	virtual void MirrorYeqPosX(); //关于y=x对称（二维、三维）
	virtual void MirrorYeNegPX(); //关于y=-x对称（二维、三维）
	virtual void MirrorOrigin(); //关于原点对称（二维、三维）
	virtual void ShearXAxis(double shx); //沿X轴错切
	virtual void ShearYAxis(double shy); //沿Y轴错切
	virtual void ShearXYAxis(double shx, double shy); //沿X、Y轴错切
	virtual void Transform(const Mat3d& mat); //几何变换（左乘给定矩阵）

protected:
	Vec2d mStart, mEnd; //起点、终点坐标
};
CG_NAMESPACE_EXIT
#endif //_CG2DLINESEGMENT_H_INCLUDED
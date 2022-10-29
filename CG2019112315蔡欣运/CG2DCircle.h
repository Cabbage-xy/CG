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
	virtual void computeBoundingBox(); //计算包围盒
public:
	//二维图形对象的几何变换（需要在派生具体类中重写）
	virtual void Translate(double tx, double ty); //平移
	//virtual void Rotate(double angle, double cx, double cy); //旋转（逆时针为正，度）
	//virtual void Scale(double sx, double sy); //缩放（关于坐标原点缩放）
	//virtual void Scale(double sx, double sy, double cx, double cy); //缩放（关于指定参考点缩放）
	//virtual void Scale(double sx, double sy, double cx, double cy, const Vec2d& xDir); //缩放（指定参考点，缩放方向）
	virtual void MirrorXAxis(); //关于X轴对称（二维、三维）
	virtual void MirrorYAxis(); //关于Y轴对称（二维、三维）
	virtual void MirrorYeqPosX(); //关于y=x对称（二维、三维）
	virtual void MirrorYeNegPX(); //关于y=-x对称（二维、三维）
	virtual void MirrorOrigin(); //关于原点对称（二维、三维）
	//virtual void ShearXAxis(double shx); //沿X轴错切
	//virtual void ShearYAxis(double shy); //沿Y轴错切
	//virtual void ShearXYAxis(double shx, double shy); //沿X、Y轴错切
	//virtual void Transform(const Mat3d& mat); //几何变换（左乘给定矩阵）
protected:
	Vec2d mCenter; //圆心坐标
	double r;	//半径
};
CG_NAMESPACE_EXIT
#endif //_CG2DCIRCLE_H_INCLUDED
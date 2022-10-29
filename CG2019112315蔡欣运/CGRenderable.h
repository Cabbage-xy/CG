#ifndef _CGRENDERABLE_H_INCLUDED
#define _CGRENDERABLE_H_INCLUDED
#include "CGObject.h"
#include "Vector2.h"
#include "Matrix33.h"
CG_NAMESPACE_ENTER
class CGRenderContext;
class CGCamera;
class CGScene; //预声明的场景类
class CGRenderable : public CGObject
{
		DECLARE_SERIAL(CGRenderable)
public:
	CGRenderable();
	CGRenderable(const CString& name);
	virtual ~CGRenderable();
	//序列化
	virtual void Serialize(CArchive& ar);
	//对象被添加到场景，建立与场景的管理（包括子对象也关联到场景）
	void addToScene(CGScene* s);
	CGScene* scene() const;
public:
	virtual void Render(CGRenderContext* pRC, CGCamera* pCamera); //绘制对象，使用指定相机
	//对象状态定义（也可用枚举类型）
	static const int sNormal = 0; //正常状态
	static const int sSelected = 1; //选中状态
	int status() const { return mStatus; }
	void setStatus(int s) { mStatus = s; }
	//对象包围盒是否需要重新计算
	bool boundsDirty() const { return mBoundsDirty; }
	void setBoundsDirty(bool dirty) { mBoundsDirty = dirty; }
	virtual void computeBoundingBox(); //计算对象的包围盒,派生类中重写
	virtual bool Picked(const Vec2d& p, double radius); //（二维）是否拾取到
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
	CGScene* mScene; //对象实例所属的场景，当对象加入场景时自动进行设置。
	int mStatus = 0; //状态
	bool mBoundsDirty = true; //包围盒是否已改变
};
CG_NAMESPACE_EXIT
#endif //_CGRENDERABLE_H_INCLUDED
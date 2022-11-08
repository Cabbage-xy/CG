#include "pch.h"
#include "CGRenderable.h"
#include "Vector2.h"
CG_NAMESPACE_ENTER
IMPLEMENT_SERIAL(CGRenderable, CGObject, 1)
CGRenderable::CGRenderable()
	:CGObject(CString("CGRenderable"))
	, mScene(nullptr), mStatus(sNormal)
{
}
CGRenderable::CGRenderable(const CString& name)
	: CGObject(CString(name))
	, mScene(nullptr), mStatus(sNormal)
{
}
CGRenderable::~CGRenderable()
{
}
void CGRenderable::addToScene(CGScene* s)
{
	mScene = s;
}
CGScene* CGRenderable::scene() const
{
	return mScene;
}
//序列化
void CGRenderable::Serialize(CArchive& ar)
{
	CGObject::Serialize(ar);
}
void CGRenderable::Render(CGRenderContext* pRC, CGCamera* pCamera) //绘制对象，使用指定相机
{
	//派生类中实现
}
void CGRenderable::computeBoundingBox() //计算对象的包围盒
{
	//派生类中实现
}
bool CGRenderable::Picked(const Vec2d& p, double radius) //（二维）是否拾取到
{
	//派生类中实现
	return false;
}
//二维图形对象的几何变换
void CGRenderable::Translate(double tx, double ty) //平移
{
	//派生类中实现
}
void CGRenderable::Rotate(double angle, double cx, double cy) //旋转（逆时针为正，度）
{
	//派生类中实现
}
void CGRenderable::Scale(double sx, double sy) //缩放
{
	//派生类中实现
}
void CGRenderable::Scale(double sx, double sy, double cx, double cy) //缩放
{
	//派生类中实现
}
void CGRenderable::Scale(double sx, double sy, double cx, double cy, const Vec2d& xDir) //缩放
{
	//派生类中实现
}
void CGRenderable::MirrorXAxis() //关于X轴对称（二维、三维）
{
	//派生类中实现
}
void CGRenderable::MirrorYAxis() //关于Y轴对称（二维、三维）
{
	//派生类中实现
}
void CGRenderable::MirrorYeqPosX() //关于y=x对称（二维、三维）
{
	//派生类中实现
}
void CGRenderable::MirrorYeNegPX() //关于y=-x对称（二维、三维）
{
	//派生类中实现
}
void CGRenderable::MirrorOrigin() //关于原点对称（二维、三维）
{
	//派生类中实现
}
void CGRenderable::ShearXAxis(double shx) //沿X轴错切
{
	//派生类中实现
}
void CGRenderable::ShearYAxis(double shy) //沿Y轴错切
{
	//派生类中实现
}
void CGRenderable::ShearXYAxis(double shx, double shy) //沿X、Y轴错切
{
	//派生类中实现
}
void CGRenderable::Transform(const Mat3d& mat) //几何变换（左乘给定矩阵）
{
	//派生类中实现
}
//给定裁剪窗口（矩形范围）左下右上进行采集，裁剪结果放入result数组。
bool CGRenderable::Cliped(double xl, double yb, double xr, double yt, CGCamera* pCamera,
	CTypedPtrArray<CObArray, CGRenderable*>& result)
{
	return false;
}
CG_NAMESPACE_EXIT
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
CG_NAMESPACE_EXIT
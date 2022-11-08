#include "pch.h"
#include "CGDI2DCamera.h"
CG_NAMESPACE_ENTER
IMPLEMENT_SERIAL(CGDI2DCamera, CGCamera, 1)
CGDI2DCamera::CGDI2DCamera()
	:CGCamera(CString("CGDI2DCamera"))
{
}
CGDI2DCamera::CGDI2DCamera(const CString& name)
	: CGCamera(CString(name))
{
}
void CGDI2DCamera::Serialize(CArchive& ar)
{
	CGCamera::Serialize(ar);
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}
void CGDI2DCamera::InitCamera()
{
}
//世界坐标系转换到视口（二维）
Vec2i CGDI2DCamera::WorldtoViewPort(const Vec2d& p)
{
	//此处简单映射实现用于测试，画布坐标系设在客户区左下角，x向右，y向上。
	//观察窗口与视口一样的大小。视口与客户区重叠
	//return Vec2i(int(p.x()), int(-p.y()) + mClienRect.height());
	//画布坐标系在客户区中心，x向右，y向上。
	return Vec2i(int(p.x()+ mClienRect.width()/2.0), int(-p.y() + mClienRect.height()/2.0));
}
//视口转换到世界坐标系（二维）
Vec2d CGDI2DCamera::ViewPorttoWorld(const Vec2i& p)
{
	//此处简单映射实现用于测试，画布坐标系设在客户区左下角，x向右，y向上。
	//观察窗口与视口一样的大小。视口与客户区重叠
	//return Vec2d(p.x(), double(mClienRect.height()) - p.y());
	//画布坐标系在客户区中心，x向右，y向上。
	return Vec2d(p.x() - mClienRect.width()/2.0, mClienRect.height()/2.0 - p.y());
}
CG_NAMESPACE_EXIT

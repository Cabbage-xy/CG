#include "pch.h"
#include "CGCamera.h"
CG_NAMESPACE_ENTER
IMPLEMENT_SERIAL(CGCamera, CGObject, 1)
CGCamera::CGCamera()
	:CGObject(CString("CGCamera"))
{
}
CGCamera::CGCamera(const CString& name)
	: CGObject(CString(name))
{
}
void CGCamera::Serialize(CArchive& ar)
{
	CGObject::Serialize(ar);
	mViewPort.Serialize(ar);
	if (ar.IsStoring())
	{
		ar << mClienRect.minCorner().x() << mClienRect.minCorner().y() << mClienRect.maxCorner().x() <<
			mClienRect.maxCorner().y();
	}
	else
	{
		ar >> mClienRect.minCorner().x() >> mClienRect.minCorner().y() >> mClienRect.maxCorner().x() >>
			mClienRect.maxCorner().y();
	}
}
void CGCamera::InitCamera()
{
	//派生类中实现
}
void CGCamera::setViewPortBox(int xl, int yb, int xr, int yt)
{
	mViewPort.set(xl, yb, xr, yt);
}
void CGCamera::setViewPort(const CGViewPort& vp)
{
	//要保证xl<xr, yb<yt
	mViewPort.set(vp.box().minCorner().x(), vp.box().minCorner().y(), vp.box().maxCorner().x(),
		vp.box().maxCorner().y());
	//是否要保持与观察窗口的等比例？
}
void CGCamera::setClientRect(int xl, int yb, int xr, int yt)
{
	//要保证xl<xr, yb<yt
	if (xl < xr)
	{
		mClienRect.minCorner().x() = xl;
		mClienRect.maxCorner().x() = xr;
	}
	else
	{
		mClienRect.minCorner().x() = xr;
		mClienRect.maxCorner().x() = xl;
	}
	if (yb < yt)
	{
		mClienRect.minCorner().y() = yb;
		mClienRect.maxCorner().y() = yt;
	}
	else
	{
		mClienRect.minCorner().y() = yt;
		mClienRect.maxCorner().y() = yb;
	}
}
void CGCamera::setClientRect(const ABox2i& rc)
{
	mClienRect = rc;
}
//世界坐标系转换到视口（二维）
Vec2i CGCamera::WorldtoViewPort(const Vec2d& p)
{
	//派生类中实现
	return Vec2i(0, 0);
}
//视口转换到世界坐标系（二维）
Vec2d CGCamera::ViewPorttoWorld(const Vec2i& p)
{
	//派生类中实现
	return Vec2d(0, 0);
}
CG_NAMESPACE_EXIT
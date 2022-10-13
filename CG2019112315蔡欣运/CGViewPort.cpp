#include "pch.h"
#include "CGViewPort.h"
CG_NAMESPACE_ENTER
IMPLEMENT_SERIAL(CGViewPort, CGObject, 1)
CGViewPort::CGViewPort()
	:CGObject(CString("视口"))
{
	set(0, 0, 1, 1);
}
CGViewPort::CGViewPort(const CString& name)
	: CGObject(name)
{
	set(0, 0, 1, 1);
}
CGViewPort::CGViewPort(const CGViewPort& vp)
	: CGObject(vp.name()), mViewPortBox(vp.box())
{
}
CGViewPort::CGViewPort(int xl, int yb, int xr, int yt)
	: CGObject(CString("视口"))
{
	set(xl, yb, xr, yt);
}
CGViewPort::CGViewPort(int xr, int yt)
	: CGObject(CString("视口"))
{
	set(0, 0, xr, yt);
}
void CGViewPort::Serialize(CArchive& ar)
{
	CGObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << mViewPortBox.minCorner().x() << mViewPortBox.minCorner().y() <<
			mViewPortBox.maxCorner().x() << mViewPortBox.maxCorner().y();
	}
	else
	{
		ar >> mViewPortBox.minCorner().x() >> mViewPortBox.minCorner().y() >>
			mViewPortBox.maxCorner().x() >> mViewPortBox.maxCorner().y();
	}
}
void CGViewPort::set(int xl, int yb, int xr, int yt)
{
	//要保证xl<xr, yb<yt
	if (xl < xr)
	{
		mViewPortBox.minCorner().x() = xl;
		mViewPortBox.maxCorner().x() = xr;
	}
	else
	{
		mViewPortBox.minCorner().x() = xr;
		mViewPortBox.maxCorner().x() = xl;
	}
	if (yb < yt)
	{
		mViewPortBox.minCorner().y() = yb;
		mViewPortBox.maxCorner().y() = yt;
	}
	else
	{
		mViewPortBox.minCorner().y() = yt;
		mViewPortBox.maxCorner().y() = yb;
	}
}
void CGViewPort::setMinCorner(int xl, int yb)
{
	//要保证xl<xr, yb<yt
	if (xl < mViewPortBox.maxCorner().x())
	{
		mViewPortBox.minCorner().x() = xl;
	}
	else
	{
		mViewPortBox.minCorner().x() = mViewPortBox.maxCorner().x();
		mViewPortBox.maxCorner().x() = xl;
	}
	if (yb < mViewPortBox.maxCorner().y())
	{
		mViewPortBox.minCorner().y() = yb;
	}
	else
	{
		mViewPortBox.minCorner().y() = mViewPortBox.maxCorner().y();
		mViewPortBox.maxCorner().y() = yb;
	}
}
void CGViewPort::setMaxCorner(int xr, int yt)
{
	//要保证xl<xr, yb<yt
	if (mViewPortBox.minCorner().x() < xr)
	{
		mViewPortBox.maxCorner().x() = xr;
	}
	else
	{
		mViewPortBox.maxCorner().x() = mViewPortBox.minCorner().x();
		mViewPortBox.minCorner().x() = xr;
	}
	if (mViewPortBox.minCorner().y() < yt)
	{
		mViewPortBox.maxCorner().y() = yt;
	}
	else
	{
		mViewPortBox.maxCorner().y() = mViewPortBox.minCorner().y();
		mViewPortBox.minCorner().y() = yt;
	}
}
void CGViewPort::setLeft(int xl)
{
	//要保证xl<xr, yb<yt
	if (xl < mViewPortBox.maxCorner().x())
	{
		mViewPortBox.minCorner().x() = xl;
	}
	else
	{
		mViewPortBox.minCorner().x() = mViewPortBox.maxCorner().x();
		mViewPortBox.maxCorner().x() = xl;
	}
}
void CGViewPort::setBottom(int yb)
{
	if (yb < mViewPortBox.maxCorner().y())
	{
		mViewPortBox.minCorner().y() = yb;
	}
	else
	{
		mViewPortBox.minCorner().y() = mViewPortBox.maxCorner().y();
		mViewPortBox.maxCorner().y() = yb;
	}
}
void CGViewPort::setRight(int xr)
{
	//要保证xl<xr, yb<yt
	if (mViewPortBox.minCorner().x() < xr)
	{
		mViewPortBox.maxCorner().x() = xr;
	}
	else
	{
		mViewPortBox.maxCorner().x() = mViewPortBox.minCorner().x();
		mViewPortBox.minCorner().x() = xr;
	}
}
void CGViewPort::setTop(int yt)
{
	if (mViewPortBox.minCorner().y() < yt)
	{
		mViewPortBox.maxCorner().y() = yt;
	}
	else
	{
		mViewPortBox.maxCorner().y() = mViewPortBox.minCorner().y();
		mViewPortBox.minCorner().y() = yt;
	}
}
CG_NAMESPACE_EXIT

#include "pch.h"
#include "CGCamera.h"
CG_NAMESPACE_ENTER
IMPLEMENT_SERIAL(CGCamera, CGObject, 1)
CGCamera::CGCamera()
	:CGObject(CString("CGCamera"))
	, mViewPort(0, 0, 1, 1) //需要根据具体设置进行修改
	, mClienRect(Vec2i(0, 0), Vec2i(1, 1), 0) //需要根据具体设置进行修改
{
	InitCamera();
}
CGCamera::CGCamera(const CString& name)
	: CGObject(CString(name))
	, mViewPort(0, 0, 1, 1) //需要根据具体设置进行修改
	, mClienRect(Vec2i(0, 0), Vec2i(1, 1), 0) //需要根据具体设置进行修改
{
	InitCamera();
}

void CGCamera::InitCamera()
{
	mLeft = -1000.0;
	mBottom = -1000.0;
	mRight = 1000.0;
	mTop = 1000.0;
	mEyeX = 0.0;
	mEyeY = 0.0;
	mUpX = 0.0;
	mUpY = 1.0;
	//派生类中实现其他初始化
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
//观察窗口宽度与视口宽度的比例
double CGCamera::WidthFactorWindowtoViewPort()
{
	return (mRight - mLeft) / mViewPort.width();
}
//观察窗口高度与视口高度的比例
double CGCamera::HeightFactorWindowtoViewPort()
{
	return (mTop - mBottom) / mViewPort.height();
}

//设置相机位置（二维、三维）
void CGCamera::setEye(double eyex, double eyey, double eyez)
{
	mEyeX = eyex;
	mEyeY = eyey;
	mEyeZ = eyez;
}
//设置相机向上方向（二维、三维）
void CGCamera::setUp(double upx, double upy, double upz)
{
	mUpX = upx;
	mUpY = upy;
	mUpZ = upz;
}

//客户区（二维、三维）
void CGCamera::setClientRect(int cx, int cy)
{
	if (cx < 1 || cy < 1)
		return;
	mClienRect.minCorner().x() = 0;
	mClienRect.minCorner().y() = 0;
	mClienRect.maxCorner().x() = cx;
	mClienRect.maxCorner().y() = cy;
	ClientResized(cx, cy); //窗口视口相应变化
}
//客户区大小发生变换时，调整观察窗口与视口，并使高宽比相同，不产生变形
void CGCamera::ClientResized(int cx, int cy)
{
	//如果视口与客户区一样大
	setViewPortBox(0, 0, cx, cy);
	//视口大小变化后要更新窗口保持比例一致？
	Zoom(Vec2d(Left(), Bottom()), Vec2d(Right(), Top()));
}
//相机控制（观察控制）
void CGCamera::Move(double tx, double ty) //移动观察坐标系（二维）
{
	//派生类中实现
}
void CGCamera::Zoom(double ratio) //观察窗口缩放
{
	//派生类中实现
}
void CGCamera::Zoom(const Vec2d& lb, const Vec2d& rt) //观察窗口缩放
{
	//派生类中实现
}
void CGCamera::Rotate(double degree) //旋转观察坐标系（绕坐标系原点）
{
	//派生类中实现
}
void CGCamera::Reset() //重置到默认参数
{
	//派生类中实现
}
//二维图形观察变换（世界坐标系到观察坐标系）（二维）
Vec2d CGCamera::WCStoVCS(const Vec2d& p)
{
	//派生类中实现
	return Vec2d(0, 0);
}
//二维图形窗视变换（观察坐标系到规范化设备坐标系）（二维）（实验中使用虚拟设备坐标系代替规范化设备坐标系）
Vec2d CGCamera::VCStoNCS(const Vec2d& p)
{
	//派生类中实现
	return Vec2d(0, 0);
}
//二维图形视口变换（规范化设备坐标系到设备坐标系）（二维）（实验中使用虚拟设备坐标系代替规范化设备坐标系）
Vec2i CGCamera::NCStoDCS(const Vec2d& p)
{
	//派生类中实现
	return Vec2i(0, 0);
}
//设备坐标系到规范化设备坐标系（二维）（实验中使用虚拟设备坐标系代替规范化设备坐标系）
Vec2d CGCamera::DCStoNCS(const Vec2i& p)
{
	//派生类中实现
	return Vec2d(0, 0);
}
//规范化设备坐标系到观察坐标系（二维）（实验中使用虚拟设备坐标系代替规范化设备坐标系）
Vec2d CGCamera::NCStoVCS(const Vec2d& p)
{
	//派生类中实现
	return Vec2d(0, 0);
}
//观察坐标系到世界坐标系
Vec2d CGCamera::VCStoWCS(const Vec2d& p)
{
	//派生类中实现
	return Vec2d(0, 0);
}
CG_NAMESPACE_EXIT
#include "pch.h"
#include "CGDI2DCamera.h"
#include "Vector3.h"
#include "Matrix33.h"
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
	CGCamera::InitCamera();
}
//世界坐标系转换到视口（二维）
Vec2i CGDI2DCamera::WorldtoViewPort(const Vec2d& p)
{
	//此处简单映射实现用于测试，画布坐标系设在客户区左下角，x向右，y向上。
	//观察窗口与视口一样的大小。视口与客户区重叠
	//return Vec2i(int(p.x()), int(-p.y()) + mClienRect.height());
	//画布坐标系在客户区中心，x向右，y向上。
	//return Vec2i(int(p.x()+ mClienRect.width()/2.0), int(-p.y() + mClienRect.height()/2.0));
	Vec2d v(p);
	v = WCStoVCS(v);//世界坐标系到观察坐标系
	v = VCStoNCS(v);//观察坐标系到虚拟设备坐标系
	return NCStoDCS(v);//虚拟设备坐标系到设备坐标系
}
//视口转换到世界坐标系（二维）
Vec2d CGDI2DCamera::ViewPorttoWorld(const Vec2i& p)
{
	//此处简单映射实现用于测试，画布坐标系设在客户区左下角，x向右，y向上。
	//观察窗口与视口一样的大小。视口与客户区重叠
	//return Vec2d(p.x(), double(mClienRect.height()) - p.y());
	//画布坐标系在客户区中心，x向右，y向上。
	//return Vec2d(p.x() - mClienRect.width()/2.0, mClienRect.height()/2.0 - p.y());
	Vec2d v = DCStoNCS(p);//虚拟设备坐标系到设备坐标系
	v = NCStoVCS(v);//观察坐标系到虚拟设备坐标系
	return VCStoWCS(v);//世界坐标系到观察坐标系
}

//相机控制（观察控制）
void CGDI2DCamera::Move(double tx, double ty) //移动观察坐标系（二维）
{
	mEyeX += tx;
	mEyeY += ty;
}
//观察窗口缩放（两个方向同比例缩放，窗口宽高比与视口宽高比相同）
void CGDI2DCamera::Zoom(double ratio)
{
	if (ratio < 0)
		return;
	double xc = (mLeft + mRight) / 2.0;
	double yc = (mBottom + mTop) / 2.0;
	double w = (mRight - mLeft) / 2.0;
	double h = (mTop - mBottom) / 2.0;
	mLeft = xc - w * ratio;
	mRight = xc + w * ratio;
	mBottom = yc - h * ratio;
	mTop = yc + h * ratio;
}

//观察窗口缩放（窗口宽高比与视口宽高比相同）。用于交互获取观察窗口（在客户区中框出）
void CGDI2DCamera::Zoom(const Vec2d& lb, const Vec2d& rt)
{
	////视口宽高比
	//double aspect = double(mViewPort.width()) / double(mViewPort.height());
	//double h = rt.y() - lb.y();
	////double w = rt.x() - lb.x();
	//double w = aspect * h;//以高度为基准，保持观察窗口与视口的高宽比相同，使观察效果不变形
	//mBottom = lb.y();
	//mTop = rt.y();
	//mLeft = -w / 2;
	//mRight = w / 2;
	
	//视口宽高比
	double aspectViewPort = double(mViewPort.width()) / double(mViewPort.height());
	//防止为0
	if (rt.y() - lb.y() == 0) return;
	double aspectZoomBox = abs((rt.x() - lb.x()) / (rt.y() - lb.y()));

	double w, h;
	if (aspectViewPort > aspectZoomBox)
	{
		h = abs(rt.y() - lb.y());
		w = aspectViewPort * h; //以高度为基准，保持观察窗口与视口的高宽比相同，使观察效果不变形
	}
	else
	{
		w = abs(rt.x() - lb.x());
		h = w / aspectViewPort; //以宽度为基准，保持观察窗口与视口的高宽比相同，使观察效果不变形
	}
	mBottom = -h / 2;
	mTop = h / 2;
	mLeft = -w / 2;
	mRight = w / 2;
}

void CGDI2DCamera::Rotate(double degree) //旋转观察坐标系（绕世界坐标系原点，逆时针方向为正，单位：度）
{
	Mat3d mat = Mat3d::getRotation(degree);
	Vec3d vec = operator *(mat, Vec3d(mUpX, mUpY, 1)); //观察坐标系Y轴向量的齐次坐标表示（mUpX,mUpY, 1）
	mUpX = vec.x();
	mUpY = vec.y();
}
void CGDI2DCamera::Reset() //重置到默认参数
{
	//此处仅调整观察坐标系，保持观察窗口参数
	mEyeX = 0.0;
	mEyeY = 0.0;
	mUpX = 0.0;
	mUpY = 1.0;
}
//二维图形观察变换（世界坐标系到观察坐标系）（二维） ，移动观察坐标系
Vec2d CGDI2DCamera::WCStoVCS(const Vec2d& p)
{
	//世界坐标原点在窗口中心
	int x = p.x() - mEyeX; //转换为观察坐标
	int y = p.y() - mEyeY;
	Vec2d v(x, y);
	double degrees = atan(mUpX / mUpY); //观察坐标系与世界坐标系的夹角
	Mat3d mat = Mat3d::getRotation(degrees);//世界坐标系转换为观察坐标系，观察坐标系需进行逆时针旋转
	v = operator*(mat, v);
	return v;
}

//二维图形窗视变换（观察坐标系到虚拟设备坐标系）（二维）（实验中使用虚拟设备坐标系代替规范化设备坐标系）
Vec2d CGDI2DCamera::VCStoNCS(const Vec2d& p)
{
	return Vec2d(p.x() / WidthFactorWindowtoViewPort(), p.y() / HeightFactorWindowtoViewPort());
}

//二维图形视口变换（虚拟设备坐标系到设备坐标系）（二维）（实验中使用虚拟设备坐标系代替规范化设备坐标系）
Vec2i CGDI2DCamera::NCStoDCS(const Vec2d& p)
{
	Vec2i v(p.x() + (double)mClienRect.width() / 2, -p.y() + (double)mClienRect.height() / 2); //横坐标不变，纵坐标翻转
	return v;
}
//设备坐标系到虚拟设备坐标系（二维）（实验中使用虚拟设备坐标系代替规范化设备坐标系）
Vec2d CGDI2DCamera::DCStoNCS(const Vec2i& p)
{
	Vec2d v((p.x() - (double)mClienRect.width() / 2), (-p.y() + (double)mClienRect.height() / 2));
	return v;
}
//虚拟设备坐标系到观察坐标系（二维）（实验中使用虚拟设备坐标系代替规范化设备坐标系）
Vec2d CGDI2DCamera::NCStoVCS(const Vec2d& p)
{
	return Vec2d(p.x() * WidthFactorWindowtoViewPort(), p.y() * HeightFactorWindowtoViewPort());
}
//观察坐标系到世界坐标系（二维）
Vec2d CGDI2DCamera::VCStoWCS(const Vec2d& p)
{
	int x = p.x() + mEyeX; //转换为观察坐标
	int y = p.y() + mEyeY;
	Vec2d v(x, y);
	double degrees = atan(mUpX / mUpY); //观察坐标系与世界坐标系的夹角
	Mat3d mat = Mat3d::getRotation(-degrees);//观察坐标系转换为世界坐标系，世界坐标系需进行顺时针旋转
	v = operator*(mat, v);
	return v;
}
CG_NAMESPACE_EXIT

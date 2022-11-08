#ifndef _CGCAMERA_H_INCLUDED
#define _CGCAMERA_H_INCLUDED
#include "AABBox2.h"
#include "CGViewPort.h"
#include "Vector2.h"
CG_NAMESPACE_ENTER
class CGCamera : public CGObject
{
	DECLARE_SERIAL(CGCamera)
public:
	CGCamera();
	CGCamera(const CString& name);
	virtual ~CGCamera() = default;
	//序列化
	virtual void Serialize(CArchive& ar);
	//初始化相机
	virtual void InitCamera();
	//视口（二维、三维）
	virtual void setViewPortBox(int xl, int yb, int xr, int yt);
	virtual void setViewPort(const CGViewPort& vp);
	//客户区（二维、三维）
	virtual void setClientRect(int xl, int yb, int xr, int yt);
	virtual void setClientRect(const ABox2i& rc);
	//世界坐标系转换到视口（二维）
	virtual Vec2i WorldtoViewPort(const Vec2d& p);
	//视口转换到世界坐标系（二维）
	virtual Vec2d ViewPorttoWorld(const Vec2i & p);
	//观察窗口及观察体
	double Left() const { return mLeft; }
	double Bottom() const { return mBottom; }
	double Right() const { return mRight; }
	double Top() const { return mTop; }

	//观察坐标系
	double EyeX() const { return mEyeX; }
	double EyeY() const { return mEyeY; }
	double EyeZ() const { return mEyeZ; }
	double UpX() const { return mUpX; }
	double UpY() const { return mUpY; }
	double UpZ() const { return mUpZ; }

	//虚拟设备坐标系中视口参数，与实际视口左右一直，上下边界计算依赖客户区与视口
	int NCSViewPortLeft() const { return mViewPort.left(); }
	int NCSViewPortBottom() const { return mViewPort.bottom(); }
	int NCSViewPortRight() const { return mViewPort.right(); }
	int NCSViewPortTop() const { return mViewPort.top(); }

	//观察窗口高度与视口高度的比例
	double WidthFactorWindowtoViewPort();
	//观察窗口高度与视口高度的比例
	double HeightFactorWindowtoViewPort();

	//设置相机位置（二维、三维）
	void setEye(double eyex, double eyey, double eyez = 0);
	//设置相机向上方向（二维、三维）
	void setUp(double upx, double upy, double upz = 0);

	//客户区（二维、三维）
	virtual void setClientRect(int cx, int cy);
	//客户区大小发生变换时，调整观察窗口与视口，并使高宽比相同，不产生变形
	void ClientResized(int cx, int cy);

	virtual void Move(double tx, double ty); //移动观察坐标系（二维）
	virtual void Zoom(double ratio); //观察窗口缩放（二维），两个方向同比例缩放，参数应大于0。
	virtual void Zoom(const Vec2d& lb, const Vec2d& rt); //观察窗口缩放（二维）（指定窗口参数，但要保证两方向同比例缩放）
	virtual void Rotate(double degree); //旋转观察坐标系（绕坐标系原点，逆时针方向为正，单位：度）（二维）
	virtual void Reset(); //重置到默认参数（二维）
public:
	//直线段裁剪算法（使用交互命令构造裁剪窗口对选中的线段进行裁剪）
	//Cohen-Sutherland（编码）直线段裁剪
	//xl、yb、xr、yt对应裁剪窗口的左、下、右、上。s、e输入线段起点终点，rs、re裁剪结果，无，则返回false，有则返回true
	virtual bool CohenSutherlandLineClip(double xl, double yb, double xr, double yt, const Vec2d& s, const Vec2d& e, Vec2d& rs, Vec2d& re);
	//其他裁剪算法（选做）
	//中点分割直线段裁剪算法
	//bool MidpointSplitLineClip(double xl, double yb, double xr, double yt, const Vec2d& s, const Vec2d& e, Vec2d& rs, Vec2d& re);
	//梁-Barsky直线段裁剪算法
	//bool LiangBarskyLineClip(double xl, double yb, double xr, double yt, const Vec2d& s, const Vec2d& e, Vec2d& rs, Vec2d& re);
	//多边形裁剪算法（使用交互命令构造裁剪窗口对选中的多边形进行裁剪）
	//Sutherland-Hodgman(逐边)多边形裁剪算法，输入矩形裁剪窗口、被裁剪多边形，输出一个结果多边形
	//bool SutherlandHodgmanPolygonClip(double xl, double yb, double xr, double yt, const Vec2dArray& in, Vec2dArray& out);
	//Werler-Atherton(双边)多边形裁剪算法，输入裁剪窗口多边形、被裁剪多边形，可能输出多个结果多边形
	//bool WerlerAthertonPolygonClip(const Vec2dArray& win, const Vec2dArray& in, std::vector<Vec2dArray>& out);
protected:
	//变换支持函数
	//二维图形观察变换（世界坐标系到观察坐标系）（二维）
	virtual Vec2d WCStoVCS(const Vec2d& p);
	//二维图形窗视变换（观察坐标系到规范化设备坐标系）（二维）（实验中使用虚拟设备坐标系代替规范化设备坐标系）
	virtual Vec2d VCStoNCS(const Vec2d& p);
	//二维图形视口变换（规范坐标系到设备坐标系）（二维）（实验中使用虚拟设备坐标系代替规范化设备坐标系）
	virtual Vec2i NCStoDCS(const Vec2d& p);
	//设备坐标系到规范化设备坐标系（二维）（实验中使用虚拟设备坐标系代替规范化设备坐标系）
	virtual Vec2d DCStoNCS(const Vec2i& p);
	//规范化设备坐标系到观察坐标系（二维）（实验中使用虚拟设备坐标系代替规范化设备坐标系）
	virtual Vec2d NCStoVCS(const Vec2d& p);
	//观察坐标系到世界坐标系（二维）
	virtual Vec2d VCStoWCS(const Vec2d& p);
protected:
	CGViewPort mViewPort; //对应视口，在设备坐标系（客户区）中定义
	ABox2i mClienRect; //视图客户区矩形
	double mLeft, mBottom, mRight, mTop; //观察窗口（在观察坐标系中定义）矩形的左、下、右、上（默认0,0,1,1）
	double mEyeX, mEyeY, mEyeZ; //相机位置（默认0,0,0），二维中用到了x，y，表示观察坐标系原点在世界坐标系中的位置，mEyeZ用于三维，二维中默认为0
	double mUpX, mUpY, mUpZ; //向上方向（默认0,1,0），二维中用到x，y，表示观察坐标系Y轴的方向矢量，mUpZ用于三维，二维中默认为0
};
CG_NAMESPACE_EXIT
#endif //_CGCAMERA_H_INCLUDED
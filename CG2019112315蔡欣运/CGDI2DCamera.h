#ifndef _CGDI2DCAMERA_H_INCLUDED
#define _CGDI2DCAMERA_H_INCLUDED
#include "CGCamera.h"
CG_NAMESPACE_ENTER
class CGDI2DCamera : public CGCamera
{
	DECLARE_SERIAL(CGDI2DCamera)
public:
	CGDI2DCamera();
	CGDI2DCamera(const CString& name);
	virtual ~CGDI2DCamera() = default;
	//序列化
	virtual void Serialize(CArchive& ar);
	//初始化相机
	virtual void InitCamera();
	//世界坐标系转换到视口（二维）
	virtual Vec2i WorldtoViewPort(const Vec2d& p);
	//视口转换到世界坐标系（二维）
	virtual Vec2d ViewPorttoWorld(const Vec2i& p);

public://相机操作
	//相机控制（观察控制）
	virtual void Move(double tx, double ty); //移动观察坐标系（二维）
	virtual void Zoom(double ratio); //观察窗口缩放（二维）
	virtual void Zoom(const Vec2d& lb, const Vec2d& rt); //观察窗口缩放（二维）
	virtual void Rotate(double degree); //旋转观察坐标系（绕坐标系原点）（二维）
	virtual void Reset(); //重置到默认参数（二维）
public:
	bool CohenSutherlandLineClip(double xl, double yb, double xr, double yt, const Vec2d& s, const Vec2d& e, Vec2d& rs, Vec2d& re) override;


protected://观察变换
//二维图形观察变换（世界坐标系到观察坐标系）（二维）
	virtual Vec2d WCStoVCS(const Vec2d& p);
	//二维图形窗视变换（观察坐标系到规范化设备坐标系）（二维）（实验中使用虚拟设备坐标系代替规范化设备坐标系）
	virtual Vec2d VCStoNCS(const Vec2d& p);
	//二维图形视口变换（规范化设备坐标系到设备坐标系）（二维）（实验中使用虚拟设备坐标系代替规范化设备坐标系）
	virtual Vec2i NCStoDCS(const Vec2d& p);
	//设备坐标系到规范化设备坐标系（二维）（实验中使用虚拟设备坐标系代替规范化设备坐标系）
	virtual Vec2d DCStoNCS(const Vec2i& p);
	//规范化设备坐标系到观察坐标系（二维）（实验中使用虚拟设备坐标系代替规范化设备坐标系）
	virtual Vec2d NCStoVCS(const Vec2d& p);
	//观察坐标系到世界坐标系（二维）
	virtual Vec2d VCStoWCS(const Vec2d& p);
protected:
};
CG_NAMESPACE_EXIT
#endif //_CGDI2DCAMERA_H_INCLUDED
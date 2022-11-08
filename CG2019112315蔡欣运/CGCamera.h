#ifndef _CGCAMERA_H_INCLUDED
#define _CGCAMERA_H_INCLUDED
#include "AABBox2.h"
#include "CGViewPort.h"
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
protected:
	CGViewPort mViewPort; //对应视口，在设备坐标系（客户区）中定义
	ABox2i mClienRect; //视图客户区矩形
};
CG_NAMESPACE_EXIT
#endif //_CGCAMERA_H_INCLUDED
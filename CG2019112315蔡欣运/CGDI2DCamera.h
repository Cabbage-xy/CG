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
protected:
};
CG_NAMESPACE_EXIT
#endif //_CGDI2DCAMERA_H_INCLUDED
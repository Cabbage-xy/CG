#ifndef _CGDI2DSCENE_H_INCLUDED
#define _CGDI2DSCENE_H_INCLUDED
#include "CGScene.h"
CG_NAMESPACE_ENTER
class CGDI2DScene : public CGScene
{
	DECLARE_SERIAL(CGDI2DScene)
public:
	CGDI2DScene();
	virtual ~CGDI2DScene();
	//序列化
	virtual void Serialize(CArchive& ar);
	//渲染场景到指定客户区（依赖CGDI2DView）
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);
	//二维场景包围盒计算
	virtual ABox2d BoundingABox();
	//给定裁剪窗口（矩形范围）左下右上进行采集，裁剪结果不为空时返回true。
	virtual bool Clip(double xl, double yb, double xr, double yt, CGCamera* pCamera);
};
CG_NAMESPACE_EXIT
#endif //_CGDI2DSCENE_H_INCLUDED
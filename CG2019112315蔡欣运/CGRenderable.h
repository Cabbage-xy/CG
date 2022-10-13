#ifndef _CGRENDERABLE_H_INCLUDED
#define _CGRENDERABLE_H_INCLUDED
#include "CGObject.h"
#include "Vector2.h"
CG_NAMESPACE_ENTER
class CGRenderContext;
class CGCamera;
class CGScene; //预声明的场景类
class CGRenderable : public CGObject
{
		DECLARE_SERIAL(CGRenderable)
public:
	CGRenderable();
	CGRenderable(const CString& name);
	virtual ~CGRenderable();
	//序列化
	virtual void Serialize(CArchive& ar);
	//对象被添加到场景，建立与场景的管理（包括子对象也关联到场景）
	void addToScene(CGScene* s);
	CGScene* scene() const;
public:
	virtual void Render(CGRenderContext* pRC, CGCamera* pCamera); //绘制对象，使用指定相机
	//对象状态定义（也可用枚举类型）
	static const int sNormal = 0; //正常状态
	static const int sSelected = 1; //选中状态
	int status() const { return mStatus; }
	void setStatus(int s) { mStatus = s; }
	//对象包围盒是否需要重新计算
	bool boundsDirty() const { return mBoundsDirty; }
	void setBoundsDirty(bool dirty) { mBoundsDirty = dirty; }
	virtual void computeBoundingBox(); //计算对象的包围盒,派生类中重写
	virtual bool Picked(const Vec2d& p, double radius); //（二维）是否拾取到
protected:
	CGScene* mScene; //对象实例所属的场景，当对象加入场景时自动进行设置。
	int mStatus = 0; //状态
	bool mBoundsDirty = true; //包围盒是否已改变
};
CG_NAMESPACE_EXIT
#endif //_CGRENDERABLE_H_INCLUDED
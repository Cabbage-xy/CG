#ifndef _CGSCENE_H_INCLUDED
#define _CGSCENE_H_INCLUDED
#include "Vector2.h"
#include "AABBox2.h"
#include "CGObject.h"
CG_NAMESPACE_ENTER
class CGRenderable;
class CGCamera;
class CGRenderContext;
class CGScene : public CGObject
{
	DECLARE_SERIAL(CGScene)
public:
	CGScene();
	virtual ~CGScene();
	virtual void Serialize(CArchive& ar);
	//图形对象
	bool addRenderable(CGRenderable*);
	CGRenderable* detachRenderable(CGRenderable*);
	bool delRenderable(CGRenderable*);
	void removeAllRenderable();
	CGRenderable* getRenderable(unsigned int index);
	//渲染场景
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera); //应派生类中重写
	//图形对象选取（按对象名）
	CGRenderable* RenderableSelected(const CString& name);
	bool RenderableUnselect(const CString& name);
	bool RenderableUnselect(CGRenderable* r);
	bool RenderableUnselectAll();
	bool RenderableSelectAll();
	//图形对象的拾取（二维图形）
	virtual CGRenderable* UpdatePicked(const Vec2d& p, double radius); //更新选择（如果拾取对象成功，则替换选择集）
	virtual CGRenderable* AppendPicked(const Vec2d& p, double radius); //添加选择（如果拾取对象成功，则加入选择集）
protected:
	CTypedPtrArray<CObArray, CGRenderable*> mRenderables;//图形对象列表
	//图形对象选择集
	CTypedPtrArray<CObArray, CGRenderable*> mSelections;
};
CG_NAMESPACE_EXIT
#endif //_CGSCENE_H_INCLUDED
#ifndef _CGSCENE_H_INCLUDED
#define _CGSCENE_H_INCLUDED
#include "Vector2.h"
#include "AABBox2.h"
#include "CGObject.h"
#include "Matrix33.h"
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
public:
	//二维图形对象的几何变换
	virtual bool Translate(double tx, double ty); //平移
	virtual bool Rotate(double angle, double cx, double cy); //旋转（逆时针为正，度）
	virtual bool Scale(double sx, double sy); //缩放（关于坐标原点缩放）
	virtual bool Scale(double sx, double sy, double cx, double cy); //缩放（关于指定参考点缩放）
	virtual bool Scale(double sx, double sy, double cx, double cy, const Vec2d& xDir); //缩放（指定参考点，缩放方向）
	virtual bool MirrorXAxis(); //关于X轴对称（二维、三维）
	virtual bool MirrorYAxis(); //关于Y轴对称（二维、三维）
	virtual bool MirrorYeqPosX(); //关于y=x对称（二维、三维）
	virtual bool MirrorYeNegPX(); //关于y=-x对称（二维、三维）
	virtual bool MirrorOrigin(); //关于原点对称（二维、三维）
	virtual bool ShearXAxis(double shx); //沿X轴错切
	virtual bool ShearYAxis(double shy); //沿Y轴错切
	virtual bool ShearXYAxis(double shx, double shy); //沿X、Y轴错切
	virtual bool Transform(const Mat3d& mat); //几何变换（左乘给定矩阵）
protected:
	CTypedPtrArray<CObArray, CGRenderable*> mRenderables;//图形对象列表
	//图形对象选择集
	CTypedPtrArray<CObArray, CGRenderable*> mSelections;
};
CG_NAMESPACE_EXIT
#endif //_CGSCENE_H_INCLUDED
#include "pch.h"
#include "CGScene.h"
#include "CGRenderable.h"
#include "CGCamera.h"
#include "CGRenderContext.h"
CG_NAMESPACE_ENTER
IMPLEMENT_SERIAL(CGScene, CGObject, 1)
CGScene::CGScene()
	:CGObject(CString("CGScene"))
{
}
CGScene::~CGScene()
{
	removeAllRenderable();
	ClearClipResult();
}
//序列化
void CGScene::Serialize(CArchive & ar)
{
	CGObject::Serialize(ar);
	mRenderables.Serialize(ar);
	if (ar.IsStoring())
	{
	}
	else
	{
		int cnt = mRenderables.GetCount();
		for (int i = 0; i < cnt; i++)
		{
			mRenderables.GetAt(i)->addToScene(this); //建立与场景的关联
		}
	}
}
//图形对象
bool CGScene::addRenderable(CGRenderable* pr)
{
	if (pr == nullptr || !pr->IsKindOf(RUNTIME_CLASS(CGRenderable)))
		return false;
	mRenderables.Add(pr);
	pr->addToScene(this);
	return true;
}
CGRenderable* CGScene::detachRenderable(CGRenderable* r)
{
	if (r)
	{
		r->addToScene(nullptr);
		int i = 0, cnt = mRenderables.GetSize();
		while (i < cnt)
		{
			if (mRenderables.GetAt(i) == r) {
				mRenderables.RemoveAt(i);
			}
			i++;
		}
	}
	return r;
}
bool CGScene::delRenderable(CGRenderable* pr)
{
	if (pr == nullptr)
		return false;
	int i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		if (mRenderables.GetAt(i) == pr) {
			delete mRenderables.GetAt(i);
			mRenderables.RemoveAt(i);
				return true;
		}
		i++;
	}
	return false;
}
void CGScene::removeAllRenderable()
{
	int i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		if (mRenderables.GetAt(i))
			delete mRenderables.GetAt(i);
		i++;
	}
	mRenderables.RemoveAll();
}
CGRenderable* CGScene::getRenderable(unsigned int index)
{
	if (index >= (unsigned int)mRenderables.GetSize())
		return nullptr;
	return mRenderables.GetAt(index);
}
//渲染场景到指定客户区（客户区包含若干视口），每个视口对应一个相机。
bool CGScene::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return false;
	return true;
}
//图形对象选取（按对象名）
CGRenderable* CGScene::RenderableSelected(const CString& name)
{
	int i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		CGRenderable* r = mRenderables.GetAt(i);
		if (r && r->name() == name && r->status() != CGRenderable::sSelected)
		{
			r->setStatus(CGRenderable::sSelected); //设置对象的状态为选中
			mSelections.Add(r); //加入选择集
			return r;
		}
		i++;
	}
	return nullptr;
}
bool CGScene::RenderableUnselect(const CString& name)
{
	int i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		CGRenderable* r = mRenderables.GetAt(i);
		if (r && r->name() == name)
		{
			return RenderableUnselect(r); //
		}
			i++;
	}
	return false;
}
bool CGScene::RenderableUnselect(CGRenderable* r)
{
	if (r)
		r->setStatus(CGRenderable::sNormal); //设置对象状态为正常
	int i = 0, cnt = mSelections.GetSize();
	while (i < cnt) //从选择集中清除
	{
		CGRenderable* s = mSelections.GetAt(i);
		if (s == r)
		{
			mSelections.RemoveAt(i);
			return true;
		}
		i++;
	}
	return false;
}
bool CGScene::RenderableUnselectAll()
{
	int i = 0, cnt = mSelections.GetSize();
	while (i < cnt)
	{
		CGRenderable* s = mSelections.GetAt(i);
		if (s)
			s->setStatus(CGRenderable::sNormal);
		i++;
	}
	mSelections.RemoveAll();
	if (cnt > 0) //如果有选中对象被清除标记
		return true;
	return false;
}
bool CGScene::RenderableSelectAll()
{
	mSelections.RemoveAll();
	int i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		CGRenderable* r = mRenderables.GetAt(i);
		if (r)
		{
			r->setStatus(CGRenderable::sSelected);
			mSelections.Add(r);
		}
		i++;
	}
	if (cnt > 0) //如果有选中对象被清除标记
		return true;
	return false;
}
//图形对象的拾取（二维图形）
CGRenderable* CGScene::UpdatePicked(const Vec2d& p, double radius) //更新选择
{
	int i = 0, cnt = mRenderables.GetSize();
	while (i < cnt) //遍历场景中的所有图形对象，判断是否拾取到
	{
		CGRenderable* r = mRenderables.GetAt(i);
		if (r && r->Picked(p, radius))
		{
			RenderableUnselectAll(); //替换前先清空选择集
			r->setStatus(CGRenderable::sSelected);
			mSelections.Add(r); //加入选择集
			return r;
		}
		i++;
	}
	return nullptr;
}
CGRenderable* CGScene::AppendPicked(const Vec2d& p, double radius) //添加选择
{
		int i = 0, cnt = mRenderables.GetSize();
	while (i < cnt) //遍历场景中的所有图形对象，判断是否拾取到
	{
		CGRenderable* r = mRenderables.GetAt(i);
		if (r && r->Picked(p, radius))
		{
			r->setStatus(CGRenderable::sSelected);
			mSelections.Add(r); //加入选择集
			return r;
		}
		i++;
	}
	return nullptr;
}
//二维图形对象的几何变换（针对选择集中的对象）
bool CGScene::Translate(double tx, double ty) //平移
{
	int i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CGRenderable* s = mSelections.GetAt(i);
		if (s)
			s->Translate(tx, ty);
		i++;
	}
	return true;
}
bool CGScene::Rotate(double angle, double cx, double cy) //旋转（逆时针为正，度）
{
	int i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CGRenderable* s = mSelections.GetAt(i);
		if (s)
			s->Rotate(angle, cx, cy);
		i++;
	}
	return true;
}
bool CGScene::Scale(double sx, double sy) //缩放
{
	int i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CGRenderable* s = mSelections.GetAt(i);
		if (s)
			s->Scale(sx, sy);
		i++;
	}
	return true;
}
bool CGScene::Scale(double sx, double sy, double cx, double cy) //缩放（关于指定参考点缩放）
{
	int i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CGRenderable* s = mSelections.GetAt(i);
		if (s)
			s->Scale(sx, sy, cx, cy);
		i++;
	}
	return true;
}
bool CGScene::Scale(double sx, double sy, double cx, double cy, const Vec2d& xDir) //缩放（指定参考点，缩放方向）
{
	int i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CGRenderable* s = mSelections.GetAt(i);
		if (s)
			s->Scale(sx, sy, cx, cy, xDir);
		i++;
	}
	return true;
}
bool CGScene::MirrorXAxis() //关于X轴对称（二维、三维）
{
	int i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CGRenderable* s = mSelections.GetAt(i);
		if (s)
			s->MirrorXAxis();
		i++;
	}
	return true;
}
bool CGScene::MirrorYAxis() //关于Y轴对称（二维、三维）
{
	int i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CGRenderable* s = mSelections.GetAt(i);
		if (s)
			s->MirrorYAxis();
		i++;
	}
	return true;
}
bool CGScene::MirrorYeqPosX() //关于y=x对称（二维、三维）
{
	int i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CGRenderable* s = mSelections.GetAt(i);
		if (s)
			s->MirrorYeqPosX();
		i++;
	}
	return true;
}
bool CGScene::MirrorYeNegPX() //关于y=-x对称（二维、三维）
{
	int i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CGRenderable* s = mSelections.GetAt(i);
		if (s)
			s->MirrorYeNegPX();
		i++;
	}
	return true;
}
bool CGScene::MirrorOrigin() //关于原点对称（二维、三维）
{
	int i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CGRenderable* s = mSelections.GetAt(i);
		if (s)
			s->MirrorOrigin();
		i++;
	}
	return true;
}
bool CGScene::ShearXAxis(double shx) //沿X轴错切
{
	int i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CGRenderable* s = mSelections.GetAt(i);
		if (s)
			s->ShearXAxis(shx);
		i++;
	}
	return true;
}
bool CGScene::ShearYAxis(double shy) //沿Y轴错切
{
	int i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CGRenderable* s = mSelections.GetAt(i);
		if (s)
			s->ShearYAxis(shy);
		i++;
	}
	return true;
}
bool CGScene::ShearXYAxis(double shx, double shy) //沿X、Y轴错切
{
	int i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CGRenderable* s = mSelections.GetAt(i);
		if (s)
			s->ShearXYAxis(shx, shy);
		i++;
	}
	return true;
}
bool CGScene::Transform(const Mat3d& mat) //几何变换（左乘给定矩阵）
{
	int i = 0, cnt = mSelections.GetSize();
	if (cnt == 0)
		return false;
	while (i < cnt)
	{
		CGRenderable* s = mSelections.GetAt(i);
		if (s)
			s->Transform(mat);
		i++;
	}
	return true;
}
//给定裁剪窗口（矩形范围）左下右上进行采集，裁剪结果不为空时返回true。
bool CGScene::Clip(double xl, double yb, double xr, double yt, CGCamera* pCamera)
{
	//派生类中实现
	return false;
}
void CGScene::ClearClipResult() //清除裁剪结果集
{
	int i = 0, cnt = mClipResult.GetSize();
	while (i < cnt)
	{
		if (mClipResult.GetAt(i))
			delete mClipResult.GetAt(i);
		i++;
	}
	mClipResult.RemoveAll();
}
CG_NAMESPACE_EXIT
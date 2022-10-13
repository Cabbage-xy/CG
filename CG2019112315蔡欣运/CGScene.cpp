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

CG_NAMESPACE_EXIT
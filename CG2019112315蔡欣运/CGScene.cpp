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
//���л�
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
			mRenderables.GetAt(i)->addToScene(this); //�����볡���Ĺ���
		}
	}
}
//ͼ�ζ���
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
//��Ⱦ������ָ���ͻ������ͻ������������ӿڣ���ÿ���ӿڶ�Ӧһ�������
bool CGScene::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return false;
	return true;
}
//ͼ�ζ���ѡȡ������������
CGRenderable* CGScene::RenderableSelected(const CString& name)
{
	int i = 0, cnt = mRenderables.GetSize();
	while (i < cnt)
	{
		CGRenderable* r = mRenderables.GetAt(i);
		if (r && r->name() == name && r->status() != CGRenderable::sSelected)
		{
			r->setStatus(CGRenderable::sSelected); //���ö����״̬Ϊѡ��
			mSelections.Add(r); //����ѡ��
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
		r->setStatus(CGRenderable::sNormal); //���ö���״̬Ϊ����
	int i = 0, cnt = mSelections.GetSize();
	while (i < cnt) //��ѡ�������
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
	if (cnt > 0) //�����ѡ�ж���������
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
	if (cnt > 0) //�����ѡ�ж���������
		return true;
	return false;
}
//ͼ�ζ����ʰȡ����άͼ�Σ�
CGRenderable* CGScene::UpdatePicked(const Vec2d& p, double radius) //����ѡ��
{
	int i = 0, cnt = mRenderables.GetSize();
	while (i < cnt) //���������е�����ͼ�ζ����ж��Ƿ�ʰȡ��
	{
		CGRenderable* r = mRenderables.GetAt(i);
		if (r && r->Picked(p, radius))
		{
			RenderableUnselectAll(); //�滻ǰ�����ѡ��
			r->setStatus(CGRenderable::sSelected);
			mSelections.Add(r); //����ѡ��
			return r;
		}
		i++;
	}
	return nullptr;
}
CGRenderable* CGScene::AppendPicked(const Vec2d& p, double radius) //���ѡ��
{
		int i = 0, cnt = mRenderables.GetSize();
	while (i < cnt) //���������е�����ͼ�ζ����ж��Ƿ�ʰȡ��
	{
		CGRenderable* r = mRenderables.GetAt(i);
		if (r && r->Picked(p, radius))
		{
			r->setStatus(CGRenderable::sSelected);
			mSelections.Add(r); //����ѡ��
			return r;
		}
		i++;
	}
	return nullptr;
}

CG_NAMESPACE_EXIT
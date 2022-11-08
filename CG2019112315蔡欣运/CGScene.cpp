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
//��άͼ�ζ���ļ��α任�����ѡ���еĶ���
bool CGScene::Translate(double tx, double ty) //ƽ��
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
bool CGScene::Rotate(double angle, double cx, double cy) //��ת����ʱ��Ϊ�����ȣ�
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
bool CGScene::Scale(double sx, double sy) //����
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
bool CGScene::Scale(double sx, double sy, double cx, double cy) //���ţ�����ָ���ο������ţ�
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
bool CGScene::Scale(double sx, double sy, double cx, double cy, const Vec2d& xDir) //���ţ�ָ���ο��㣬���ŷ���
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
bool CGScene::MirrorXAxis() //����X��Գƣ���ά����ά��
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
bool CGScene::MirrorYAxis() //����Y��Գƣ���ά����ά��
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
bool CGScene::MirrorYeqPosX() //����y=x�Գƣ���ά����ά��
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
bool CGScene::MirrorYeNegPX() //����y=-x�Գƣ���ά����ά��
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
bool CGScene::MirrorOrigin() //����ԭ��Գƣ���ά����ά��
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
bool CGScene::ShearXAxis(double shx) //��X�����
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
bool CGScene::ShearYAxis(double shy) //��Y�����
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
bool CGScene::ShearXYAxis(double shx, double shy) //��X��Y�����
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
bool CGScene::Transform(const Mat3d& mat) //���α任����˸�������
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
//�����ü����ڣ����η�Χ���������Ͻ��вɼ����ü������Ϊ��ʱ����true��
bool CGScene::Clip(double xl, double yb, double xr, double yt, CGCamera* pCamera)
{
	//��������ʵ��
	return false;
}
void CGScene::ClearClipResult() //����ü������
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
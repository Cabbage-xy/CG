#include "pch.h"
#include "CGRenderable.h"
#include "Vector2.h"
CG_NAMESPACE_ENTER
IMPLEMENT_SERIAL(CGRenderable, CGObject, 1)
CGRenderable::CGRenderable()
	:CGObject(CString("CGRenderable"))
	, mScene(nullptr), mStatus(sNormal)
{
}
CGRenderable::CGRenderable(const CString& name)
	: CGObject(CString(name))
	, mScene(nullptr), mStatus(sNormal)
{
}
CGRenderable::~CGRenderable()
{
}
void CGRenderable::addToScene(CGScene* s)
{
	mScene = s;
}
CGScene* CGRenderable::scene() const
{
	return mScene;
}
//���л�
void CGRenderable::Serialize(CArchive& ar)
{
	CGObject::Serialize(ar);
}
void CGRenderable::Render(CGRenderContext* pRC, CGCamera* pCamera) //���ƶ���ʹ��ָ�����
{
	//��������ʵ��
}
void CGRenderable::computeBoundingBox() //�������İ�Χ��
{
	//��������ʵ��
}
bool CGRenderable::Picked(const Vec2d& p, double radius) //����ά���Ƿ�ʰȡ��
{
	//��������ʵ��
	return false;
}
CG_NAMESPACE_EXIT
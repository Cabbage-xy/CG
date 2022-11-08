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
//��άͼ�ζ���ļ��α任
void CGRenderable::Translate(double tx, double ty) //ƽ��
{
	//��������ʵ��
}
void CGRenderable::Rotate(double angle, double cx, double cy) //��ת����ʱ��Ϊ�����ȣ�
{
	//��������ʵ��
}
void CGRenderable::Scale(double sx, double sy) //����
{
	//��������ʵ��
}
void CGRenderable::Scale(double sx, double sy, double cx, double cy) //����
{
	//��������ʵ��
}
void CGRenderable::Scale(double sx, double sy, double cx, double cy, const Vec2d& xDir) //����
{
	//��������ʵ��
}
void CGRenderable::MirrorXAxis() //����X��Գƣ���ά����ά��
{
	//��������ʵ��
}
void CGRenderable::MirrorYAxis() //����Y��Գƣ���ά����ά��
{
	//��������ʵ��
}
void CGRenderable::MirrorYeqPosX() //����y=x�Գƣ���ά����ά��
{
	//��������ʵ��
}
void CGRenderable::MirrorYeNegPX() //����y=-x�Գƣ���ά����ά��
{
	//��������ʵ��
}
void CGRenderable::MirrorOrigin() //����ԭ��Գƣ���ά����ά��
{
	//��������ʵ��
}
void CGRenderable::ShearXAxis(double shx) //��X�����
{
	//��������ʵ��
}
void CGRenderable::ShearYAxis(double shy) //��Y�����
{
	//��������ʵ��
}
void CGRenderable::ShearXYAxis(double shx, double shy) //��X��Y�����
{
	//��������ʵ��
}
void CGRenderable::Transform(const Mat3d& mat) //���α任����˸�������
{
	//��������ʵ��
}
//�����ü����ڣ����η�Χ���������Ͻ��вɼ����ü��������result���顣
bool CGRenderable::Cliped(double xl, double yb, double xr, double yt, CGCamera* pCamera,
	CTypedPtrArray<CObArray, CGRenderable*>& result)
{
	return false;
}
CG_NAMESPACE_EXIT
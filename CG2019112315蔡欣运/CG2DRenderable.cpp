#include "pch.h"
#include "CG2DRenderable.h"
CG_NAMESPACE_ENTER
IMPLEMENT_SERIAL(CG2DRenderable, CGRenderable, 1)
CG2DRenderable::CG2DRenderable()
	:CGRenderable(CString("CG2DRenderable"))
	, mPenColor(RGB(0, 0, 0)), mPenWidth(1), mPenStyle(PS_SOLID)
	, mBrushUse(false), mBrushColor(RGB(0, 0, 0)), mBrushIndex(-1)
{
}
CG2DRenderable::CG2DRenderable(const CString & name)
	: CGRenderable(CString(name))
	, mPenColor(RGB(0, 0, 0)), mPenWidth(1), mPenStyle(PS_SOLID)
	, mBrushUse(false), mBrushColor(RGB(0, 0, 0)), mBrushIndex(-1)
{
}
CG2DRenderable::~CG2DRenderable()
{
}
//���л�
void CG2DRenderable::Serialize(CArchive& ar)
{
	CGRenderable::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << mPenColor << mPenWidth << mPenStyle << mBrushUse << mBrushColor << mBrushIndex;
	}
	else
	{
		ar >> mPenColor >> mPenWidth >> mPenStyle >> mBrushUse >> mBrushColor >> mBrushIndex;
	}
}
void CG2DRenderable::setPenColor(COLORREF color)
{
	mPenColor = color;
}
COLORREF CG2DRenderable::penColor() const
{
	return mPenColor;
}
void CG2DRenderable::setPenWidth(int width)
{
	mPenWidth = width;
}
int CG2DRenderable::penWidth() const
{
	return mPenWidth;
}
void CG2DRenderable::setPenStyle(int style)
{
	mPenStyle = style;
}
int CG2DRenderable::penStyle() const
{
	return mPenStyle;
}
void CG2DRenderable::setBrushUse(bool use)
{
	mBrushUse = use;
}
bool CG2DRenderable::brushUse() const
{
	return mBrushUse;
}
void CG2DRenderable::setBrushColor(COLORREF color)
{
	mBrushColor = color;
}
COLORREF CG2DRenderable::brushColor() const
{
	return mBrushColor;
}
void CG2DRenderable::setBrushIndex(int index)
{
	mBrushIndex = index;
}
int CG2DRenderable::brushIndex() const
{
	return mBrushIndex;
}
void CG2DRenderable::Render(CGRenderContext* pRC, CGCamera* pCamera) //���ƶ���ʹ��ָ�����
{
	//�ɸ�������׼�����ƹ��ߣ����ʻ�ˢ��
	//��������ʵ��
}
ABox2d& CG2DRenderable::BoundingABox() //AABB��Χ�У�����������
{
	if (boundsDirty())
	{
		computeBoundingBox();
	}
	return mABox;
}
void CG2DRenderable::computeBoundingBox() //�����Χ�У���Ҫ����������ʵ��
{
	//��������ʵ�֣�Ȼ��Ҫ�������º���
	setBoundsDirty(false);
}
bool CG2DRenderable::Picked(const Vec2d& p, double radius) //����ά���Ƿ�ʰȡ��
{ //�˴�ֻ�Ǽ򵥸��ݰ�Χ���Ƿ��ཻ�����жϣ�Ҫ����ȷ�ж�����Ӧ������������д
	ABox2d abox = BoundingABox();
	ABox2d sbox(p, radius);
	if (abox.intersects(sbox))
		return true;
	return false;
}
CG_NAMESPACE_EXIT
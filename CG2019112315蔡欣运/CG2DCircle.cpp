#include "pch.h"
#include "CG2DCircle.h"
#include "CGDI2DRenderContext.h"
#include "CGDI2DCamera.h"
#include "CGDI2DView.h"

CG_NAMESPACE_ENTER
IMPLEMENT_SERIAL(CG2DCircle, CG2DRenderable, 1)
CG2DCircle::CG2DCircle()
	: CG2DRenderable(CString("CG2DCircle")), mCenter(0, 0), r(0)
{
	mName.Format(_T("Բ-%ld"), sID);
}
CG2DCircle::CG2DCircle(const Vec2d& c, const double r)
	: CG2DRenderable(CString("CG2DCircle")), mCenter(c), r(r)
{
	mName.Format(_T("Բ-%ld"), sID);
}
CG2DCircle::CG2DCircle(const Vec2d& m1, const Vec2d& m2)
	: CG2DRenderable(CString("Բ-%ld"))
{
	mCenter.x() = (m1.x() + m2.x()) / 2;
	mCenter.y() = (m1.y() + m2.y()) / 2;
	r = (mCenter - m1).length();
	mName.Format(_T("Բ-%ld"), sID);
}
CG2DCircle::CG2DCircle(const CG2DCircle& other)
	: CG2DRenderable(CString("CG2DCircle")), mCenter(other.mCenter), r(other.r)
{
	mName.Format(_T("Բ-%ld"), sID);
}
CG2DCircle::~CG2DCircle()
{
}
//���л�
void CG2DCircle::Serialize(CArchive& ar)
{
	CG2DRenderable::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << mCenter.x() << mCenter.y() << r;
	}
	else
	{
		ar >> mCenter.x() >> mCenter.y() >> r;
	}
}
void CG2DCircle::Render(CGRenderContext* pRC, CGCamera* pCamera) //���ƶ���ʹ��ָ�����
{
	if (pRC == nullptr || !pRC->IsKindOf(RUNTIME_CLASS(CGDI2DRenderContext)) || pRC->getView() == nullptr)
		return;
	if (pCamera == nullptr || !pCamera->IsKindOf(RUNTIME_CLASS(CGDI2DCamera)))
		return;
#ifdef USEMEMDC
	HDC hDC = ((CGDI2DRenderContext*)pRC)->hmemDC(); //ʹ��˫���棨�ڴ�DC��
#else
	HDC hDC = pRC->hdc(); //��ʹ��˫���棨�ڴ�DC��
#endif
//����Բ����
	int circleAlgorithm = pRC->getView()->CircleAlgorithm();
	if (circleAlgorithm == CGRenderContext::aCircleCDC) {
		CPen pen(penStyle(), penWidth(), penColor());
		//CBrush brush(RGB(255, 255, 255));
		CBrush brush(brushColor());
		Vec2i v1 = pCamera->WorldtoViewPort(Vec2d(mCenter.x() - r, mCenter.y() - r));
		Vec2i v2 = pCamera->WorldtoViewPort(Vec2d(mCenter.x() + r, mCenter.y() + r));
		if (hDC != 0)
		{
			HPEN hOldPen = (HPEN)::SelectObject(hDC, pen.GetSafeHandle());
			HBRUSH hOldBrush = (HBRUSH)::SelectObject(hDC, brush.GetSafeHandle());
			::Ellipse(hDC, v1.x(), v1.y(), v2.x(), v2.y());
			::SelectObject(hDC, hOldPen);
			::SelectObject(hDC, hOldBrush);
		}
		else
		{
			CClientDC dc(pRC->getView());
			CPen* pOldPen = dc.SelectObject(&pen);
			CBrush* pOldBrush = dc.SelectObject(&brush);
			dc.Ellipse(v1.x(), v1.y(), v2.x(), v2.y());
			dc.SelectObject(pOldPen);
			dc.SelectObject(pOldBrush);
		}
	}
	else if (circleAlgorithm == CGRenderContext::aCrcleMidPoint) {
		Vec2i center = pCamera->WorldtoViewPort(mCenter);
		pRC->MidPointCircle(center, (int)r, penColor());
	}
	else if (circleAlgorithm == CGRenderContext::aCircleBresenham) {
		Vec2i center = pCamera->WorldtoViewPort(mCenter);
		pRC->BresenhamCircle(center, (int)r, penColor());
	}
	//�˴����Ի��ƶ����Χ�еķ�ʽ��ʾ����ѡ�У�Ҳ��������ȷ��ѡ����ʾ��ʽ
	if (status() == CGRenderable::sSelected) //������ѡ��״̬
	{
		//�԰�Χ�л���ѡ��״̬
		ABox2d abox = BoundingABox(); //�����Χ�У����ư�Χ��
		Vec2i v1 = pCamera->WorldtoViewPort(abox.minCorner());
		Vec2i v2 = pCamera->WorldtoViewPort(abox.maxCorner());
		CPen pen(PS_DASHDOT, 1, RGB(0, 0, 255));
		if (hDC != 0)
		{
			HPEN hOldPen = (HPEN)::SelectObject(hDC, pen.GetSafeHandle());
			HBRUSH hOldBrush = (HBRUSH)::SelectObject(hDC, (HBRUSH)GetStockObject(NULL_BRUSH));
			::Rectangle(hDC, v1.x(), v1.y(), v2.x(), v2.y());
			::SelectObject(hDC, hOldPen);
			::SelectObject(hDC, hOldBrush);
		}
		else
		{
			CClientDC dc(pRC->getView()); //��ʹ��˫���棨�ڴ�DC����ֱ��ʹ��ClientDC
			CPen* pOldPen = dc.SelectObject(&pen);
			CBrush* pOldBursh = (CBrush*)dc.SelectStockObject(NULL_BRUSH);
			dc.Rectangle(v1.x(), v1.y(), v2.x(), v2.y());
			dc.SelectObject(pOldPen);
			dc.SelectObject(pOldBursh);
		}
	}
}
void CG2DCircle::computeBoundingBox() //�����Χ��
{
	mABox.setNull(); //�����
	mABox.addPoint(Vec2d(mCenter.x() + r, mCenter.y() + r)); //���Ͻ�
	mABox.addPoint(Vec2d(mCenter.x() - r, mCenter.y() - r)); //���½�
	setBoundsDirty(false);
}
//��άͼ�ζ���ļ��α任����д������麯����
void CG2DCircle::Translate(double tx, double ty) //ƽ��
{
	//�򵥱任����ʹ�þ���ֱ������
	mCenter.x() += tx;
	mCenter.y() += ty;
	setBoundsDirty(true);
}

void CG2DCircle::MirrorXAxis() //����X��Գƣ���ά����ά��
{
	//�򵥱任����ʹ�þ���ֱ������
	mCenter.y() = -mCenter.y();
	setBoundsDirty(true);
}
void CG2DCircle::MirrorYAxis() //����Y��Գƣ���ά����ά��
{
	//�򵥱任����ʹ�þ���ֱ������
	mCenter.x() = -mCenter.x();
	setBoundsDirty(true);
}
void CG2DCircle::MirrorYeqPosX() //����y=x�Գƣ���ά����ά��
{
	//�򵥱任����ʹ�þ���ֱ������
	double t = mCenter.x();
	mCenter.x() = mCenter.y();
	mCenter.y() = t;
	setBoundsDirty(true);
}
void CG2DCircle::MirrorYeNegPX() //����y=-x�Գƣ���ά����ά��
{
	//�򵥱任����ʹ�þ���ֱ������
	double t = mCenter.x();
	mCenter.x() = -mCenter.y();
	mCenter.y() = -t;
	setBoundsDirty(true);
}
void CG2DCircle::MirrorOrigin() //����ԭ��Գƣ���ά����ά��
{
	//�򵥱任����ʹ�þ���ֱ������
	mCenter.x() = -mCenter.x();
	mCenter.y() = -mCenter.y();
	setBoundsDirty(true);
}

CG_NAMESPACE_EXIT
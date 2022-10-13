#include "pch.h"
#include "CG2DLine.h"
#include "CGDI2DRenderContext.h"
#include "CGDI2DCamera.h"
#include "CGDI2DView.h"
CG_NAMESPACE_ENTER
IMPLEMENT_SERIAL(CG2DLine, CG2DRenderable, 1)
CG2DLine::CG2DLine()
	: CG2DRenderable(CString("CG2DLine")), mStart(0, 0), mEnd(0, 0)
{
	mName.Format(_T("ֱ��-%ld"), sID);
}
CG2DLine::CG2DLine(const Vec2d& s, const Vec2d& e)
	: CG2DRenderable(CString("CG2DLine"))
{
	Vec2d dir = e - s;
	double dirlen = dir.length();
	double length = 2000;
	if (dirlen)
	{
		mEnd.x() = e.x() + length * dir.x() / dirlen;
		mEnd.y() = e.y() + length * dir.y() / dirlen;
		mStart.x() = s.x() - length * dir.x() / dirlen;
		mStart.y() = s.y() - length * dir.y() / dirlen;
	}
	else
	{
		mEnd.x() = mStart.x();
		mEnd.y() = mStart.y();
	}
	mName.Format(_T("ֱ��-%ld"), sID);
}
/*
CG2DLine::CG2DLine(const Vec2d& s, const Vec2d& dir)
	: CG2DRenderable(CString("ֱ��"))
{
	double dirlen = dir.length();
	double length = 2000;
	if (dirlen)
	{
		mEnd.x() = mStart.x() + length * dir.x() / dirlen;
		mEnd.y() = mStart.y() + length * dir.y() / dirlen;
		mStart.x() = mEnd.x() - length * dir.x() / dirlen;
		mStart.y() = mEnd.y() - length * dir.y() / dirlen;
	}
	else
	{
		mEnd.x() = mStart.x();
		mEnd.y() = mStart.y();
	}
	mName.Format(_T("ֱ��-%ld"), sID);
}
*/
CG2DLine::CG2DLine(const CG2DLine& other)
	: CG2DRenderable(CString("CG2DLine")), mStart(other.mStart), mEnd(other.mEnd)
{
	mName.Format(_T("ֱ��-%ld"), sID);
}
CG2DLine::~CG2DLine()
{
}
//���л�
void CG2DLine::Serialize(CArchive& ar)
{
	CG2DRenderable::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << mStart.x() << mStart.y() << mEnd.x() << mEnd.y();
	}
	else
	{
		ar >> mStart.x() >> mStart.y() >> mEnd.x() >> mEnd.y();
	}
}
void CG2DLine::Render(CGRenderContext* pRC, CGCamera* pCamera) //���ƶ���ʹ��ָ�����
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
//�����߶ζ���
	Vec2i v1 = pCamera->WorldtoViewPort(mStart);
	Vec2i v2 = pCamera->WorldtoViewPort(mEnd);
	/*
	//ģ������Զ
	Vec2i dir = v2 - v1;
	double dirlen = dir.length();
	v1.x() = v1.x() - 5000.0 * dir.x() / dirlen;
	v1.y() = v1.y() - 5000.0 * dir.y() / dirlen;
	v2.x() = v2.x() + 5000.0 * dir.x() / dirlen;
	v2.y() = v2.y() + 5000.0 * dir.y() / dirlen;
	*/
	//CDC���Ʋ���
	CPen pen(penStyle(), penWidth(), penColor());
	if (hDC != 0)
	{
		HPEN hOldPen = (HPEN)::SelectObject(hDC, pen.GetSafeHandle());
		::MoveToEx(hDC, v1.x(), v1.y(), nullptr);
		::LineTo(hDC, v2.x(), v2.y());
		::SelectObject(hDC, hOldPen);
	}
	else
	{
		CClientDC dc(pRC->getView());
		CPen* pOldPen = dc.SelectObject(&pen);
		dc.MoveTo(v1.x(), v1.y());
		dc.LineTo(v2.x(), v2.y());
		dc.SelectObject(pOldPen);
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
void CG2DLine::computeBoundingBox() //�����Χ��
{
	mABox.setNull(); //�����
	mABox.addPoint(mStart); //���
	mABox.addPoint(mEnd); //�յ�
	setBoundsDirty(false);
}
bool CG2DLine::Picked(const Vec2d& p, double radius) //�Ƿ�ʰȡ��
{
	//������λ�úͷ�Χ����Χr���Ը�����Ҫ��ΪԲ�뾶�������α߳���һ�룩
	ABox2d abox = BoundingABox();
	ABox2d sbox(p, radius);
	if (abox.intersects(sbox)) //��������߶ΰ�Χ���ڣ���һ���жϾ���
	{
		//�㵽ֱ�߶εľ���
		Vec2d ES = mEnd - mStart;
		Vec2d PS = p - mStart;
		Vec2d PE = p - mEnd;
		double c = ES.dot(PS);
		if (c <= 0) return PS.length();
		double d = ES.lengthSquared();
		if (c >= d) return (PE.length());
		double r = c / d;
		double px = mStart.x() + (mEnd.x() - mStart.x()) * r;
		double py = mStart.y() + (mEnd.y() - mStart.y()) * r;
		Vec2d S = Vec2d(px, py);
		double dis = (p - S).length();
		if (dis <= r)
			return true;
	}
	return false;
}

CG_NAMESPACE_EXIT
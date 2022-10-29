#include "pch.h"
#include "CG2DLineSegment.h"
#include "CGDI2DRenderContext.h"
#include "CGDI2DCamera.h"
#include "CGDI2DView.h"
CG_NAMESPACE_ENTER
IMPLEMENT_SERIAL(CG2DLineSegment, CG2DRenderable, 1)
CG2DLineSegment::CG2DLineSegment()
	: CG2DRenderable(CString("CG2DLineSegment")), mStart(0, 0), mEnd(0, 0)
{
	mName.Format(_T("ֱ�߶�-%ld"), sID);
}
CG2DLineSegment::CG2DLineSegment(const Vec2d& s, const Vec2d& e)
	: CG2DRenderable(CString("CG2DLineSegment")), mStart(s), mEnd(e)
{
	mName.Format(_T("ֱ�߶�-%ld"), sID);
}
CG2DLineSegment::CG2DLineSegment(const Vec2d& s, const Vec2d& dir, double length)
	: CG2DRenderable(CString("ֱ�߶�")), mStart(s)
{
		double dirlen = dir.length();
	if (dirlen)
	{
		mEnd.x() = mStart.x() + length * dir.x() / dirlen;
		mEnd.y() = mStart.y() + length * dir.y() / dirlen;
	}
	else
	{
		mEnd.x() = mStart.x();
		mEnd.y() = mStart.y();
	}
	mName.Format(_T("ֱ�߶�-%ld"), sID);
}
CG2DLineSegment::CG2DLineSegment(const CG2DLineSegment& other)
	: CG2DRenderable(CString("CG2DLineSegment")), mStart(other.mStart), mEnd(other.mEnd)
{
	mName.Format(_T("ֱ�߶�-%ld"), sID);
}
CG2DLineSegment::~CG2DLineSegment()
{
}
//���л�
void CG2DLineSegment::Serialize(CArchive& ar)
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
void CG2DLineSegment::Render(CGRenderContext* pRC, CGCamera* pCamera) //���ƶ���ʹ��ָ�����
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
	int lineAlgorithm = pRC->getView()->LineAlgorithm();
	if (lineAlgorithm == CGRenderContext::aLineCDC) {
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
	}
	else if (lineAlgorithm == CGRenderContext::aLineDDA) {
		pRC->DDALine(v1, v2, penColor());
	}
	else if (lineAlgorithm == CGRenderContext::aLineMidPoint) {
		pRC->MidPointLine(v1, v2, penColor());
	}
	else if (lineAlgorithm == CGRenderContext::aLineBresenham) {
		pRC->BresenhamLine(v1, v2, penColor());
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
			CBrush * pOldBursh = (CBrush*)dc.SelectStockObject(NULL_BRUSH);
			dc.Rectangle(v1.x(), v1.y(), v2.x(), v2.y());
			dc.SelectObject(pOldPen);
			dc.SelectObject(pOldBursh);
		}
	}
}
void CG2DLineSegment::computeBoundingBox() //�����Χ��
{
	mABox.setNull(); //�����
	mABox.addPoint(mStart); //���
	mABox.addPoint(mEnd); //�յ�
	setBoundsDirty(false);
}
bool CG2DLineSegment::Picked(const Vec2d& p, double radius) //�Ƿ�ʰȡ��
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
//��άͼ�ζ���ļ��α任����д������麯����
void CG2DLineSegment::Translate(double tx, double ty) //ƽ��
{
	//�򵥱任����ʹ�þ���ֱ������
	mStart.x() += tx;
	mStart.y() += ty;
	mEnd.x() += tx;
	mEnd.y() += ty;
	setBoundsDirty(true);
}
void CG2DLineSegment::Rotate(double angle, double cx, double cy) //��ת����ʱ��Ϊ�����ȣ�
{
	//ʹ�ñ任����ʵ��
	Mat3d mat = Mat3d::getRotation(angle, Vec2d(cx, cy));
	Vec3d start = operator*(mat, Vec3d(mStart));
	Vec3d end = operator*(mat, Vec3d(mEnd));
	mStart = Vec2d(start.x(), start.y());
	mEnd = Vec2d(end.x(), end.y());
	setBoundsDirty(true);
}
void CG2DLineSegment::Scale(double sx, double sy) //����
{
	//��������ԭ�����ţ��򵥱任����ʹ�þ���ֱ������
	mStart.x() *= sx;
	mStart.y() *= sy;
	mEnd.x() *= sx;
	mEnd.y() *= sy;
	setBoundsDirty(true);
}
void CG2DLineSegment::Scale(double sx, double sy, double cx, double cy) //����
{
	//����ָ�������ţ�ʹ�þ���ֱ������
	Mat3d mat = Mat3d::getScaling(Vec2d(sx, sy), Vec2d(cx, cy));
	Vec3d start = operator*(mat, Vec3d(mStart));
	Vec3d end = operator*(mat, Vec3d(mEnd));
	mStart = Vec2d(start.x(), start.y());
	mEnd = Vec2d(end.x(), end.y());
	setBoundsDirty(true);
}
void CG2DLineSegment::Scale(double sx, double sy, double cx, double cy, const Vec2d& xDir) //����
{
	//����ָ�������ţ�ʹ�þ���ֱ������
	Mat3d mat = Mat3d::getScaling(Vec2d(sx, sy), Vec2d(cx, cy), xDir);
	Vec3d start = operator*(mat, Vec3d(mStart));
	Vec3d end = operator*(mat, Vec3d(mEnd));
	mStart = Vec2d(start.x(), start.y());
	mEnd = Vec2d(end.x(), end.y());
	setBoundsDirty(true);
}
void CG2DLineSegment::MirrorXAxis() //����X��Գƣ���ά����ά��
{
	//�򵥱任����ʹ�þ���ֱ������
	mStart.y() = -mStart.y();
	mEnd.y() = -mEnd.y();
	setBoundsDirty(true);
}
void CG2DLineSegment::MirrorYAxis() //����Y��Գƣ���ά����ά��
{
	//�򵥱任����ʹ�þ���ֱ������
	mStart.x() = -mStart.x();
	mEnd.x() = -mEnd.x();
	setBoundsDirty(true);
}
void CG2DLineSegment::MirrorYeqPosX() //����y=x�Գƣ���ά����ά��
{
	//�򵥱任����ʹ�þ���ֱ������
	double t = mStart.x();
	mStart.x() = mStart.y();
	mStart.y() = t;
	t = mEnd.x();
	mEnd.x() = mEnd.y();
	mEnd.y() = t;
	setBoundsDirty(true);
}
void CG2DLineSegment::MirrorYeNegPX() //����y=-x�Գƣ���ά����ά��
{
	//�򵥱任����ʹ�þ���ֱ������
	double t = mStart.x();
	mStart.x() = -mStart.y();
	mStart.y() = -t;
	t = mEnd.x();
	mEnd.x() = -mEnd.y();
	mEnd.y() = -t;
	setBoundsDirty(true);
}
void CG2DLineSegment::MirrorOrigin() //����ԭ��Գƣ���ά����ά��
{
	//�򵥱任����ʹ�þ���ֱ������
	mStart.x() = -mStart.x();
	mStart.y() = -mStart.y();
	mEnd.x() = -mEnd.x();
	mEnd.y() = -mEnd.y();
	setBoundsDirty(true);
}
void CG2DLineSegment::ShearXAxis(double shx) //��X�����
{
	//�򵥱任����ʹ�þ���ֱ������
	mStart.x() = mStart.x() + shx * mStart.y();
	mEnd.x() = mEnd.x() + shx * mEnd.y();
	setBoundsDirty(true);
}
void CG2DLineSegment::ShearYAxis(double shy) //��Y�����
{
	//�򵥱任����ʹ�þ���ֱ������
	mStart.y() = mStart.y() + shy * mStart.x();
	mEnd.y() = mEnd.y() + shy * mEnd.x();
	setBoundsDirty(true);
}
void CG2DLineSegment::ShearXYAxis(double shx, double shy) //��X��Y�����
{
	//ʹ�ñ任����ʵ��
	Mat3d mat = Mat3d::getShear(shx, shy);
	Vec3d start = operator*(mat, Vec3d(mStart));
	Vec3d end = operator*(mat, Vec3d(mEnd));
	mStart = Vec2d(start.x(), start.y());
	mEnd = Vec2d(end.x(), end.y());
	setBoundsDirty(true);
}
void CG2DLineSegment::Transform(const Mat3d& mat) //���α任����˸�������
{
	Vec3d start = operator*(mat, Vec3d(mStart));
	Vec3d end = operator*(mat, Vec3d(mEnd));
	mStart = Vec2d(start.x(), start.y());
	mEnd = Vec2d(end.x(), end.y());
	setBoundsDirty(true);
}
CG_NAMESPACE_EXIT
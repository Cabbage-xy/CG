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
	mName.Format(_T("直线-%ld"), sID);
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
	mName.Format(_T("直线-%ld"), sID);
}
/*
CG2DLine::CG2DLine(const Vec2d& s, const Vec2d& dir)
	: CG2DRenderable(CString("直线"))
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
	mName.Format(_T("直线-%ld"), sID);
}
*/
CG2DLine::CG2DLine(const CG2DLine& other)
	: CG2DRenderable(CString("CG2DLine")), mStart(other.mStart), mEnd(other.mEnd)
{
	mName.Format(_T("直线-%ld"), sID);
}
CG2DLine::~CG2DLine()
{
}
//序列化
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
void CG2DLine::Render(CGRenderContext* pRC, CGCamera* pCamera) //绘制对象，使用指定相机
{
	if (pRC == nullptr || !pRC->IsKindOf(RUNTIME_CLASS(CGDI2DRenderContext)) || pRC->getView() == nullptr)
		return;
	if (pCamera == nullptr || !pCamera->IsKindOf(RUNTIME_CLASS(CGDI2DCamera)))
		return;
#ifdef USEMEMDC
	HDC hDC = ((CGDI2DRenderContext*)pRC)->hmemDC(); //使用双缓存（内存DC）
#else
	HDC hDC = pRC->hdc(); //不使用双缓存（内存DC）
#endif
//绘制线段对象
	Vec2i v1 = pCamera->WorldtoViewPort(mStart);
	Vec2i v2 = pCamera->WorldtoViewPort(mEnd);
	/*
	//模拟无限远
	Vec2i dir = v2 - v1;
	double dirlen = dir.length();
	v1.x() = v1.x() - 5000.0 * dir.x() / dirlen;
	v1.y() = v1.y() - 5000.0 * dir.y() / dirlen;
	v2.x() = v2.x() + 5000.0 * dir.x() / dirlen;
	v2.y() = v2.y() + 5000.0 * dir.y() / dirlen;
	*/
	//CDC绘制测试
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
	//此处仅以绘制对象包围盒的方式显示对象被选中，也可以自行确定选中显示方式
	if (status() == CGRenderable::sSelected) //对象处于选中状态
	{
		//以包围盒绘制选中状态
		ABox2d abox = BoundingABox(); //计算包围盒，绘制包围盒
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
			CClientDC dc(pRC->getView()); //不使用双缓存（内存DC），直接使用ClientDC
			CPen* pOldPen = dc.SelectObject(&pen);
			CBrush* pOldBursh = (CBrush*)dc.SelectStockObject(NULL_BRUSH);
			dc.Rectangle(v1.x(), v1.y(), v2.x(), v2.y());
			dc.SelectObject(pOldPen);
			dc.SelectObject(pOldBursh);
		}
	}
}
void CG2DLine::computeBoundingBox() //计算包围盒
{
	mABox.setNull(); //先清空
	mABox.addPoint(mStart); //起点
	mABox.addPoint(mEnd); //终点
	setBoundsDirty(false);
}
bool CG2DLine::Picked(const Vec2d& p, double radius) //是否拾取到
{
	//（给定位置和范围，范围r可以根据需要设为圆半径或正方形边长的一半）
	ABox2d abox = BoundingABox();
	ABox2d sbox(p, radius);
	if (abox.intersects(sbox)) //如果点在线段包围盒内，进一步判断距离
	{
		//点到直线段的距离
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
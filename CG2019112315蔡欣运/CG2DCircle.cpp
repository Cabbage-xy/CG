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
	mName.Format(_T("圆-%ld"), sID);
}
CG2DCircle::CG2DCircle(const Vec2d& c, const double r)
	: CG2DRenderable(CString("CG2DCircle")), mCenter(c), r(r)
{
	mName.Format(_T("圆-%ld"), sID);
}
CG2DCircle::CG2DCircle(const Vec2d& m1, const Vec2d& m2)
	: CG2DRenderable(CString("圆-%ld"))
{
	mCenter.x() = (m1.x() + m2.x()) / 2;
	mCenter.y() = (m1.y() + m2.y()) / 2;
	r = (mCenter - m1).length();
	mName.Format(_T("圆-%ld"), sID);
}
CG2DCircle::CG2DCircle(const CG2DCircle& other)
	: CG2DRenderable(CString("CG2DCircle")), mCenter(other.mCenter), r(other.r)
{
	mName.Format(_T("圆-%ld"), sID);
}
CG2DCircle::~CG2DCircle()
{
}
//序列化
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
void CG2DCircle::Render(CGRenderContext* pRC, CGCamera* pCamera) //绘制对象，使用指定相机
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
//绘制圆对象
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
void CG2DCircle::computeBoundingBox() //计算包围盒
{
	mABox.setNull(); //先清空
	mABox.addPoint(Vec2d(mCenter.x() + r, mCenter.y() + r)); //左上角
	mABox.addPoint(Vec2d(mCenter.x() - r, mCenter.y() - r)); //右下角
	setBoundsDirty(false);
}
//二维图形对象的几何变换（重写基类的虚函数）
void CG2DCircle::Translate(double tx, double ty) //平移
{
	//简单变换，不使用矩阵直接运算
	mCenter.x() += tx;
	mCenter.y() += ty;
	setBoundsDirty(true);
}

void CG2DCircle::MirrorXAxis() //关于X轴对称（二维、三维）
{
	//简单变换，不使用矩阵直接运算
	mCenter.y() = -mCenter.y();
	setBoundsDirty(true);
}
void CG2DCircle::MirrorYAxis() //关于Y轴对称（二维、三维）
{
	//简单变换，不使用矩阵直接运算
	mCenter.x() = -mCenter.x();
	setBoundsDirty(true);
}
void CG2DCircle::MirrorYeqPosX() //关于y=x对称（二维、三维）
{
	//简单变换，不使用矩阵直接运算
	double t = mCenter.x();
	mCenter.x() = mCenter.y();
	mCenter.y() = t;
	setBoundsDirty(true);
}
void CG2DCircle::MirrorYeNegPX() //关于y=-x对称（二维、三维）
{
	//简单变换，不使用矩阵直接运算
	double t = mCenter.x();
	mCenter.x() = -mCenter.y();
	mCenter.y() = -t;
	setBoundsDirty(true);
}
void CG2DCircle::MirrorOrigin() //关于原点对称（二维、三维）
{
	//简单变换，不使用矩阵直接运算
	mCenter.x() = -mCenter.x();
	mCenter.y() = -mCenter.y();
	setBoundsDirty(true);
}

CG_NAMESPACE_EXIT
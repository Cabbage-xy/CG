#include "pch.h"
#include "CGRenderContext.h"
#include "CGView.h"
CG_NAMESPACE_ENTER
CGRenderContext::CGRenderContext()
{
	mView = nullptr;
	mHWND = 0;
	mHDC = 0;
	mHGLRC = 0;
	mWidth = 0;
	mHeight = 0;
}
CGRenderContext::CGRenderContext(CGView* pView)
{
	mView = pView;
	if (pView != nullptr)
	{
		mHWND = pView->GetSafeHwnd();
		mHDC = ::GetDC(mHWND);
		CRect rc;
		pView->GetClientRect(&rc);
		mWidth = rc.Width();
		mHeight = rc.Height();
		mHGLRC = 0; //mHGLRC = ::wglCreateContext(mHDC); //��ά�������г�ʼ��
	}
	else
	{
		mHWND = 0;
		mHDC = 0;
		mHGLRC = 0; //
		mWidth = 0;
		mHeight = 0;
	}
}
CGRenderContext::~CGRenderContext()
{
	if (mHDC != 0)
	{
		::ReleaseDC(mHWND, mHDC); //�ͷ�DC
		mHDC = 0;
	}
}
void CGRenderContext::setView(CGView* pView)
{
	mView = pView;
	if (mView != nullptr)
	{
		mHWND = mView->GetSafeHwnd();
			if (mHDC != 0)
			{
				::ReleaseDC(mHWND, mHDC); //�ͷ�DC
				mHDC = 0;
			}
		mHDC = ::GetDC(mHWND);//��ά������������
		CRect rc;
		pView->GetClientRect(&rc);
		mWidth = rc.Width();
		mHeight = rc.Height();
		//mHGLRC = ::wglCreateContext(mHDC); //��ά������������
	}
}
CGView* CGRenderContext::getView() const
{
	return mView;
}
void CGRenderContext::DDALine(const Vec2i& start, const Vec2i& end, unsigned long color)
{
	if (mView == nullptr && mHWND == 0 && mHDC == 0)
		return;
#ifdef USEMEMDC
	if (mMemDC == 0)
		return;
#endif
	HDC hDC = 0;
#ifdef USEMEMDC
	hDC = hmemDC(); //ʹ��˫���棨�ڴ�DC��
#else
	hDC = hdc(); //��ʹ��˫���棨�ڴ�DC��
#endif
	CClientDC dc(mView); //���hDCΪ0ʱʹ��
	//������ֱ�߶εĻ��ƣ����в��䣩
	int x0 = start.x(), y0 = start.y();
	int x1 = end.x(), y1 = end.y();
	int dx = x1 - x0, dy = y1 - y0;
	float x, y, xIncre, yIncre;
	int epsl;
	x = x0; y = y0;
	if (abs(dx) < abs(dy)) epsl = abs(dy);
	else  epsl = abs(dx);
	xIncre = (float)dx / (float)epsl;
	yIncre = (float)dy / (float)epsl;

	if (hDC != 0)
	{
		for (int i = 0; i <= epsl; i++) {
			::SetPixel(hDC, (int)(x + 0.5), (int)(y + 0.5), color);
			x += xIncre;
			y += yIncre;
		}
	}
	else
	{
		for (int i = 0; i <= epsl; i++) {
			dc.SetPixel((int)(x + 0.5), (int)(y + 0.5), color);
			x += xIncre;
			y += yIncre;
		}
	}
	return;
}
void CGRenderContext::DDALine(const Vec2i& start, const Vec2i& end, unsigned long color, int width)
{
	return;
}
void CGRenderContext::DDALine(const Vec2i& start, const Vec2i& end, unsigned long color, int width, int style)
{
	return;
}
void CGRenderContext::MidPointLine(const Vec2i& start, const Vec2i& end, unsigned long color)
{
	return;
}
void CGRenderContext::MidPointLine(const Vec2i& start, const Vec2i& end, unsigned long color, int width)
{
	return;
}
void CGRenderContext::MidPointLine(const Vec2i& start, const Vec2i& end, unsigned long color, int width, int style)
{
	return;
}
void CGRenderContext::BresenhamLine(const Vec2i& start, const Vec2i& end, unsigned long color)
{
	return;
}
void CGRenderContext::BresenhamLine(const Vec2i& start, const Vec2i& end, unsigned long color, int width)
{
	return;
}
void CGRenderContext::BresenhamLine(const Vec2i& start, const Vec2i& end, unsigned long color, int width, int style)
{
	return;
}
void CGRenderContext::MidPointCircle(const Vec2i& center, int radius, unsigned long color) {
	return;
}
void CGRenderContext::BresenhamCircle(const Vec2i& center, int radius, unsigned long color) {
	return;
}
CG_NAMESPACE_EXIT
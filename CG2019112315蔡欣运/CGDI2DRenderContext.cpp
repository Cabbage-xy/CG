#include "pch.h"
#include "CGDI2DRenderContext.h"
#include "CGDI2DView.h"
CG_NAMESPACE_ENTER
CGDI2DRenderContext::CGDI2DRenderContext()
{
#ifdef USEMEMDC
	mMemDC = 0;
	mMemBMP = 0;
#endif
}
CGDI2DRenderContext::CGDI2DRenderContext(CGDI2DView* pView)
	:CGRenderContext(pView)
{
	if (pView != nullptr && mHWND != 0 && mHDC != 0)
	{
#ifdef USEMEMDC
		CRect rc;
		pView->GetClientRect(&rc);
		mMemDC = ::CreateCompatibleDC(mHDC);
		mMemBMP = ::CreateCompatibleBitmap(mHDC, rc.Width(), rc.Height());
		::SelectObject(mMemDC, mMemBMP);
		HBRUSH br = ::CreateSolidBrush(RGB(255, 255, 255));
		::FillRect(mMemDC, &rc, br);
		::DeleteObject(br);
#endif
	}
	else
	{
#ifdef USEMEMDC
		mMemDC = 0;
		mMemBMP = 0;
#endif
	}
}
CGDI2DRenderContext::~CGDI2DRenderContext()
{
#ifdef USEMEMDC
	if (mMemBMP != 0)
	{
		::DeleteObject(mMemBMP);
		mMemBMP = 0;
	}
	if (mMemDC != 0)
	{
		::DeleteDC(mMemDC);
		mMemDC = 0;
	}
#endif
}
void CGDI2DRenderContext::setView(CGView* pView) //���ǻ���setView
{
	CGRenderContext::setView(pView);
	if (pView != nullptr && mHWND != 0 && mHDC != 0)
	{
#ifdef USEMEMDC
		if (mMemBMP != 0)
		{
			::DeleteObject(mMemBMP);
			mMemBMP = 0;
		}
		if (mMemDC != 0)
		{
			::DeleteDC(mMemDC);
			mMemDC = 0;
		}
		CRect rc;
		pView->GetClientRect(&rc);
		mMemDC = ::CreateCompatibleDC(mHDC);
		mMemBMP = ::CreateCompatibleBitmap(mHDC, rc.Width(), rc.Height());
		::SelectObject(mMemDC, mMemBMP);
		HBRUSH br = ::CreateSolidBrush(RGB(255, 255, 255));
		::FillRect(mMemDC, &rc, br);
		::DeleteObject(br);
#endif
	}
}
void CGDI2DRenderContext::DDALine(const Vec2i& start, const Vec2i& end, unsigned long color)
{
	if (mView == nullptr || mHWND == 0 || mHDC == 0)
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
void CGDI2DRenderContext::DDALine(const Vec2i& start, const Vec2i& end, unsigned long color, int width)
{
	return;
}
void CGDI2DRenderContext::DDALine(const Vec2i& start, const Vec2i& end, unsigned long color, int width, int style)
{
	return;
}
void CGDI2DRenderContext::MidPointLine(const Vec2i& start, const Vec2i& end, unsigned long color)
{
	if (mView == nullptr || mHWND == 0 || mHDC == 0)
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
	int x = x0, y = y0;
	int a = y0 - y1, b = x1 - x0;
	int cx = (b >= 0 ? 1 : (b = -b, -1));
	int cy = (a <= 0 ? 1 : (a = -a, -1));
	int d, d1, d2;
	
	if (hDC != 0)
	{
		::SetPixel(hDC, x, y, color);
		if (-a <= b)		// б�ʾ���ֵ <= 1
		{
			d = 2 * a + b;
			d1 = 2 * a;
			d2 = 2 * (a + b);
			while (x != x1)
			{
				if (d < 0)
					y += cy, d += d2;
				else
					d += d1;
				x += cx;
				::SetPixel(hDC, x, y, color);
			}
		}
		else				// б�ʾ���ֵ > 1
		{
			d = 2 * b + a;
			d1 = 2 * b;
			d2 = 2 * (a + b);
			while (y != y1)
			{
				if (d < 0)
					d += d1;
				else
					x += cx, d += d2;
				y += cy;
				::SetPixel(hDC, x, y, color);
			}
		}
	}
	else
	{
		dc.SetPixel(x, y, color);
		if (-a <= b)		// б�ʾ���ֵ <= 1
		{
			d = 2 * a + b;
			d1 = 2 * a;
			d2 = 2 * (a + b);
			while (x != x1)
			{
				if (d < 0)
					y += cy, d += d2;
				else
					d += d1;
				x += cx;
				dc.SetPixel(x, y, color);
			}
		}
		else				// б�ʾ���ֵ > 1
		{
			d = 2 * b + a;
			d1 = 2 * b;
			d2 = 2 * (a + b);
			while (y != y1)
			{
				if (d < 0)
					d += d1;
				else
					x += cx, d += d2;
				y += cy;
				dc.SetPixel(x, y, color);
			}
		}
	}
	return;
}
void CGDI2DRenderContext::MidPointLine(const Vec2i& start, const Vec2i& end, unsigned long color, int width)
{
	return;
}
void CGDI2DRenderContext::MidPointLine(const Vec2i& start, const Vec2i& end, unsigned long color, int width, int style)
{
	return;
}
void CGDI2DRenderContext::BresenhamLine(const Vec2i& start, const Vec2i& end, unsigned long color)
{
	if (mView == nullptr || mHWND == 0 || mHDC == 0)
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
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int erro = (dx > dy ? dx : -dy) / 2;
	int x = x0, y = y0;
	if (hDC != 0)
	{
		while (::SetPixel(hDC, x, y, color), x != x1 || y != y1)
		{
			int e2 = erro;
			if (e2 > -dx) { erro -= dy; x += sx; }
			if (e2 < dy) { erro += dx; y += sy; }
		}
	}
	else
	{
		while (dc.SetPixel(x, y, color), x != x1 || y != y1)
		{
			int e2 = erro;
			if (e2 > -dx) { erro -= dy; x += sx; }
			if (e2 < dy) { erro += dx; y += sy; }
		}
	}
	return;
}
void CGDI2DRenderContext::BresenhamLine(const Vec2i& start, const Vec2i& end, unsigned long color, int width)
{
	return;
}
void CGDI2DRenderContext::BresenhamLine(const Vec2i& start, const Vec2i& end, unsigned long color, int width, int style)
{
	return;
}

void CGDI2DRenderContext::CirclePlot(const Vec2i& center, int x, int y, unsigned long color) {
	if (mView == nullptr || mHWND == 0 || mHDC == 0)
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
	int xc = center.x(), yc = center.y();
	if (hDC != 0) {
		::SetPixel(hDC, xc + x, yc + y, color);
		::SetPixel(hDC, xc + x, yc - y, color);
		::SetPixel(hDC, xc - x, yc + y, color);
		::SetPixel(hDC, xc - x, yc - y, color);
		::SetPixel(hDC, xc + y, yc + x, color);
		::SetPixel(hDC, xc + y, yc - x, color);
		::SetPixel(hDC, xc - y, yc + x, color);
		::SetPixel(hDC, xc - y, yc - x, color);
	}
	else {
		CClientDC dc(mView); //���hDCΪ0ʱʹ��
		dc.SetPixel(xc + x, yc + y, color);
		dc.SetPixel(xc + x, yc - y, color);
		dc.SetPixel(xc - x, yc + y, color);
		dc.SetPixel(xc - x, yc - y, color);
		dc.SetPixel(xc + y, yc + x, color);
		dc.SetPixel(xc + y, yc - x, color);
		dc.SetPixel(xc - y, yc + x, color);
		dc.SetPixel(xc - y, yc - x, color);
	}
	return;
}

void CGDI2DRenderContext::MidPointCircle(const Vec2i& center, int radius, unsigned long color) {
	int x, y;
	double d;
	x = 0;
	y = radius;
	d = 1.25 - radius;
	CirclePlot(center, x, y, color);
	while (x < y)
	{
		if (d < 0)
			d = d + (double)x * 2.0f + 3.0f;
		else
		{
			d = d + ((double)x - (double)y) * 2.0f + 5;
			y--;
		}
		x++;
		CirclePlot(center, x, y, color);
	}
	return;
}
void CGDI2DRenderContext::BresenhamCircle(const Vec2i& center, int radius, unsigned long color) {
	int x, y, d;
	x = 0;
	y = radius;
	d = 3 - 2 * radius;
	CirclePlot(center, x, y, color);
	while (x < y)
	{
		if (d < 0)
		{
			d = d + 4 * x + 6;
		}
		else
		{
			d = d + 4 * (x - y) + 10;
			y--;
		}
		x++;
		CirclePlot(center, x, y, color);
	}
	return;
}
#ifdef USEMEMDC
void CGDI2DRenderContext::SwapBackBuffer()
{
		if (mView != nullptr && mHDC != 0 && mMemDC != 0)
		{
			CRect rc;
			mView->GetClientRect(&rc);
			::BitBlt(mHDC, 0, 0, rc.Width(), rc.Height(), mMemDC, 0, 0, SRCCOPY);
		}
}
#endif
CG_NAMESPACE_EXIT
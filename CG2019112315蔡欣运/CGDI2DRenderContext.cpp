#include "pch.h"
#include "CGDI2DRenderContext.h"
#include "CGDI2DView.h"
#include <stack>
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
void CGDI2DRenderContext::setView(CGView* pView) //覆盖基类setView
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
	hDC = hmemDC(); //使用双缓存（内存DC）
#else
	hDC = hdc(); //不使用双缓存（内存DC）
#endif
	CClientDC dc(mView); //如果hDC为0时使用
	//以下是直线段的绘制（自行补充）
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
	hDC = hmemDC(); //使用双缓存（内存DC）
#else
	hDC = hdc(); //不使用双缓存（内存DC）
#endif
	CClientDC dc(mView); //如果hDC为0时使用
	//以下是直线段的绘制（自行补充）
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
		if (-a <= b)		// 斜率绝对值 <= 1
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
		else				// 斜率绝对值 > 1
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
		if (-a <= b)		// 斜率绝对值 <= 1
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
		else				// 斜率绝对值 > 1
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
	hDC = hmemDC(); //使用双缓存（内存DC）
#else
	hDC = hdc(); //不使用双缓存（内存DC）
#endif
	CClientDC dc(mView); //如果hDC为0时使用
	//以下是直线段的绘制（自行补充）
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
	hDC = hmemDC(); //使用双缓存（内存DC）
#else
	hDC = hdc(); //不使用双缓存（内存DC）
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
		CClientDC dc(mView); //如果hDC为0时使用
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

//有效边表多边形扫描线填充算法
int Compare(const void* a, const void* b) {
	float* pa = (float*)a;
	float* pb = (float*)b;
	return (*pa) - (*pb);  //从小到大排序
}

void CGDI2DRenderContext::ScanLinePolygonFill(const Vec2iArray& pnts, unsigned long fillcolor)
{
	int yLow, yHigh, xLow, xHigh;
	CalculateBounds(pnts, yLow, yHigh, xLow, xHigh);

	std::unordered_map<int, std::vector<float>> yHitsMap;
	PrepareMap(yHitsMap, pnts);


	for (int y = yLow; y <= yHigh; y++) {
		sort(yHitsMap.at(y).begin(), yHitsMap.at(y).end());

		int counter = 0, listIndex = 0;
		for (int x = xLow; x <= xHigh; x++) {
			if (x >= yHitsMap.at(y)[listIndex])
			{
				DrawPixel(x, y, fillcolor);
				counter++, listIndex++;
				if (listIndex >= yHitsMap.at(y).size()) break;
				//当扫描线上有两点x坐标相同时，表明遇到了顶点，则判断该顶点是否为局部极值
				if (yHitsMap.at(y)[listIndex] == yHitsMap.at(y)[listIndex - 1]) {
					if (!isPartialExtremum(pnts, x, y)) listIndex++;
				}
			}
			if (IsOdd(counter))
				DrawPixel(x, y, fillcolor);
		}
	}
}

void CGDI2DRenderContext::DrawPixel(int x, int y, unsigned long fillcolor) {
	if (mView == nullptr || mHWND == 0 || mHDC == 0)
		return;
#ifdef USEMEMDC
	if (mMemDC == 0)
		return;
#endif
	HDC hDC = 0;
#ifdef USEMEMDC
	hDC = hmemDC(); //使用双缓存（内存DC）
#else
	hDC = hdc(); //不使用双缓存（内存DC）
#endif
	CClientDC dc(mView); //如果hDC为0时使用
	//以下是直线段的绘制（自行补充）
	if (hDC != 0)
	{
		::SetPixel(hDC, (int)(x + 0.5), (int)(y + 0.5), fillcolor);
	}
	else
	{
		dc.SetPixel((int)(x + 0.5), (int)(y + 0.5), fillcolor);
	}
}

bool CGDI2DRenderContext::IsOdd(int num) {
	return num % 2;
}

void  CGDI2DRenderContext::CalculateBounds(const Vec2iArray& pnts, int& yLow, int& yHigh,
	int& xLow, int& xHigh) {
	yLow = xLow = 25000;
	yHigh = xHigh = -25000;
	for (auto pnt : pnts) {
		if (pnt.x() > xHigh) xHigh = pnt.x();
		if (pnt.y() > yHigh) yHigh = pnt.y();
		if (pnt.x() < xLow) xLow = pnt.x();
		if (pnt.y() < yLow) yLow = pnt.y();
	}
}


void CGDI2DRenderContext::PrepareMap(std::unordered_map<int, std::vector<float>>& yHitsMap, const Vec2iArray& pnts) {
	for (int p1 = 0; p1 < pnts.size(); p1++) {
		int p2 = (p1 + 1) % pnts.size();
		GetHits(pnts[p1], pnts[p2], yHitsMap);
	}
}

void CGDI2DRenderContext::GetHits(Vec2i p1, Vec2i p2, std::unordered_map<int, std::vector<float>>& yHitsMap) {
	if (p2.y() == p1.y()) return;
	float k = (float)(p2.x() - p1.x()) / (float)(p2.y() - p1.y());
	int yLow, yHigh;
	yLow = p2.y() < p1.y() ? p2.y() : p1.y();
	yHigh = p2.y() < p1.y() ? p1.y() : p2.y();

	for (int y = yLow; y <= yHigh; y++) {
		float hit = k * (y - p1.y()) + p1.x();
		bool found = yHitsMap.find(y) != yHitsMap.end();
		if (!found) {
			yHitsMap.insert({ y, std::vector<float>() });
		}

		yHitsMap[y].push_back(hit);
	}
}

bool CGDI2DRenderContext::isPartialExtremum(const Vec2iArray& pnts, const int x, const int y) {
	for (int i = 0; i < pnts.size(); i++) {
		if (pnts[i].y() == y && pnts[i].x() == x) {
			int p1 = (i + pnts.size() - 1) % pnts.size();
			int p2 = (i + 1) % pnts.size();
			//在同侧
			if (pnts[p1].y() - y < 0 == pnts[p2].y() - y < 0)
				return true;
			else
				return false;
		}
	}
}

//边界表示的种子填充算法
void CGDI2DRenderContext::BoundFill4(int x, int y, unsigned long boundcolor, unsigned long fillcolor) {
	if (mView == nullptr || mHWND == 0 || mHDC == 0)
	{
		return;
	}
#ifdef USEMEMDC
	if (mMemDC == 0)
		return;
	Vec2i point(x, y);
	std::stack<Vec2i> pointStack;
	pointStack.push(point);
	while (!pointStack.empty()) {
		Vec2i p = pointStack.top();
		pointStack.pop();
		int color = ::GetPixel(mMemDC, p.x(), p.y());
		if ((color != boundcolor) && (color != fillcolor)) {
			::SetPixel(mMemDC, p.x(), p.y(), fillcolor);
			Vec2i pTop(p.x(), p.y() + 1), pBottom(p.x(), p.y() - 1);
			Vec2i pLeft(p.x() - 1, p.y()), pRight(p.x() + 1, p.y());
			pointStack.push(pLeft);
			pointStack.push(pTop);
			pointStack.push(pBottom);
			pointStack.push(pRight);
		}
	}
	//int color = ::GetPixel(mMemDC, x, y);
	//if ((color != boundcolor) && (color != fillcolor))
	//{
	//	::SetPixel(mMemDC, x, y, fillcolor);
	//	BoundFill4(x - 1, y, boundcolor, fillcolor); //左
	//	BoundFill4(x, y + 1, boundcolor, fillcolor); //上
	//	BoundFill4(x + 1, y, boundcolor, fillcolor); //右
	//	BoundFill4(x, y - 1, boundcolor, fillcolor); //下
	//}
#endif
}
void CGDI2DRenderContext::BoundFill8(int x, int y, unsigned long boundcolor, unsigned long fillcolor) {
	if (mView == nullptr || mHWND == 0 || mHDC == 0)
	{
		return;
	}
#ifdef USEMEMDC
	if (mMemDC == 0)
		return;
	Vec2i point(x, y);
	std::stack<Vec2i> pointStack;
	pointStack.push(point);
	while (!pointStack.empty()) {
		Vec2i p = pointStack.top();
		pointStack.pop();
		int color = ::GetPixel(mMemDC, p.x(), p.y());
		if ((color != boundcolor) && (color != fillcolor)) {
			::SetPixel(mMemDC, p.x(), p.y(), fillcolor);
			Vec2i pTop(p.x(), p.y() + 1), pBottom(p.x(), p.y() - 1);
			Vec2i pLeft(p.x() - 1, p.y()), pRight(p.x() + 1, p.y());
			Vec2i pLT(p.x() - 1, p.y() + 1), pRT(p.x() + 1, p.y() + 1);
			Vec2i pLB(p.x() - 1, p.y() - 1), pRB(p.x() + 1, p.y() - 1);
			pointStack.push(pLeft);
			pointStack.push(pTop);
			pointStack.push(pBottom);
			pointStack.push(pRight);
			pointStack.push(pLT);
			pointStack.push(pRT);
			pointStack.push(pLB);
			pointStack.push(pRB);
		}
	}
	//int color = ::GetPixel(mMemDC, x, y);
	//if ((color != boundcolor) && (color != fillcolor))
	//{
	//	::SetPixel(mMemDC, x, y, fillcolor);
	//	BoundFill8(x + 1, y, boundcolor, fillcolor);
	//	BoundFill8(x - 1, y, boundcolor, fillcolor);
	//	BoundFill8(x, y + 1, boundcolor, fillcolor);
	//	BoundFill8(x, y - 1, boundcolor, fillcolor);
	//	BoundFill8(x + 1, y + 1, boundcolor, fillcolor);
	//	BoundFill8(x - 1, y - 1, boundcolor, fillcolor);
	//	BoundFill8(x - 1, y + 1, boundcolor, fillcolor);
	//	BoundFill8(x + 1, y - 1, boundcolor, fillcolor);
	//}
#endif
}
//内点表示的种子填充算法
void CGDI2DRenderContext::FloodFill4(int x, int y, unsigned long innercolor, unsigned long fillcolor) {
	if (mView == nullptr || mHWND == 0 || mHDC == 0)
	{
		return;
	}
#ifdef USEMEMDC
	if (mMemDC == 0)
		return;
	Vec2i point(x, y);
	std::stack<Vec2i> pointStack;
	pointStack.push(point);
	while (!pointStack.empty()) {
		Vec2i p = pointStack.top();
		pointStack.pop();
		int color = ::GetPixel(mMemDC, p.x(), p.y());
		if (color == innercolor) {
			::SetPixel(mMemDC, p.x(), p.y(), fillcolor);
			Vec2i pTop(p.x(), p.y() + 1), pBottom(p.x(), p.y() - 1);
			Vec2i pLeft(p.x() - 1, p.y()), pRight(p.x() + 1, p.y());
			pointStack.push(pLeft);
			pointStack.push(pTop);
			pointStack.push(pBottom);
			pointStack.push(pRight);
		}
	}
	//int color = ::GetPixel(mMemDC, x, y);
	//if (color == innercolor)
	//{
	//	::SetPixel(mMemDC, x, y, fillcolor);
	//	FloodFill4(x - 1, y, innercolor, fillcolor); //左
	//	FloodFill4(x, y + 1, innercolor, fillcolor); //上
	//	FloodFill4(x + 1, y, innercolor, fillcolor); //右
	//	FloodFill4(x, y - 1, innercolor, fillcolor); //下
	//}
#endif
}
void CGDI2DRenderContext::FloodFill8(int x, int y, unsigned long innercolor, unsigned long fillcolor) {
	if (mView == nullptr || mHWND == 0 || mHDC == 0)
	{
		return;
	}
#ifdef USEMEMDC
	if (mMemDC == 0)
		return;
	Vec2i point(x, y);
	std::stack<Vec2i> pointStack;
	pointStack.push(point);
	while (!pointStack.empty()) {
		Vec2i p = pointStack.top();
		pointStack.pop();
		int color = ::GetPixel(mMemDC, p.x(), p.y());
		if (color == innercolor) {
			::SetPixel(mMemDC, p.x(), p.y(), fillcolor);
			Vec2i pTop(p.x(), p.y() + 1), pBottom(p.x(), p.y() - 1);
			Vec2i pLeft(p.x() - 1, p.y()), pRight(p.x() + 1, p.y());
			Vec2i pLT(p.x() - 1, p.y() + 1), pRT(p.x() + 1, p.y() + 1);
			Vec2i pLB(p.x() - 1, p.y() - 1), pRB(p.x() + 1, p.y() - 1);
			pointStack.push(pLeft);
			pointStack.push(pTop);
			pointStack.push(pBottom);
			pointStack.push(pRight);
			pointStack.push(pLT);
			pointStack.push(pRT);
			pointStack.push(pLB);
			pointStack.push(pRB);
		}
	}
	//int color = ::GetPixel(mMemDC, x, y);
	//if (color == innercolor)
	//{
	//	::SetPixel(mMemDC, x, y, fillcolor);
	//	FloodFill8(x + 1, y, innercolor, fillcolor);
	//	FloodFill8(x - 1, y, innercolor, fillcolor);
	//	FloodFill8(x, y + 1, innercolor, fillcolor);
	//	FloodFill8(x, y - 1, innercolor, fillcolor);
	//	FloodFill8(x + 1, y + 1, innercolor, fillcolor);
	//	FloodFill8(x - 1, y - 1, innercolor, fillcolor);
	//	FloodFill8(x - 1, y + 1, innercolor, fillcolor);
	//	FloodFill8(x + 1, y - 1, innercolor, fillcolor);
	//}
#endif
}
//扫描线种子填充算法
void CGDI2DRenderContext::ScanLineSeedFill(int x, int y, unsigned long boundcolor, unsigned long fillcolor) {

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
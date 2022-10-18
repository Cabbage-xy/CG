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
		mHGLRC = 0; //mHGLRC = ::wglCreateContext(mHDC); //三维派生类中初始化
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
		::ReleaseDC(mHWND, mHDC); //释放DC
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
				::ReleaseDC(mHWND, mHDC); //释放DC
				mHDC = 0;
			}
		mHDC = ::GetDC(mHWND);//二维派生类中设置
		CRect rc;
		pView->GetClientRect(&rc);
		mWidth = rc.Width();
		mHeight = rc.Height();
		//mHGLRC = ::wglCreateContext(mHDC); //三维派生类中设置
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

int Compare(const void *a, const void *b) {
	float *pa = (float*)a;
	float *pb = (float*)b;
	return (*pa) - (*pb);  //从小到大排序
}

void CGRenderContext::ScanLinePolygonFill(const Vec2iArray& pnts, unsigned long fillcolor)
{
	// table = int[y][] 
	// lines(ptns)
	// loop (var line in lines){ for (y:low->high){ table[y] << hitX; } }

	// for (y: low -> high) { table[y].sort; for (x) { if odd? drawP() } }


	
	int yLow, yHigh, xLow, xHigh;
	CalculateBounds(pnts, yLow, yHigh, xLow, xHigh);
	
	std::unordered_map<int, std::vector<float>> yHitsMap;
	PrepareMap(yHitsMap, pnts, yHigh, yLow);

	
	for (int y = yLow; y <= yHigh; y++) {
		//std::qsort(yHitsMap.at(y).data(), yHitsMap.at(y).size(), sizeof(std::vector<float>), Compare);
		sort(yHitsMap.at(y).begin(), yHitsMap.at(y).end());
			
		int counter = 0;
		for (int x = xLow; x <= xHigh; x++) {
			if (x >= yHitsMap.at(y)[counter])
			{
				DrawPixel(x, y, fillcolor);
				counter++;
			}

			if (IsOdd(counter))
				DrawPixel(x, y, fillcolor);
		}
	}
	

}

void CGRenderContext::DrawPixel(int x, int y, unsigned long fillcolor) {
	if (mView == nullptr && mHWND == 0 && mHDC == 0)
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

bool CGRenderContext::IsOdd(int num) {
	return num % 2;
}

void  CGRenderContext::CalculateBounds(const Vec2iArray& pnts, int& yLow, int& yHigh,
	int& xLow, int& xHigh) {
	yLow = xLow = 25000;
	for (auto pnt : pnts) {
		if (pnt.x() > xHigh) xHigh = pnt.x();
		if (pnt.y() > yHigh) yHigh = pnt.y();
		if (pnt.x() < xLow) xLow = pnt.x();
		if (pnt.x() < yLow) yLow = pnt.y();
	}
}

void CGRenderContext::PrepareMap(std::unordered_map<int, std::vector<float>>& yHitsMap, const Vec2iArray &pnts, int yHigh, int yLow) {
	//auto slopes = GetSlopes();

	//yHitsMap = std::unordered_map<int, std::vector<float>>;

	for (int p1 = 0; p1 < pnts.size(); p1++) {
		int p2 = (p1 + 1) % pnts.size();

		GetHits(pnts[p1], pnts[p2], yLow, yHigh, yHitsMap);
	}
}

void CGRenderContext::GetHits(Vec2i p1, Vec2i p2, int yLow, int yHigh, std::unordered_map<int, std::vector<float>>& yHitsMap) {
	//std::vector<float> slopes(pnts.size());
	//for (int i = 0; i < pnts.size() - 1; i++) {
	//std::vector<float> hits;
	if(p2.y() == p1.y()) return;
	float k =  (p2.x() - p1.x()) / (p2.y() - p1.y());

	for (int y = yLow; y <= yHigh; y++) {
		float hit = k * (y - p1.y()) + p1.x();
		bool found = yHitsMap.find(y) != yHitsMap.end();
		if (!found) {
			yHitsMap.insert({ y, std::vector<float>() });
		}

		yHitsMap[y].push_back(hit);

		//std::vector<float> hits;/*
		/*hits.pop_back(hit)*//*;
		yHitsMap.insert(y, hits);*/

		//yHitsMap[y].push_back(hit);
		//hits.push_back(hit);
	}
	//return hits;

	//}
	//slopes.back() = (pnts.front().x() - pnts.back().x()) / (pnts.front().y() - pnts.back().y());
	//return slopes;
}
void CGRenderContext::BoundFill4(int x, int y, unsigned long boundcolor, unsigned long fillcolor) {

}
void CGRenderContext::BoundFill8(int x, int y, unsigned long boundcolor, unsigned long fillcolor) {

}
void CGRenderContext::FloodFill4(int x, int y, unsigned long innercolor, unsigned long fillcolor) {

}
void CGRenderContext::FloodFill8(int x, int y, unsigned long innercolor, unsigned long fillcolor) {

}

CG_NAMESPACE_EXIT
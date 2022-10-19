// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// CG2019112315蔡欣运GDI2DView.cpp: CCG2019112315蔡欣运GDI2DView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CG2019112315蔡欣运.h"
#endif

#include "CG2019112315蔡欣运GDI2DDoc.h"
#include "CG2019112315蔡欣运GDI2DView.h"
#include "MainFrm.h"
#include "Create2DLineSegment.h"
#include "Create2DLine.h"
#include "Create2DRay.h"
#include "Create2DPolyLine.h"
#include "Create2DCircle1PointRadius.h"
#include "Create2DCircle2PointDiameter.h"
#include "Create2DCircle3Point.h"
#include "Create2DPolygon.h"
#include "Create2DSeedFill.h"
#include "Pick2DRenderable.h"

#include "CGRenderContext.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCG2019112315蔡欣运GDI2DView

IMPLEMENT_DYNCREATE(CCG2019112315蔡欣运GDI2DView, CGDI2DView/*CView*/)

BEGIN_MESSAGE_MAP(CCG2019112315蔡欣运GDI2DView, CGDI2DView/*CView*/)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CGDI2DView/*CView*/::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CGDI2DView/*CView*/::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCG2019112315蔡欣运GDI2DView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DRAW_CDC, &CCG2019112315蔡欣运GDI2DView::OnDrawCdc)
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDBLCLK()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_POINTER, &CCG2019112315蔡欣运GDI2DView::OnPointer)
	ON_UPDATE_COMMAND_UI(ID_POINTER, &CCG2019112315蔡欣运GDI2DView::OnUpdatePointer)
	ON_COMMAND(ID_DRAW_LINESEG, &CCG2019112315蔡欣运GDI2DView::OnDrawLineseg)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LINESEG, &CCG2019112315蔡欣运GDI2DView::OnUpdateDrawLineseg)
	ON_COMMAND(ID_PICK_ONE, &CCG2019112315蔡欣运GDI2DView::OnPickOne)
	ON_UPDATE_COMMAND_UI(ID_PICK_ONE, &CCG2019112315蔡欣运GDI2DView::OnUpdatePickOne)
	ON_COMMAND(ID_PICK_ALL, &CCG2019112315蔡欣运GDI2DView::OnPickAll)
	ON_COMMAND(ID_PICK_NONE, &CCG2019112315蔡欣运GDI2DView::OnPickNone)
	ON_COMMAND(ID_DRAW_LINE, &CCG2019112315蔡欣运GDI2DView::OnDrawLine)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LINE, &CCG2019112315蔡欣运GDI2DView::OnUpdateDrawLine)
	ON_COMMAND(ID_DRAW_RAY, &CCG2019112315蔡欣运GDI2DView::OnDrawRay)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RAY, &CCG2019112315蔡欣运GDI2DView::OnUpdateDrawRay)
	ON_COMMAND(ID_DRAW_2DLINE_TIME, &CCG2019112315蔡欣运GDI2DView::OnDraw2dlineTime)
	ON_COMMAND(ID_DRAW_BROKEN_LINE, &CCG2019112315蔡欣运GDI2DView::OnDrawBrokenLine)
	ON_UPDATE_COMMAND_UI(ID_DRAW_BROKEN_LINE, &CCG2019112315蔡欣运GDI2DView::OnUpdateDrawBrokenLine)
	ON_COMMAND(ID_DRAW_CIRCLE_2POINT_DIAMETER, &CCG2019112315蔡欣运GDI2DView::OnDrawCircle2pointDiameter)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CIRCLE_2POINT_DIAMETER, &CCG2019112315蔡欣运GDI2DView::OnUpdateDrawCircle2pointDiameter)
	ON_COMMAND(ID_DRAW_CIRCLE_1POINT_RADIUS, &CCG2019112315蔡欣运GDI2DView::OnDrawCircle1pointRadius)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CIRCLE_1POINT_RADIUS, &CCG2019112315蔡欣运GDI2DView::OnUpdateDrawCircle1pointRadius)
	ON_COMMAND(ID_DRAW_CIRCLE_3POINT, &CCG2019112315蔡欣运GDI2DView::OnDrawCircle3point)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CIRCLE_3POINT, &CCG2019112315蔡欣运GDI2DView::OnUpdateDrawCircle3point)
	ON_COMMAND(ID_DRAW_POLYGON, &CCG2019112315蔡欣运GDI2DView::OnDrawPolygon)
	ON_UPDATE_COMMAND_UI(ID_DRAW_POLYGON, &CCG2019112315蔡欣运GDI2DView::OnUpdateDrawPolygon)
	ON_COMMAND(ID_PICK_SEED_POINT, &CCG2019112315蔡欣运GDI2DView::OnPickSeedPoint)
	ON_UPDATE_COMMAND_UI(ID_PICK_SEED_POINT, &CCG2019112315蔡欣运GDI2DView::OnUpdatePickSeedPoint)
END_MESSAGE_MAP()

// CCG2019112315蔡欣运GDI2DView 构造/析构

CCG2019112315蔡欣运GDI2DView::CCG2019112315蔡欣运GDI2DView() noexcept
{
	// TODO: 在此处添加构造代码

}

CCG2019112315蔡欣运GDI2DView::~CCG2019112315蔡欣运GDI2DView()
{
}

BOOL CCG2019112315蔡欣运GDI2DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CGDI2DView/*CView*/::PreCreateWindow(cs);
}

//图形对象的拾取（二维图形）
void CCG2019112315蔡欣运GDI2DView::UpdatePicked(const Vec2d& p, double radius) //更新选择
{
	CCG2019112315蔡欣运GDI2DDoc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->UpdatePicked(p, radius);
		Invalidate();
		UpdateWindow();
	}
}
void CCG2019112315蔡欣运GDI2DView::AppendPicked(const Vec2d& p, double radius) //添加选择
{
	CCG2019112315蔡欣运GDI2DDoc* pDoc = GetDocument();
	if (pDoc)
	{
		pDoc->AppendPicked(p, radius);
		Invalidate();
		UpdateWindow();
	}
}

// CCG2019112315蔡欣运GDI2DView 绘图

void CCG2019112315蔡欣运GDI2DView::OnDraw(CDC* pDC)
{
	CCG2019112315蔡欣运GDI2DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	//pDC->MoveTo(100, 100); //默认画笔移到(100, 100)
	//pDC->LineTo(500, 200); //默认画笔绘制到(500, 200)
	
	RenderScene();
}


// CCG2019112315蔡欣运GDI2DView 打印


void CCG2019112315蔡欣运GDI2DView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCG2019112315蔡欣运GDI2DView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCG2019112315蔡欣运GDI2DView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCG2019112315蔡欣运GDI2DView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

//画笔属性
COLORREF CCG2019112315蔡欣运GDI2DView::PenColor() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return RGB(0, 0, 0);
	return pMainWnd->PenColor();
}
int CCG2019112315蔡欣运GDI2DView::PenWidth() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 1;
	return pMainWnd->PenWidth();
}
int CCG2019112315蔡欣运GDI2DView::PenStyle() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return PS_SOLID;
	return pMainWnd->PenStyle();
}
//画刷属性
bool CCG2019112315蔡欣运GDI2DView::UseBrush() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return false;
	return pMainWnd->UseBrush();
}
COLORREF CCG2019112315蔡欣运GDI2DView::BrushColor() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return RGB(255, 255, 255);
	return pMainWnd->BrushColor();
}
int CCG2019112315蔡欣运GDI2DView::BrushIndex() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return -1; // 0;
	return pMainWnd->BrushIndex();
}
//画线算法
int CCG2019112315蔡欣运GDI2DView::LineAlgorithm() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->LineAlgorithm();
}
//圆弧算法
int CCG2019112315蔡欣运GDI2DView::CircleAlgorithm() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->CircleAlgorithm();
}
//填充算法
int CCG2019112315蔡欣运GDI2DView::FillAlgorithm() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->FillAlgorithm();
}
int CCG2019112315蔡欣运GDI2DView::SeedAlgorithm() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return 0;
	return pMainWnd->SeedAlgorithm();
}
//点阵区域的边界颜色
COLORREF CCG2019112315蔡欣运GDI2DView::BoundColor() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return RGB(0, 0, 0);
	return pMainWnd->BoundColor();
}
//点阵区域的内点颜色
COLORREF CCG2019112315蔡欣运GDI2DView::FloodColor() const
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (!pMainWnd)
		return RGB(255, 255, 255);
	return pMainWnd->FloodColor();
}
//状态栏上显示提示信息
void CCG2019112315蔡欣运GDI2DView::Prompt(const CString& str)
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (pMainWnd != nullptr)
	{
		pMainWnd->ShowPrompt(str);
	}
}
//根据视口坐标获取对应场景坐标（二维）-调用场景类的ViewPortToWorld
Vec2d CCG2019112315蔡欣运GDI2DView::ViewPortToWorld(const Vec2i& p)
{
	CCG2019112315蔡欣运GDI2DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return Vec2d();
	return pDoc->ViewPorttoWorld(p);
}
Vec2i CCG2019112315蔡欣运GDI2DView::WorldToViewPort(const Vec2d& p)
{
	CCG2019112315蔡欣运GDI2DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return Vec2i();
	return pDoc->WorldtoViewPort(p);
}
//图形对象添加到场景
bool CCG2019112315蔡欣运GDI2DView::addRenderable(CGRenderable * r)
{
	CCG2019112315蔡欣运GDI2DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return false;
	bool ret = pDoc->addRenderable(r);
	return ret;
}
bool CCG2019112315蔡欣运GDI2DView::delReaderable(CGRenderable* r)
{
	CCG2019112315蔡欣运GDI2DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return false;
	bool ret = pDoc->delReaderable(r);
	return ret;
}
void CCG2019112315蔡欣运GDI2DView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCG2019112315蔡欣运GDI2DView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCG2019112315蔡欣运GDI2DView 诊断

#ifdef _DEBUG
void CCG2019112315蔡欣运GDI2DView::AssertValid() const
{
	CGDI2DView/*CView*/::AssertValid();
}

void CCG2019112315蔡欣运GDI2DView::Dump(CDumpContext& dc) const
{
	CGDI2DView/*CView*/::Dump(dc);
}

CCG2019112315蔡欣运GDI2DDoc* CCG2019112315蔡欣运GDI2DView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCG2019112315蔡欣运GDI2DDoc)));
	return (CCG2019112315蔡欣运GDI2DDoc*)m_pDocument;
}
#endif //_DEBUG


// CCG2019112315蔡欣运GDI2DView 消息处理程序


void CCG2019112315蔡欣运GDI2DView::OnDrawCdc()
{
	// TODO: 在此添加命令处理程序代码
	// 在此处添加基于GDI相关类进行基本图形绘制
	// （直线、圆、椭圆、矩形、多边形、折现、曲线、圆弧
	// 椭圆弧、弦、填充、文字等）以及
	// 图形属性的编程（修改线型、线宽、颜色、填充样式、文字样式等）
	// 掌握GDI图形编程相关类及函数的用法。
	CClientDC dc(this); //首先获取客户区绘制环境（相当于面板）

	// 绘制示例
	dc.MoveTo(100, 100);
	dc.LineTo(600, 200);

	// 其它练习

	// 绘制直线段
	CPen myPen1(PS_SOLID, 5, RGB(255, 0, 0));
	CPen* pOldPen = dc.SelectObject(&myPen1);
	dc.MoveTo(50, 50);
	dc.LineTo(100, 100);
	dc.SelectObject(pOldPen);

	// 绘制圆
	dc.Ellipse(125, 50, 175, 100);

	// 绘制椭圆
	dc.Ellipse(200, 50, 275, 100);

	// 绘制矩形
	dc.Rectangle(300, 50, 325, 100);

	// 绘制多边形
	CPoint m_point[5];
	m_point[0].x = 75;
	m_point[0].y = 125;
	m_point[1].x = 50;
	m_point[1].y = 150;
	m_point[2].x = 50;
	m_point[2].y = 175;
	m_point[3].x = 100;
	m_point[3].y = 175;
	m_point[4].x = 100;
	m_point[4].y = 150;
	dc.Polygon(m_point, 5);

	// 绘制折线
	//CPoint m_point[5];
	m_point[0].x = 150;
	m_point[0].y = 125;
	m_point[1].x = 125;
	m_point[1].y = 150;
	m_point[2].x = 125;
	m_point[2].y = 175;
	m_point[3].x = 175;
	m_point[3].y = 150;
	m_point[4].x = 175;
	m_point[4].y = 175;
	dc.Polyline(m_point, 5);

	// 绘制曲线

	// 绘制圆弧
	int x = 75, y = 200; //圆心
	int r = 50; //半径
	dc.Arc(x - r, y - r, x + r, y + r, x - r, y, x + r, y);//下半圆弧.

	// 绘制椭圆弧
	//int x = 200, y = 200;
	int a = 50, b = 25;
	x = 200, y = 200;
	dc.Arc(x - a, y - b, x + a, y + b, x - a, y, x + a, y);//下半圆弧.

	// 绘制弦
	//int x = 325, y = 192; //圆心
	x = 325, y = 192;
	//int r = 50; //半径
	r = 50;
	dc.Arc(x - r, y - r, x + r, y + r, x - r, y, x + r, y);//下半圆弧.
	dc.MoveTo(x - r, y);
	dc.LineTo(x + r, y);

	// 绘制填充区域
	TRIVERTEX vertex[2];
	vertex[0].x = 0;
	vertex[0].y = 275;
	vertex[0].Red = 0x0000;
	vertex[0].Green = 0x8000;
	vertex[0].Blue = 0x8000;
	vertex[0].Alpha = 0x0000;

	vertex[1].x = 300;
	vertex[1].y = 350;
	vertex[1].Red = 0x0000;
	vertex[1].Green = 0xd000;
	vertex[1].Blue = 0xd000;
	vertex[1].Alpha = 0x0000;

	GRADIENT_RECT gRect;
	gRect.UpperLeft = 0;
	gRect.LowerRight = 1;

	dc.GradientFill(vertex, 2, &gRect, 1, GRADIENT_FILL_RECT_H);

	// 绘制文字
	CRect rect(25, 25, 125, 50);
	CFont fontGrade;//定义CFont对象  
	fontGrade.CreatePointFont(100, L"宋体");//初始化
	CFont* pOldFont = dc.SelectObject(&fontGrade);//将CFont对象选入到当前DC中即为设置当前字体及大小
	dc.DrawText(_T("你好"), &rect, DT_LEFT | DT_WORDBREAK | DT_NOPREFIX | DT_EDITCONTROL);
}

bool CCG2019112315蔡欣运GDI2DView::RenderScene()
{
	CCG2019112315蔡欣运GDI2DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return false;
	//调用文档类的RenderScene
	return pDoc->RenderScene(mRenderContext);
}


void CCG2019112315蔡欣运GDI2DView::OnSize(UINT nType, int cx, int cy)
{
	CGDI2DView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (mRenderContext != nullptr)
		mRenderContext->setView(this);	//更新渲染环境
}


void CCG2019112315蔡欣运GDI2DView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nChar == VK_ESCAPE) //如果按下了ESC键，则中断当前的绘制命令（如果正在执行）
	{
		if (mCommand)
		{
				mCommand->Cancel();
			delete mCommand;
			mCommand = nullptr;
		}
	}
	if (mCommand) //命令模式
		mCommand->OnKeyDown(nChar, nRepCnt, nFlags);
	CGDI2DView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CCG2019112315蔡欣运GDI2DView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mCommand) //命令模式
		mCommand->OnKeyUp(nChar, nRepCnt, nFlags);
	CGDI2DView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CCG2019112315蔡欣运GDI2DView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mCommand)
		mCommand->OnLButtonDblClk(nFlags, Pos2i(point.x, point.y));
	CGDI2DView::OnLButtonDblClk(nFlags, point);
}


void CCG2019112315蔡欣运GDI2DView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mCommand)
		mCommand->OnLButtonDown(nFlags, Pos2i(point.x, point.y));
	CGDI2DView::OnLButtonDown(nFlags, point);
}


void CCG2019112315蔡欣运GDI2DView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mCommand)
		mCommand->OnLButtonUp(nFlags, Pos2i(point.x, point.y));
	CGDI2DView::OnLButtonUp(nFlags, point);
}


void CCG2019112315蔡欣运GDI2DView::OnMButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mCommand)
		mCommand->OnMButtonDblClk(nFlags, Pos2i(point.x, point.y));
	CGDI2DView::OnMButtonDblClk(nFlags, point);
}


void CCG2019112315蔡欣运GDI2DView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mCommand)
		mCommand->OnMButtonDown(nFlags, Pos2i(point.x, point.y));
	CGDI2DView::OnMButtonDown(nFlags, point);
}


void CCG2019112315蔡欣运GDI2DView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mCommand)
		mCommand->OnMButtonUp(nFlags, Pos2i(point.x, point.y));
	CGDI2DView::OnMButtonUp(nFlags, point);
}


void CCG2019112315蔡欣运GDI2DView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CGDI2DView::OnMouseHWheel(nFlags, zDelta, pt);
}


void CCG2019112315蔡欣运GDI2DView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CCG2019112315蔡欣运GDI2DDoc* pDoc = GetDocument();
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (pDoc != nullptr && pMainWnd != nullptr)
	{
		Vec2d v = pDoc->ViewPorttoWorld(Vec2i(point.x, point.y));
		CString str;
		str.Format(_T("视口坐标 ( %d, %d ) : 世界坐标 (%.2f , %.2f) "), point.x, point.y, v.x(), v.y());
		pMainWnd->ShowCoordOnStatusBar(str); //显示到状态栏
	}
	//命令模式，进一步根据当前的命令状态处理鼠标移动事件
	if (mCommand)
		mCommand->OnMouseMove(nFlags, Pos2i(point.x, point.y));
	CGDI2DView::OnMouseMove(nFlags, point);
}


BOOL CCG2019112315蔡欣运GDI2DView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mCommand)
		mCommand->OnMouseWheel(nFlags, zDelta, Pos2i(pt.x, pt.y));
	return CGDI2DView::OnMouseWheel(nFlags, zDelta, pt);
}


void CCG2019112315蔡欣运GDI2DView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mCommand)
		mCommand->OnRButtonDblClk(nFlags, Pos2i(point.x, point.y));
	CGDI2DView::OnRButtonDblClk(nFlags, point);
}


void CCG2019112315蔡欣运GDI2DView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (mCommand)
		mCommand->OnRButtonDown(nFlags, Pos2i(point.x, point.y));
	CGDI2DView::OnRButtonDown(nFlags, point);
}


void CCG2019112315蔡欣运GDI2DView::OnPointer()
{
	// TODO: 在此添加命令处理程序代码
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
}


void CCG2019112315蔡欣运GDI2DView::OnUpdatePointer(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(!mCommand);
}


void CCG2019112315蔡欣运GDI2DView::OnDrawLineseg()
{
	// TODO: 在此添加命令处理程序代码
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new Create2DLineSegment(this);
}


void CCG2019112315蔡欣运GDI2DView::OnUpdateDrawLineseg(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == cmd2dLineSegment);
}


void CCG2019112315蔡欣运GDI2DView::OnPickOne()
{
	// TODO: 在此添加命令处理程序代码
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new Pick2DRenderable(this);
}


void CCG2019112315蔡欣运GDI2DView::OnUpdatePickOne(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == cmd2dPickRenderable);
}


void CCG2019112315蔡欣运GDI2DView::OnPickAll()
{
	// TODO: 在此添加命令处理程序代码
	//场景树视图选中所有节点（这里没做处理）
	CCG2019112315蔡欣运GDI2DDoc* pDoc = GetDocument();
	if (pDoc)
		pDoc->scene()->RenderableSelectAll();
	Invalidate();
	UpdateWindow();
}


void CCG2019112315蔡欣运GDI2DView::OnPickNone()
{
	// TODO: 在此添加命令处理程序代码
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (pMainWnd)
		pMainWnd->UnselectSceneTree();
	CCG2019112315蔡欣运GDI2DDoc* pDoc = GetDocument();
	if (pDoc)
		pDoc->scene()->RenderableUnselectAll();
	Invalidate();
	UpdateWindow();
}


void CCG2019112315蔡欣运GDI2DView::OnDrawLine()
{
	// TODO: 在此添加命令处理程序代码
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new Create2DLine(this);
}


void CCG2019112315蔡欣运GDI2DView::OnUpdateDrawLine(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == cmd2dLine);
}


void CCG2019112315蔡欣运GDI2DView::OnDrawRay()
{
	// TODO: 在此添加命令处理程序代码
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new Create2DRay(this);
}

void CCG2019112315蔡欣运GDI2DView::OnUpdateDrawRay(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == cmd2dRay);
}

void CCG2019112315蔡欣运GDI2DView::OnDraw2dlineTime()
{
	// TODO: 在此添加命令处理程序代码
	if (mRenderContext == nullptr) return;
#ifdef USEMEMDC
	mRenderContext->setView(this);
#endif
	//mRenderContext->DDALine(Vec2i(100, 100), Vec2i(500), RGB(255, 0, 0));
	//生成一定数量的直线段的端点坐标
	//视口坐标0<x<1700,0<y<800
	const int pointCount = 10000;
	srand((unsigned)time(NULL));
	
	int randomP1[pointCount][2], randomP2[pointCount][2];
	for (int i = 0; i < pointCount; i++) {
		randomP1[i][0] = rand() % 1700;
		randomP2[i][0] = rand() % 1700;
		randomP1[i][1] = rand() % 800;
		randomP2[i][1] = rand() % 800;
	}
	//定义计时用的参数
	double fitDDA, fitMidPoint, fitBresenham;
	CString strFitin;
	LARGE_INTEGER frequency, start, end; //计时

	QueryPerformanceFrequency(&frequency); //滴答频率

	//DDA算法
	QueryPerformanceCounter(&start); //绘制前计时
	//绘制
	for (int i = 0; i < pointCount; i++) {
		mRenderContext->DDALine(Vec2i(randomP1[i][0], randomP1[i][1]), Vec2i(randomP2[i][0], randomP2[i][1]), RGB(0, 0, 0));
	}
	QueryPerformanceCounter(&end); //绘制结束计时
	//算出持续时间
	fitDDA = (double)(end.QuadPart - start.QuadPart) / (double)frequency.QuadPart;

	//MidPoint算法
	QueryPerformanceCounter(&start);
	for (int i = 0; i < pointCount; i++) {
		mRenderContext->MidPointLine(Vec2i(randomP1[i][0], randomP1[i][1]), Vec2i(randomP2[i][0], randomP2[i][1]), RGB(0, 0, 0));
	}
	QueryPerformanceCounter(&end);
	fitMidPoint = (double)(end.QuadPart - start.QuadPart) / (double)frequency.QuadPart;

	//Bresenham算法
	QueryPerformanceCounter(&start);
	for (int i = 0; i < pointCount; i++) {
		mRenderContext->BresenhamLine(Vec2i(randomP1[i][0], randomP1[i][1]), Vec2i(randomP2[i][0], randomP2[i][1]), RGB(0, 0, 0));
	}
	QueryPerformanceCounter(&end);
	fitBresenham = (double)(end.QuadPart - start.QuadPart) / (double)frequency.QuadPart;

	Invalidate();
	UpdateWindow();
	
	strFitin.Format(_T("DDALine：%.6f\nMidPoint：%.6f\nBresenham：%.6f"), fitDDA, fitMidPoint, fitBresenham);
	AfxMessageBox(strFitin);

#ifdef USEMEMDC
	((CGDI2DRenderContext*)mRenderContext)->SwapBackBuffer();
#endif
}


void CCG2019112315蔡欣运GDI2DView::OnDrawBrokenLine()
{
	// TODO: 在此添加命令处理程序代码
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new Create2DPolyLine(this);
}


void CCG2019112315蔡欣运GDI2DView::OnUpdateDrawBrokenLine(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == cmd2dPolyline);
}


void CCG2019112315蔡欣运GDI2DView::OnDrawCircle1pointRadius()
{
	// TODO: 在此添加命令处理程序代码
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new Create2DCircle1PointRadius(this);
}


void CCG2019112315蔡欣运GDI2DView::OnUpdateDrawCircle1pointRadius(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == cmd2dCircle1PointRadius);
}


void CCG2019112315蔡欣运GDI2DView::OnDrawCircle2pointDiameter()
{
	// TODO: 在此添加命令处理程序代码
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new Create2DCircle2PointDiameter(this);
}


void CCG2019112315蔡欣运GDI2DView::OnUpdateDrawCircle2pointDiameter(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == cmd2dCircle2PointDiameter);
}


void CCG2019112315蔡欣运GDI2DView::OnDrawCircle3point()
{
	// TODO: 在此添加命令处理程序代码
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new Create2DCircle3Point(this);
}


void CCG2019112315蔡欣运GDI2DView::OnUpdateDrawCircle3point(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == cmd2dCircle3Point);
}


void CCG2019112315蔡欣运GDI2DView::OnDrawPolygon()
{
	// TODO: 在此添加命令处理程序代码
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new Create2DPolygon(this);
	/*mRenderContext->setView(this);
	Vec2iArray pnts;
	pnts.push_back(Vec2i(100, 100));
	pnts.push_back(Vec2i(200, 250));
	pnts.push_back(Vec2i(100, 300));
	pnts.push_back(Vec2i(0, 200));
	mRenderContext->ScanLinePolygonFill(pnts, AFX_IDC_COLOR_BLACK);
	Invalidate();*/
}


void CCG2019112315蔡欣运GDI2DView::OnUpdateDrawPolygon(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == cmd2dPolygon);
}


void CCG2019112315蔡欣运GDI2DView::OnPickSeedPoint()
{
	// TODO: 在此添加命令处理程序代码
	if (mCommand)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
	mCommand = new Create2DSeedFill(this);
}


void CCG2019112315蔡欣运GDI2DView::OnUpdatePickSeedPoint(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(mCommand && mCommand->GetType() == cmd2dSeedFill);
}

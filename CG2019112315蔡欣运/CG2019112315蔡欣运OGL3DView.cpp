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

// CG2019112315蔡欣运OGL3DView.cpp: CCG2019112315蔡欣运OGL3DView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CG2019112315蔡欣运.h"
#endif

#include "CG2019112315蔡欣运OGL3DDoc.h"
#include "CG2019112315蔡欣运OGL3DView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCG2019112315蔡欣运OGL3DView

IMPLEMENT_DYNCREATE(CCG2019112315蔡欣运OGL3DView, CView)

BEGIN_MESSAGE_MAP(CCG2019112315蔡欣运OGL3DView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCG2019112315蔡欣运OGL3DView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CCG2019112315蔡欣运OGL3DView 构造/析构

CCG2019112315蔡欣运OGL3DView::CCG2019112315蔡欣运OGL3DView() noexcept
{
	// TODO: 在此处添加构造代码

}

CCG2019112315蔡欣运OGL3DView::~CCG2019112315蔡欣运OGL3DView()
{
}

BOOL CCG2019112315蔡欣运OGL3DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCG2019112315蔡欣运OGL3DView 绘图

void CCG2019112315蔡欣运OGL3DView::OnDraw(CDC* pDC)
{
	CCG2019112315蔡欣运OGL3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	pDC->MoveTo(100, 100); //默认画笔移到(100, 100)
	pDC->LineTo(500, 200); //默认画笔绘制到(500, 200)
}


// CCG2019112315蔡欣运OGL3DView 打印


void CCG2019112315蔡欣运OGL3DView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCG2019112315蔡欣运OGL3DView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCG2019112315蔡欣运OGL3DView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCG2019112315蔡欣运OGL3DView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CCG2019112315蔡欣运OGL3DView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCG2019112315蔡欣运OGL3DView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCG2019112315蔡欣运OGL3DView 诊断

#ifdef _DEBUG
void CCG2019112315蔡欣运OGL3DView::AssertValid() const
{
	CView::AssertValid();
}

void CCG2019112315蔡欣运OGL3DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCG2019112315蔡欣运OGL3DDoc* CCG2019112315蔡欣运OGL3DView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCG2019112315蔡欣运OGL3DDoc)));
	return (CCG2019112315蔡欣运OGL3DDoc*)m_pDocument;
}
#endif //_DEBUG


// CCG2019112315蔡欣运OGL3DView 消息处理程序

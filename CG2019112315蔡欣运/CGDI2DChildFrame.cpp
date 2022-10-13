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

// CGDI2DChildFrame.cpp: CGDI2DChildFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "CG2019112315蔡欣运.h"
#include "MainFrm.h"

#include "CGDI2DChildFrame.h"
#include "CG2019112315蔡欣运GDI2DDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGDI2DChildFrame

IMPLEMENT_DYNCREATE(CGDI2DChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CGDI2DChildFrame, CMDIChildWndEx)
	ON_COMMAND(ID_FILE_PRINT, &CGDI2DChildFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CGDI2DChildFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGDI2DChildFrame::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &CGDI2DChildFrame::OnUpdateFilePrintPreview)
	ON_WM_MDIACTIVATE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CGDI2DChildFrame 构造/析构

CGDI2DChildFrame::CGDI2DChildFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CGDI2DChildFrame::~CGDI2DChildFrame()
{
}


BOOL CGDI2DChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CGDI2DChildFrame 诊断

#ifdef _DEBUG
void CGDI2DChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CGDI2DChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CGDI2DChildFrame 消息处理程序

void CGDI2DChildFrame::OnFilePrint()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void CGDI2DChildFrame::OnFilePrintPreview()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // 强制关闭“打印预览”模式
	}
}

void CGDI2DChildFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_dockManager.IsPrintPreviewValid());
}


void CGDI2DChildFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
	CMDIChildWndEx::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);

	// TODO: 在此处添加消息处理程序代码
	if (bActivate)
	{
		CDocument* pDoc = this->GetActiveDocument();
		if (pDoc != nullptr)
		{
			if (pDoc->IsKindOf(RUNTIME_CLASS(CCG2019112315蔡欣运GDI2DDoc)))
			{
				CCG2019112315蔡欣运GDI2DDoc* doc = dynamic_cast<CCG2019112315蔡欣运GDI2DDoc*>(pDoc);
				CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
				pMainWnd->ShowSceneTree(doc->scene());
			}
			return;
		}
	}
}


void CGDI2DChildFrame::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	CDocument* pDoc = pMainWnd->GetActiveDocument();
	if (pDoc == nullptr)
		pMainWnd->ShowSceneTree(nullptr);
	CMDIChildWndEx::OnClose();
}

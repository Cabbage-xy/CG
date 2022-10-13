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

// COGL3DChildFrame.cpp: COGL3DChildFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "CG2019112315蔡欣运.h"

#include "COGL3DChildFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// COGL3DChildFrame

IMPLEMENT_DYNCREATE(COGL3DChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(COGL3DChildFrame, CMDIChildWndEx)
	ON_COMMAND(ID_FILE_PRINT, &COGL3DChildFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &COGL3DChildFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COGL3DChildFrame::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &COGL3DChildFrame::OnUpdateFilePrintPreview)
END_MESSAGE_MAP()

// COGL3DChildFrame 构造/析构

COGL3DChildFrame::COGL3DChildFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

COGL3DChildFrame::~COGL3DChildFrame()
{
}


BOOL COGL3DChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	if (!CMDIChildWndEx::PreCreateWindow(cs))
		return FALSE;

	return TRUE;
}

// COGL3DChildFrame 诊断

#ifdef _DEBUG
void COGL3DChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void COGL3DChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// COGL3DChildFrame 消息处理程序

void COGL3DChildFrame::OnFilePrint()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void COGL3DChildFrame::OnFilePrintPreview()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // 强制关闭“打印预览”模式
	}
}

void COGL3DChildFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_dockManager.IsPrintPreviewValid());
}

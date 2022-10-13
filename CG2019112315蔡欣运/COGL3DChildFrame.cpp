// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���  
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�  
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ������� 
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// COGL3DChildFrame.cpp: COGL3DChildFrame ���ʵ��
//

#include "pch.h"
#include "framework.h"
#include "CG2019112315������.h"

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

// COGL3DChildFrame ����/����

COGL3DChildFrame::COGL3DChildFrame() noexcept
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

COGL3DChildFrame::~COGL3DChildFrame()
{
}


BOOL COGL3DChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if (!CMDIChildWndEx::PreCreateWindow(cs))
		return FALSE;

	return TRUE;
}

// COGL3DChildFrame ���

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

// COGL3DChildFrame ��Ϣ�������

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
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // ǿ�ƹرա���ӡԤ����ģʽ
	}
}

void COGL3DChildFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_dockManager.IsPrintPreviewValid());
}

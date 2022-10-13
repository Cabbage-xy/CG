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

// CGDI3DChildFrame.cpp: CGDI3DChildFrame ���ʵ��
//

#include "pch.h"
#include "framework.h"
#include "CG2019112315������.h"

#include "CGDI3DChildFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGDI3DChildFrame

IMPLEMENT_DYNCREATE(CGDI3DChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CGDI3DChildFrame, CMDIChildWndEx)
	ON_COMMAND(ID_FILE_PRINT, &CGDI3DChildFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CGDI3DChildFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGDI3DChildFrame::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &CGDI3DChildFrame::OnUpdateFilePrintPreview)
END_MESSAGE_MAP()

// CGDI3DChildFrame ����/����

CGDI3DChildFrame::CGDI3DChildFrame() noexcept
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CGDI3DChildFrame::~CGDI3DChildFrame()
{
}


BOOL CGDI3DChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if (!CMDIChildWndEx::PreCreateWindow(cs))
		return FALSE;

	return TRUE;
}

// CGDI3DChildFrame ���

#ifdef _DEBUG
void CGDI3DChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CGDI3DChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CGDI3DChildFrame ��Ϣ�������

void CGDI3DChildFrame::OnFilePrint()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void CGDI3DChildFrame::OnFilePrintPreview()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // ǿ�ƹرա���ӡԤ����ģʽ
	}
}

void CGDI3DChildFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_dockManager.IsPrintPreviewValid());
}

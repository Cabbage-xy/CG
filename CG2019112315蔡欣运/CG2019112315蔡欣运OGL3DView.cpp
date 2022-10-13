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

// CG2019112315������OGL3DView.cpp: CCG2019112315������OGL3DView ���ʵ��
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CG2019112315������.h"
#endif

#include "CG2019112315������OGL3DDoc.h"
#include "CG2019112315������OGL3DView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCG2019112315������OGL3DView

IMPLEMENT_DYNCREATE(CCG2019112315������OGL3DView, CView)

BEGIN_MESSAGE_MAP(CCG2019112315������OGL3DView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCG2019112315������OGL3DView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CCG2019112315������OGL3DView ����/����

CCG2019112315������OGL3DView::CCG2019112315������OGL3DView() noexcept
{
	// TODO: �ڴ˴���ӹ������

}

CCG2019112315������OGL3DView::~CCG2019112315������OGL3DView()
{
}

BOOL CCG2019112315������OGL3DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CCG2019112315������OGL3DView ��ͼ

void CCG2019112315������OGL3DView::OnDraw(CDC* pDC)
{
	CCG2019112315������OGL3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	pDC->MoveTo(100, 100); //Ĭ�ϻ����Ƶ�(100, 100)
	pDC->LineTo(500, 200); //Ĭ�ϻ��ʻ��Ƶ�(500, 200)
}


// CCG2019112315������OGL3DView ��ӡ


void CCG2019112315������OGL3DView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCG2019112315������OGL3DView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CCG2019112315������OGL3DView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CCG2019112315������OGL3DView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CCG2019112315������OGL3DView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCG2019112315������OGL3DView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCG2019112315������OGL3DView ���

#ifdef _DEBUG
void CCG2019112315������OGL3DView::AssertValid() const
{
	CView::AssertValid();
}

void CCG2019112315������OGL3DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCG2019112315������OGL3DDoc* CCG2019112315������OGL3DView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCG2019112315������OGL3DDoc)));
	return (CCG2019112315������OGL3DDoc*)m_pDocument;
}
#endif //_DEBUG


// CCG2019112315������OGL3DView ��Ϣ�������

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

// CG2019112315蔡欣运GDI2DDoc.cpp: CCG2019112315蔡欣运GDI2DDoc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CG2019112315蔡欣运.h"
#endif

#include "MainFrm.h"
#include "CG2019112315蔡欣运GDI2DDoc.h"

#include <propkey.h>

//#include "CG2DCircle.h"
//#include "CG2DEllipse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCG2019112315蔡欣运GDI2DDoc

IMPLEMENT_DYNCREATE(CCG2019112315蔡欣运GDI2DDoc, CDocument)

BEGIN_MESSAGE_MAP(CCG2019112315蔡欣运GDI2DDoc, CDocument)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_COLOR, &CCG2019112315蔡欣运GDI2DDoc::OnUpdateBrushColor)
	ON_UPDATE_COMMAND_UI(ID_PEN_COLOR, &CCG2019112315蔡欣运GDI2DDoc::OnUpdatePenColor)
	ON_UPDATE_COMMAND_UI(ID_PEN_WIDTH, &CCG2019112315蔡欣运GDI2DDoc::OnUpdatePenWidth)
	ON_UPDATE_COMMAND_UI(ID_PEN_STYLE, &CCG2019112315蔡欣运GDI2DDoc::OnUpdatePenStyle)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_USE, &CCG2019112315蔡欣运GDI2DDoc::OnUpdateBrushUse)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_COLOR, &CCG2019112315蔡欣运GDI2DDoc::OnUpdateBrushColor)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_INDEX, &CCG2019112315蔡欣运GDI2DDoc::OnUpdateBrushIndex)
	ON_UPDATE_COMMAND_UI(ID_ALGORITHM_LINE, &CCG2019112315蔡欣运GDI2DDoc::OnUpdateAlgorithmLine)
	ON_UPDATE_COMMAND_UI(ID_ALGORITHM_CIRCLE, &CCG2019112315蔡欣运GDI2DDoc::OnUpdateAlgorithmCircle)
	ON_UPDATE_COMMAND_UI(ID_ALGORITHM_POLYGON, &CCG2019112315蔡欣运GDI2DDoc::OnUpdateAlgorithmPolygon)
	ON_UPDATE_COMMAND_UI(ID_ALGORITHM_SEED, &CCG2019112315蔡欣运GDI2DDoc::OnUpdateAlgorithmSeed)
END_MESSAGE_MAP()


// CCG2019112315蔡欣运GDI2DDoc 构造/析构

CCG2019112315蔡欣运GDI2DDoc::CCG2019112315蔡欣运GDI2DDoc() noexcept
{
	// TODO: 在此添加一次性构造代码
	//测试添加直线段到场景（要包含"CG2DLineSegment.h"），测试完毕后删除。
	//mScene.addRenderable(new CG2DLineSegment(Vec2d(100, 100), Vec2d(500, 200)));
	//mScene.addRenderable(new CG2DCircle(Vec2d(100, 100), 100));
	//mScene.addRenderable(new CG2DEllipse(Vec2d(100, 100), Vec2d(500, 200)));
}

CCG2019112315蔡欣运GDI2DDoc::~CCG2019112315蔡欣运GDI2DDoc()
{
}

BOOL CCG2019112315蔡欣运GDI2DDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CCG2019112315蔡欣运GDI2DDoc 序列化

void CCG2019112315蔡欣运GDI2DDoc::Serialize(CArchive& ar)
{
	mScene.Serialize(ar); //场景
	mCamera.Serialize(ar);//相机
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
		CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
		if (pMainWnd)
			pMainWnd->ShowSceneTree(&mScene);
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CCG2019112315蔡欣运GDI2DDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CCG2019112315蔡欣运GDI2DDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CCG2019112315蔡欣运GDI2DDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCG2019112315蔡欣运GDI2DDoc 诊断

#ifdef _DEBUG
void CCG2019112315蔡欣运GDI2DDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCG2019112315蔡欣运GDI2DDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCG2019112315蔡欣运GDI2DDoc 命令

bool CCG2019112315蔡欣运GDI2DDoc::addRenderable(CGRenderable* r)
{
	if (r && r->IsKindOf(RUNTIME_CLASS(CG2DRenderable)))
	{
		//return mScene.addRenderable(r);
		bool ret = mScene.addRenderable(r);
		if (ret)
		{
			CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
			if (pMainWnd)
				pMainWnd->ShowSceneTree(&mScene);
		}
		return ret;
	}
	return false;
}
bool CCG2019112315蔡欣运GDI2DDoc::delReaderable(CGRenderable* r)
{
	if (r && r->IsKindOf(RUNTIME_CLASS(CG2DRenderable)))
	{
		//return mScene.delRenderable(r);
		bool ret = mScene.delRenderable(r);
		if (ret)
		{
			CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
			if (pMainWnd)
				pMainWnd->ShowSceneTree(&mScene);
		}
		return ret;
	}
	return false;
}
//根据视口坐标获取对应场景坐标（二维）-调用场景类的ViewPortToWorld
Vec2d CCG2019112315蔡欣运GDI2DDoc::ViewPorttoWorld(const Vec2i& p)
{
	return mCamera.ViewPorttoWorld(p);
}
Vec2i CCG2019112315蔡欣运GDI2DDoc::WorldtoViewPort(const Vec2d& p)
{
	return mCamera.WorldtoViewPort(p);
}
//图形对象的拾取（二维图形）
bool CCG2019112315蔡欣运GDI2DDoc::UpdatePicked(const Vec2d& p, double radius)//更新选择
{
	if (mScene.UpdatePicked(p, radius) != nullptr)
		return true;
	return false;
}
bool CCG2019112315蔡欣运GDI2DDoc::AppendPicked(const Vec2d& p, double radius)//添加选择
{
	if (mScene.AppendPicked(p, radius) != nullptr)
		return true;
	return false;
}
bool CCG2019112315蔡欣运GDI2DDoc::RenderScene(CGRenderContext* pRC)
{
	if (pRC == nullptr || pRC->getView() == nullptr)
		return false;
	if (pRC->width() <= 0 && pRC->height() <= 0)
		return false;
	mCamera.setClientRect(0, 0, pRC->width(), pRC->height());
	mCamera.setViewPortBox(0, 0, pRC->width(), pRC->height());
	return mScene.Render(pRC, &mCamera);
}




void CCG2019112315蔡欣运GDI2DDoc::OnUpdatePenColor(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}


void CCG2019112315蔡欣运GDI2DDoc::OnUpdatePenWidth(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}


void CCG2019112315蔡欣运GDI2DDoc::OnUpdatePenStyle(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}


void CCG2019112315蔡欣运GDI2DDoc::OnUpdateBrushUse(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}


void CCG2019112315蔡欣运GDI2DDoc::OnUpdateBrushColor(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}


void CCG2019112315蔡欣运GDI2DDoc::OnUpdateBrushIndex(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}


void CCG2019112315蔡欣运GDI2DDoc::OnUpdateAlgorithmLine(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}


void CCG2019112315蔡欣运GDI2DDoc::OnUpdateAlgorithmCircle(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}


void CCG2019112315蔡欣运GDI2DDoc::OnUpdateAlgorithmPolygon(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}


void CCG2019112315蔡欣运GDI2DDoc::OnUpdateAlgorithmSeed(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}

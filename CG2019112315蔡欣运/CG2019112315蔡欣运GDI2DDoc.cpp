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
	//ON_UPDATE_COMMAND_UI(ID_BRUSH_USE, &CCG2019112315蔡欣运GDI2DDoc::OnUpdateBrushUse)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_COLOR, &CCG2019112315蔡欣运GDI2DDoc::OnUpdateBrushColor)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_INDEX, &CCG2019112315蔡欣运GDI2DDoc::OnUpdateBrushIndex)
	ON_UPDATE_COMMAND_UI(ID_ALGORITHM_LINE, &CCG2019112315蔡欣运GDI2DDoc::OnUpdateAlgorithmLine)
	ON_UPDATE_COMMAND_UI(ID_ALGORITHM_CIRCLE, &CCG2019112315蔡欣运GDI2DDoc::OnUpdateAlgorithmCircle)
	ON_UPDATE_COMMAND_UI(ID_ALGORITHM_POLYGON, &CCG2019112315蔡欣运GDI2DDoc::OnUpdateAlgorithmPolygon)
	ON_UPDATE_COMMAND_UI(ID_ALGORITHM_SEED, &CCG2019112315蔡欣运GDI2DDoc::OnUpdateAlgorithmSeed)
	ON_UPDATE_COMMAND_UI(ID_BOUND_COLOR, &CCG2019112315蔡欣运GDI2DDoc::OnUpdateBoundColor)
	ON_UPDATE_COMMAND_UI(ID_INNER_COLOR, &CCG2019112315蔡欣运GDI2DDoc::OnUpdateInnerColor)
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
	//mCamera.setClientRect(0, 0, pRC->width(), pRC->height());
	//mCamera.setViewPortBox(0, 0, pRC->width(), pRC->height());
	return mScene.Render(pRC, &mCamera);
}

//二维图形对象的几何变换（针对选择集中的对象）
bool CCG2019112315蔡欣运GDI2DDoc::Translate(double tx, double ty) //平移
{
	return mScene.Translate(tx, ty);
}
bool CCG2019112315蔡欣运GDI2DDoc::Rotate(double angle, double cx, double cy) //旋转（逆时针为正，度）
{
	return mScene.Rotate(angle, cx, cy);
}
bool CCG2019112315蔡欣运GDI2DDoc::Scale(double sx, double sy) //缩放
{
	return mScene.Scale(sx, sy);
}
bool CCG2019112315蔡欣运GDI2DDoc::Scale(double sx, double sy, double cx, double cy) //缩放（关于指定参考点缩放）
{
	return mScene.Scale(sx, sy, cx, cy);
}
bool CCG2019112315蔡欣运GDI2DDoc::Scale(double sx, double sy, double cx, double cy, const Vec2d& xDir)//缩放（指定参考点，缩放方向）
{
	return mScene.Scale(sx, sy, cx, cy, xDir);
}
bool CCG2019112315蔡欣运GDI2DDoc::MirrorXAxis() //关于X轴对称（二维、三维）
{
	return mScene.MirrorXAxis();
}
bool CCG2019112315蔡欣运GDI2DDoc::MirrorYAxis() //关于Y轴对称（二维、三维）
{
	return mScene.MirrorYAxis();
}
bool CCG2019112315蔡欣运GDI2DDoc::MirrorYeqPosX() //关于y=x对称（二维、三维）
{
	return mScene.MirrorYeqPosX();
}
bool CCG2019112315蔡欣运GDI2DDoc::MirrorYeNegPX() //关于y=-x对称（二维、三维）
{
	return mScene.MirrorYeNegPX();
}
bool CCG2019112315蔡欣运GDI2DDoc::MirrorOrigin() //关于原点对称（二维、三维）
{
	return mScene.MirrorOrigin();
}
bool CCG2019112315蔡欣运GDI2DDoc::ShearXAxis(double shx) //沿X轴错切
{
	return mScene.ShearXAxis(shx);
}
bool CCG2019112315蔡欣运GDI2DDoc::ShearYAxis(double shy) //沿Y轴错切
{
return mScene.ShearYAxis(shy);
}
bool CCG2019112315蔡欣运GDI2DDoc::ShearXYAxis(double shx, double shy) //沿X、Y轴错切
{
	return mScene.ShearXYAxis(shx, shy);
}
bool CCG2019112315蔡欣运GDI2DDoc::Transform(const Mat3d& mat) //几何变换（左乘给定矩阵）
{
	return mScene.Transform(mat);
}

//观察窗口宽度与视口宽度的比例
double CCG2019112315蔡欣运GDI2DDoc::WidthFactorWindowtoViewPort()
{
	return mCamera.WidthFactorWindowtoViewPort();
}
//观察窗口高度与视口高度的比例
double CCG2019112315蔡欣运GDI2DDoc::HeightFactorWindowtoViewPort()
{
	return mCamera.HeightFactorWindowtoViewPort();
}

//观察（二维）（注意在实现中要保持与视口高宽比一致）
void CCG2019112315蔡欣运GDI2DDoc::Move2DCamera(double tx, double ty) //平移观察窗口
{
	mCamera.Move(tx, ty);
}
void CCG2019112315蔡欣运GDI2DDoc::Zoom2DCamera(const Vec2d& lb, const Vec2d& rt) //观察窗口左下角、右上角
{
	mCamera.Zoom(lb, rt);
}
void CCG2019112315蔡欣运GDI2DDoc::Zoom2DCamera(double ratio) //给定观察窗口的缩放比例
{
	mCamera.Zoom(ratio);
}
void CCG2019112315蔡欣运GDI2DDoc::Rotate2DCamera(double degree) //转动相机（观察坐标系）
{
	mCamera.Rotate(degree);
}
void CCG2019112315蔡欣运GDI2DDoc::ShowAll2DCamera() //显示全部场景
{
	ABox2d box = mScene.BoundingABox();//先计算场景的范围
	if (box.isNull())
	{
		box.setMaxCorner(10000, 10000);
		box.setMinCorner(-10000, -10000);
	}
	mCamera.Zoom(box.minCorner(), box.maxCorner());
	mCamera.setEye(box.center().x(), box.center().y());
}
void CCG2019112315蔡欣运GDI2DDoc::Reset2DCamera() //重置到默认参数（二维）
{
	mCamera.Reset();
}
//客户区大小发生变换时，调整观察窗口与视口，并使高宽比相同，不产生变形
void CCG2019112315蔡欣运GDI2DDoc::ClientResized(int cx, int cy)
{
	mCamera.setClientRect(cx, cy); //客户区变化
}
//测试裁剪用（通过View类调用）;
void CCG2019112315蔡欣运GDI2DDoc::Clip(double xl, double yb, double xr, double yt)
{
	mScene.Clip(xl, yb, xr, yt, &mCamera);
}
void CCG2019112315蔡欣运GDI2DDoc::ClearClipResult() //清除裁剪结果集
{
	mScene.ClearClipResult();
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


//void CCG2019112315蔡欣运GDI2DDoc::OnUpdateBrushUse(CCmdUI* pCmdUI)
//{
//	// TODO: 在此添加命令更新用户界面处理程序代码
//	pCmdUI->Enable(true);
//}


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


void CCG2019112315蔡欣运GDI2DDoc::OnUpdateBoundColor(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}


void CCG2019112315蔡欣运GDI2DDoc::OnUpdateInnerColor(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(true);
}

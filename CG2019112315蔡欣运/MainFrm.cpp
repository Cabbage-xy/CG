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

// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "CG2019112315蔡欣运.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_WM_SETTINGCHANGE()
	ON_COMMAND(ID_VIEW_FILEVIEW, &CMainFrame::OnViewFileview)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FILEVIEW, &CMainFrame::OnUpdateViewFileview)
	ON_COMMAND(ID_VIEW_CLASSVIEW, &CMainFrame::OnViewClassview)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CLASSVIEW, &CMainFrame::OnUpdateViewClassview)
	ON_COMMAND(ID_VIEW_PROPERTIESWND, &CMainFrame::OnViewPropertieswnd)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PROPERTIESWND, &CMainFrame::OnUpdateViewPropertieswnd)
	ON_COMMAND(ID_VIEW_OUTPUTWND, &CMainFrame::OnViewOutputwnd)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OUTPUTWND, &CMainFrame::OnUpdateViewOutputwnd)
	ON_COMMAND(ID_BRUSH_USE, &CMainFrame::OnBrushUse)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_USE, &CMainFrame::OnUpdateBrushUse)
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // 其他可用样式...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // 设置为 FALSE 会将关闭按钮放置在选项卡区域的右侧
	mdiTabParams.m_bTabIcons = FALSE;    // 设置为 TRUE 将在 MDI 选项卡上启用文档图标
	mdiTabParams.m_bAutoColor = TRUE;    // 设置为 FALSE 将禁用 MDI 选项卡的自动着色
	mdiTabParams.m_bDocumentMenu = TRUE; // 在选项卡区域的右边缘启用文档菜单
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 加载菜单项图像(不在任何标准工具栏上): 
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// 创建停靠窗口
	if (!CreateDockingWindows())
	{
		TRACE0("未能创建停靠窗口\n");
		return -1;
	}

	m_wndFileView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndClassView.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndFileView);
	CDockablePane* pTabbedBar = nullptr;
	m_wndClassView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);
	m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndProperties);

	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);

	// 启用增强的窗口管理对话框
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// 将文档名和应用程序名称在窗口标题栏上的顺序进行交换。这
	// 将改进任务栏的可用性，因为显示的文档名带有缩略图。
	ModifyStyle(0, FWS_PREFIXTITLE);

	return 0;
}

//在状态栏上显示提示信息
void CMainFrame::ShowPrompt(const CString& str)
{
	m_wndStatusBar.GetElement(0)->SetText(str);
	m_wndStatusBar.Invalidate();
	m_wndStatusBar.UpdateWindow();
}

//在状态栏上显示视口坐标、世界坐标
void CMainFrame::ShowCoordOnStatusBar(const CString & str)
{
	m_wndStatusBar.GetExElement(0)->SetText(str);
	m_wndStatusBar.Invalidate();
	m_wndStatusBar.UpdateWindow();
}

//画笔属性
COLORREF CMainFrame::PenColor() const
{
	CMFCRibbonColorButton* pPenColor = (CMFCRibbonColorButton*)m_wndRibbonBar.FindByID(ID_PEN_COLOR);
	if (pPenColor)
		return pPenColor->GetColor();
	return RGB(0, 0, 0);
}
int CMainFrame::PenWidth() const
{
	CMFCRibbonEdit* pPenWidth = (CMFCRibbonEdit*)m_wndRibbonBar.FindByID(ID_PEN_WIDTH);
	if (pPenWidth)
		return _ttoi(pPenWidth->GetEditText());
	return 1;
}
int CMainFrame::PenStyle() const
{
	CMFCRibbonComboBox* pPenStyle = (CMFCRibbonComboBox*)m_wndRibbonBar.FindByID(ID_PEN_STYLE);
	if (pPenStyle)
		return pPenStyle->GetCurSel();
	return 0;
}
//画刷属性
bool CMainFrame::UseBrush() const
{
	CMFCRibbonCheckBox* pUseBrush = (CMFCRibbonCheckBox*)m_wndRibbonBar.FindByID(ID_BRUSH_USE);
	if (pUseBrush)
		return pUseBrush->IsChecked();
	return false;
}
COLORREF CMainFrame::BrushColor() const
{
	CMFCRibbonColorButton* pBrushColor =
		(CMFCRibbonColorButton*)m_wndRibbonBar.FindByID(ID_BRUSH_COLOR);
	if (pBrushColor)
		return pBrushColor->GetColor();
	return RGB(255, 255, 255);
}
int CMainFrame::BrushIndex() const
{
	CMFCRibbonComboBox* pBrushIndex = (CMFCRibbonComboBox*)m_wndRibbonBar.FindByID(ID_BRUSH_INDEX);
	if (pBrushIndex)
		return pBrushIndex->GetCurSel() - 1;
	return -1;
}
//画线算法
int CMainFrame::LineAlgorithm() const
{
	CMFCRibbonComboBox* pLineAlgorithm =
		(CMFCRibbonComboBox*)m_wndRibbonBar.FindByID(ID_ALGORITHM_LINE);
	if (pLineAlgorithm)
		return pLineAlgorithm->GetCurSel();
	return 0;
}
//圆弧算法
int CMainFrame::CircleAlgorithm() const
{
	CMFCRibbonComboBox* pCircleAlgorithm =
		(CMFCRibbonComboBox*)m_wndRibbonBar.FindByID(ID_ALGORITHM_CIRCLE);
	if (pCircleAlgorithm)
		return pCircleAlgorithm->GetCurSel();
	return 0;
}
//填充算法
int CMainFrame::FillAlgorithm() const
{
	CMFCRibbonComboBox* pFillAlgorithm =
		(CMFCRibbonComboBox*)m_wndRibbonBar.FindByID(ID_ALGORITHM_POLYGON);
	if (pFillAlgorithm)
		return pFillAlgorithm->GetCurSel();
	return 0;
}
int CMainFrame::SeedAlgorithm() const
{
	CMFCRibbonComboBox* pFillAlgorithm =
		(CMFCRibbonComboBox*)m_wndRibbonBar.FindByID(ID_ALGORITHM_SEED);
	if (pFillAlgorithm)
		return pFillAlgorithm->GetCurSel();
	return 0;
}
//点阵区域的边界颜色
COLORREF CMainFrame::BoundColor() const
{
	CMFCRibbonColorButton* pBoundColor =
		(CMFCRibbonColorButton*)m_wndRibbonBar.FindByID(ID_BOUND_COLOR);
		if (pBoundColor)
			return pBoundColor->GetColor();
	return RGB(0, 0, 0);
}
//点阵区域的内点颜色
COLORREF CMainFrame::FloodColor() const
{
	CMFCRibbonColorButton* pBackColor = (CMFCRibbonColorButton*)m_wndRibbonBar.FindByID(ID_INNER_COLOR);
	if (pBackColor)
		return pBackColor->GetColor();
	return RGB(255, 255, 255);
}

//根据激活的文档显示场景树到ClassView面板
void CMainFrame::ShowSceneTree(CGScene* scene)
{
	m_wndClassView.ShowSceneTree(scene);
}

void CMainFrame::UnselectSceneTree() //撤销场景树中的选择
{
	m_wndClassView.UnselectSceneTree();
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// 创建类视图
	CString strClassView;
	bNameValid = strClassView.LoadString(IDS_CLASS_VIEW);
	ASSERT(bNameValid);
	if (!m_wndClassView.Create(strClassView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“类视图”窗口\n");
		return FALSE; // 未能创建
	}

	// 创建文件视图
	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
	ASSERT(bNameValid);
	if (!m_wndFileView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“文件视图”窗口\n");
		return FALSE; // 未能创建
	}

	// 创建输出窗口
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建输出窗口\n");
		return FALSE; // 未能创建
	}

	// 创建属性窗口
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“属性”窗口\n");
		return FALSE; // 未能创建
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndFileView.SetIcon(hFileViewIcon, FALSE);

	HICON hClassViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndClassView.SetIcon(hClassViewIcon, FALSE);

	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

	UpdateMDITabbedBarsIcons();
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	m_wndOutput.UpdateFonts();
	RedrawWindow(nullptr, nullptr, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}


void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CMDIFrameWndEx::OnSettingChange(uFlags, lpszSection);
	m_wndOutput.UpdateFonts();
}


void CMainFrame::OnViewFileview()
{
	// TODO: 在此添加命令处理程序代码
	bool visible = m_wndFileView.IsVisible();
	if (visible)
		ShowPane(&m_wndFileView, FALSE, FALSE, FALSE);
	else
		ShowPane(&m_wndFileView, TRUE, FALSE, FALSE);
}
void CMainFrame::OnUpdateViewFileview(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	bool visible = m_wndFileView.IsVisible();
	pCmdUI->SetCheck(visible);
}
void CMainFrame::OnViewClassview()
{
	// TODO: 在此添加命令处理程序代码
	bool visible = m_wndClassView.IsVisible();
	if (visible)
		ShowPane(&m_wndClassView, FALSE, FALSE, FALSE);
	else
		ShowPane(&m_wndClassView, TRUE, FALSE, FALSE);
}
void CMainFrame::OnUpdateViewClassview(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	bool visible = m_wndClassView.IsVisible();
	pCmdUI->SetCheck(visible);
}
void CMainFrame::OnViewPropertieswnd()
{
	// TODO: 在此添加命令处理程序代码
	bool visible = m_wndProperties.IsVisible();
	if (visible)
		ShowPane(&m_wndProperties, FALSE, FALSE, FALSE);
	else
		ShowPane(&m_wndProperties, TRUE, FALSE, FALSE);
}
void CMainFrame::OnUpdateViewPropertieswnd(CCmdUI* pCmdUI)
{
		// TODO: 在此添加命令更新用户界面处理程序代码
		bool visible = m_wndProperties.IsVisible();
	pCmdUI->SetCheck(visible);
}
void CMainFrame::OnViewOutputwnd()
{
	// TODO: 在此添加命令处理程序代码
	bool visible = m_wndOutput.IsVisible();
	if (visible)
		ShowPane(&m_wndOutput, FALSE, FALSE, FALSE);
	else
		ShowPane(&m_wndOutput, TRUE, FALSE, FALSE);
}
void CMainFrame::OnUpdateViewOutputwnd(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	bool visible = m_wndOutput.IsVisible();
	pCmdUI->SetCheck(visible);
}


void CMainFrame::OnBrushUse()
{
	// TODO: 在此添加命令处理程序代码
	mBrushUse = !mBrushUse;
}


void CMainFrame::OnUpdateBrushUse(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(mBrushUse);
}

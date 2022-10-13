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

// CG2019112315蔡欣运GDI2DView.h: CCG2019112315蔡欣运GDI2DView 类的接口
//

#pragma once
#include"CGDI2DView.h"
#include"UIEventListener.h"

class CCG2019112315蔡欣运GDI2DView : public CGDI2DView //CView，修改原来的基类，也要修改cpp文件
{
protected: // 仅从序列化创建
	CCG2019112315蔡欣运GDI2DView() noexcept;
	DECLARE_DYNCREATE(CCG2019112315蔡欣运GDI2DView)

// 特性
public:
	CCG2019112315蔡欣运GDI2DDoc* GetDocument() const;

// 操作
public:
	//渲染场景
	virtual bool RenderScene();
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//图形对象的拾取（二维图形）
	virtual void UpdatePicked(const Vec2d& p, double radius); //更新选择
	virtual void AppendPicked(const Vec2d& p, double radius); //添加选择
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
public:
	//画笔属性
	virtual COLORREF PenColor() const;
	virtual int PenWidth() const;
	virtual int PenStyle() const;
	//画刷属性
	virtual bool UseBrush() const;
	virtual COLORREF BrushColor() const;
	virtual int BrushIndex() const;
	//画线算法
	virtual int LineAlgorithm() const;
	//圆弧算法
	virtual int CircleAlgorithm() const;
	//填充算法
	virtual int FillAlgorithm() const;
	virtual int SeedAlgorithm() const;
	//点阵区域的边界颜色
	virtual COLORREF BoundColor() const;
	//点阵区域的内点颜色
	virtual COLORREF FloodColor() const;
	//显示提示信息
	virtual void Prompt(const CString& str);
	//根据视口坐标获取对应场景坐标（二维）
	virtual Vec2d ViewPortToWorld(const Vec2i& p);
	virtual Vec2i WorldToViewPort(const Vec2d& p);
	//图形对象添加到场景，用于交互创建对象
	virtual bool addRenderable(CGRenderable* r);
	virtual bool delReaderable(CGRenderable* r);
// 实现
public:
	virtual ~CCG2019112315蔡欣运GDI2DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawCdc();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPointer();
	afx_msg void OnUpdatePointer(CCmdUI* pCmdUI);
	afx_msg void OnDrawLineseg();
	afx_msg void OnUpdateDrawLineseg(CCmdUI* pCmdUI);
	afx_msg void OnPickOne();
	afx_msg void OnUpdatePickOne(CCmdUI* pCmdUI);
	afx_msg void OnPickAll();
	afx_msg void OnPickNone();
	afx_msg void OnDrawLine();
	afx_msg void OnUpdateDrawLine(CCmdUI* pCmdUI);
	afx_msg void OnDrawRay();
	afx_msg void OnUpdateDrawRay(CCmdUI* pCmdUI);
	afx_msg void OnDraw2dlineTime();
	afx_msg void OnDrawBrokenLine();
	afx_msg void OnUpdateDrawBrokenLine(CCmdUI* pCmdUI);
	afx_msg void OnDrawCircle2pointDiameter();
	afx_msg void OnUpdateDrawCircle2pointDiameter(CCmdUI* pCmdUI);
	afx_msg void OnDrawCircle1pointRadius();
	afx_msg void OnUpdateDrawCircle1pointRadius(CCmdUI* pCmdUI);
	afx_msg void OnDrawCircle3point();
	afx_msg void OnUpdateDrawCircle3point(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // CG2019112315蔡欣运GDI2DView.cpp 中的调试版本
inline CCG2019112315蔡欣运GDI2DDoc* CCG2019112315蔡欣运GDI2DView::GetDocument() const
   { return reinterpret_cast<CCG2019112315蔡欣运GDI2DDoc*>(m_pDocument); }
#endif


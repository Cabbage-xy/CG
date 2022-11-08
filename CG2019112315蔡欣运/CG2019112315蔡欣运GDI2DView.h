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
	//观察窗口宽度与视口宽度的比例
	double WidthFactorWindowtoViewPort();
	//观察窗口高度与视口高度的比例
	double HeightFactorWindowtoViewPort();
	//观察（二维）（注意在实现中要保持与视口高宽比一致）
	virtual void Move2DCamera(double tx, double ty); //频移观察窗口
	virtual void Zoom2DCamera(const Vec2d& lb, const Vec2d& rt); //观察窗口左下角、右上角
	virtual void Zoom2DCamera(double ratio); //给定观察窗口的缩放比例（）
	virtual void Rotate2DCamera(double degree); //转动相机（观察坐标系）
	virtual void Reset2DCamera(); //重置到默认参数（二维）
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
	//二维图形对象的几何变换（针对选择集中的对象）
	virtual void Translate(double tx, double ty); //平移
	virtual void Rotate(double angle, double cx, double cy); //旋转（逆时针为正，度）
	virtual void Scale(double sx, double sy); //缩放
	virtual void Scale(double sx, double sy, double cx, double cy); //缩放（关于指定参考点缩放）
	virtual void Scale(double sx, double sy, double cx, double cy, const Vec2d& xDir); //缩放（指定参考点，缩放方向）
	virtual void ShearXYAxis(double shx, double shy); //沿X、Y轴错切


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
	afx_msg void OnDrawPolygon();
	afx_msg void OnUpdateDrawPolygon(CCmdUI* pCmdUI);
	afx_msg void OnPickSeedPoint();
	afx_msg void OnUpdatePickSeedPoint(CCmdUI* pCmdUI);
	afx_msg void OnTransformTranslateLeft();
	afx_msg void OnTransformTranslateRight();
	afx_msg void OnTransformTranslateUp();
	afx_msg void OnTransformTranslateDown();
	afx_msg void OnTransformRotateOrigin();
	afx_msg void OnTransformTranslateFree();
	afx_msg void OnTransformRotatePickPoint();
	afx_msg void OnTransformScaleUp();
	afx_msg void OnTransformScaleDown();
	afx_msg void OnTransformScale();
	afx_msg void OnTransformMirrorXAxis();
	afx_msg void OnTransformMirrorYAxis();
	afx_msg void OnTransformMirrorOrigin();
	afx_msg void OnTransformMirrorYEqPosX();
	afx_msg void OnTransformMirrorYEqNegPosX();
	afx_msg void OnTransformMirrorChooseLine();
	afx_msg void OnTransformShearXAxis();
	afx_msg void OnTransformShearYAxis();
	afx_msg void OnTransformShearXYAxis();
	afx_msg void OnTransformMatrix();
	afx_msg void OnUpdateTransformTranslateFree(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTransformRotatePickPoint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTransformScale(CCmdUI* pCmdUI);
	afx_msg void OnMoveViewpoint();
	afx_msg void OnUpdateMoveViewpoint(CCmdUI* pCmdUI);
	afx_msg void OnExtendView();
	afx_msg void OnNarrowView();
	afx_msg void OnResetCamera();
	afx_msg void OnShowAll();
};

#ifndef _DEBUG  // CG2019112315蔡欣运GDI2DView.cpp 中的调试版本
inline CCG2019112315蔡欣运GDI2DDoc* CCG2019112315蔡欣运GDI2DView::GetDocument() const
   { return reinterpret_cast<CCG2019112315蔡欣运GDI2DDoc*>(m_pDocument); }
#endif


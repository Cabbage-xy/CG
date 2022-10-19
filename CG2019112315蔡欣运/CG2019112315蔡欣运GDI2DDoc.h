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

// CG2019112315蔡欣运GDI2DDoc.h: CCG2019112315蔡欣运GDI2DDoc 类的接口
//


#include "CGDI2DScene.h"
#include "CGDI2DCamera.h"
#include "CGDI2DRenderContext.h"
#include "CG2DRenderable.h"

using namespace CG_NAMESPACE;
class CCG2019112315蔡欣运GDI2DDoc : public CDocument
{
protected: // 仅从序列化创建
	CCG2019112315蔡欣运GDI2DDoc() noexcept;
	DECLARE_DYNCREATE(CCG2019112315蔡欣运GDI2DDoc)
	// 特性
public:
	CGDI2DScene mScene; //场景
	CGDI2DCamera mCamera; //相机
	// 操作
public:
	//渲染场景到指定客户区
	bool RenderScene(CGRenderContext* pRC);
	//图形对象添加到场景
	bool addRenderable(CGRenderable* r);
	bool delReaderable(CGRenderable* r);
	//根据视口坐标获取对应场景坐标（二维）-调用相机类的ViewPortToWorld
	Vec2d ViewPorttoWorld(const Vec2i& p);
	Vec2i WorldtoViewPort(const Vec2d& p);
	CGScene* scene() { return &mScene; }
	//图形对象的拾取（二维图形）
	bool UpdatePicked(const Vec2d& p, double radius); //更新选择
	bool AppendPicked(const Vec2d& p, double radius); //添加选择
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CCG2019112315蔡欣运GDI2DDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnUpdatePenColor(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePenWidth(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePenStyle(CCmdUI* pCmdUI);
	//afx_msg void OnUpdateBrushUse(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBrushColor(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBrushIndex(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlgorithmLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlgorithmCircle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlgorithmPolygon(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlgorithmSeed(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBoundColor(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInnerColor(CCmdUI* pCmdUI);
};

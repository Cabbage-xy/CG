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
	//二维图形对象的几何变换
	bool Translate(double tx, double ty); //平移
	bool Rotate(double angle, double cx, double cy); //旋转（逆时针为正，度）
	bool Scale(double sx, double sy); //缩放（关于坐标原点缩放）
	bool Scale(double sx, double sy, double cx, double cy); //缩放（关于指定参考点缩放）
	bool Scale(double sx, double sy, double cx, double cy, const Vec2d& xDir); //缩放（指定参考点，缩放方向）
	bool MirrorXAxis(); //关于X轴对称（二维、三维）
	bool MirrorYAxis(); //关于Y轴对称（二维、三维）
	bool MirrorYeqPosX(); //关于y=x对称（二维、三维）
	bool MirrorYeNegPX(); //关于y=-x对称（二维、三维）
	bool MirrorOrigin(); //关于原点对称（二维、三维）
	bool ShearXAxis(double shx); //沿X轴错切
	bool ShearYAxis(double shy); //沿Y轴错切
	bool ShearXYAxis(double shx, double shy); //沿X、Y轴错切
	bool Transform(const Mat3d& mat); //几何变换（左乘给定矩阵）

	//观察窗口宽度与视口宽度的比例
	double WidthFactorWindowtoViewPort();
	//观察窗口高度与视口高度的比例
	double HeightFactorWindowtoViewPort();
	//观察（二维）（注意保持与视口高宽比一致）
	void Move2DCamera(double tx, double ty); //频移观察窗口
	void Zoom2DCamera(const Vec2d& lb, const Vec2d& rt); //观察窗口左下角、右上角
	void Zoom2DCamera(double ratio); //给定观察窗口的缩放比例（）
	void Rotate2DCamera(double degree); //转动相机（观察坐标系）
	void ShowAll2DCamera(); //显示全部场景
	void Reset2DCamera(); //重置到默认参数（二维）
	//客户区大小发生变换时，调整观察窗口与视口，并使高宽比相同，不产生变形
	void ClientResized(int cx, int cy);

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

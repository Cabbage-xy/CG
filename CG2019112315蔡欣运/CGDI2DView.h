#ifndef _CGDI2DVIEW_H_INCLUDED
#define _CGDI2DVIEW_H_INCLUDED
#include "CGView.h"
CG_NAMESPACE_ENTER
class CGDI2DView : public CGView
{
	DECLARE_DYNCREATE(CGDI2DView)
protected: // 仅从序列化创建
	CGDI2DView();
	// 操作
public:
	// 实现
public:
	virtual ~CGDI2DView();
	// 重写
public:
	virtual void OnInitialUpdate(); // 重写以创建绘制环境
};
CG_NAMESPACE_EXIT
#endif //_CGDI2DVIEW_H_INCLUDED
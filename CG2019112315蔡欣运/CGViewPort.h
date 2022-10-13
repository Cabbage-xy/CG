#ifndef _CGVIEWPORT_H_INCLUDED
#define _CGVIEWPORT_H_INCLUDED
#include "AABBox2.h"
#include "CGObject.h"
CG_NAMESPACE_ENTER
// 视口：绘图客户区中的一个矩形区域，默认情况视口占满客户区
class CGViewPort : public CGObject
{
	DECLARE_SERIAL(CGViewPort)
public:
	//默认构造（left=0, bottom=0, right=1, top=1）
	CGViewPort();
	CGViewPort(const CString& name);
	CGViewPort(const CGViewPort& vp);
	//构造（left、bottom、right、top）
	CGViewPort(int xl, int yb, int xr, int yt);
	//构造（left=0, bottom=0, right, top）
	CGViewPort(int xr, int yt);
	virtual ~CGViewPort() = default;
	virtual void Serialize(CArchive& ar);
	//设置函数，要确保minCorner是左下角、maxCorner是右上角
	//设置（left、bottom、right、top）
	void set(int xl, int yb, int xr, int yt);
	void setMinCorner(int xl, int yb);
	void setMaxCorner(int xr, int yt);
	void setLeft(int xl);
	void setBottom(int yb);
	void setRight(int xr);
	void setTop(int yt);
	const int left() const { return mViewPortBox.minCorner().x(); }
	const int bottom() const { return mViewPortBox.minCorner().y(); }
	const int right() const { return mViewPortBox.maxCorner().x(); }
	const int top() const { return mViewPortBox.maxCorner().y(); }
	int width() const { return mViewPortBox.width(); }
	int height() const { return mViewPortBox.height(); }
	const ABox2i& box() const { return mViewPortBox; }
protected:
	ABox2i mViewPortBox; //视口区域
};
CG_NAMESPACE_EXIT
#endif //_CGVIEWPORT_H_INCLUDED
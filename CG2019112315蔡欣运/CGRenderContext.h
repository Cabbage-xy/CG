#ifndef _CGRENDERCONTEXT_H_INCLUDED
#define _CGRENDERCONTEXT_H_INCLUDED
#include "Vector2.h"
#include "CGObject.h"
CG_NAMESPACE_ENTER
class CGView;//ʵ������ͼ��Ļ��࣬������������ֻ��Ҫ����ָ�룬������Ԥ������
class CGRenderContext : public CGObject
{
public:
	CGRenderContext();
	CGRenderContext(CGView* pView);
	virtual ~CGRenderContext();
	virtual void setView(CGView* pView);
	CGView* getView() const;
	//��������
	HWND hwnd() const { return mHWND; }
	HDC hdc() const { return mHDC; }
	HGLRC hglrc() const { return mHGLRC; }
	int width() const { return mWidth; }
	int height() const { return mHeight; }
public:
	//�㷨����
	//ֱ�߻����㷨
	static const int aLineCDC = 0; //ʹ��CDC���ֱ�߻��ƺ���
	static const int aLineDDA = 1; //DDA�����㷨
	static const int aLineMidPoint = 2; //�е㻭���㷨
	static const int aLineBresenham = 3; //Bresenham�����㷨
	//Բ�����㷨
	static const int aCircleCDC = 0; //ʹ��CDC��Ļ�Բ����
	static const int aCrcleMidPoint = 1; //�е㻭Բ�㷨
	static const int aCircleBresenham = 2; //Bresenham��Բ�㷨
	static const int aCirclePolygon = 3; //����αƽ���Բ
	//��Բ�����㷨
	static const int aEllipseCDC = 0; //ʹ��CDC��Ļ���Բ����
	static const int aEllipseMidPoint = 1; //�е㻭��Բ�㷨
	//���������㷨
	static const int aFillCDC = 0; //ʹ��CDC�����亯��
	static const int aFillScanlinePolygon = 1; //ɨ���߶��������㷨
	//�����������
	static const int aFillSeedCDC = 0; //ʹ��CDC�����亯��
	static const int aFillSeedBound4 = 1; //4��ͨ�߽���������㷨
	static const int aFillSeedBound8 = 2; //8��ͨ�߽���������㷨
	static const int aFillSeedFlood4 = 3; //4��ͨ�ڵ���������㷨
	static const int aFillSeedFlood8 = 4; //8��ͨ�ڵ���������㷨
	static const int aFillSeedScanline = 5; //ɨ������������㷨
public:
	//ֱ�߶λ����㷨
	virtual void DDALine(const Vec2i& start, const Vec2i& end, unsigned long color);
	virtual void DDALine(const Vec2i& start, const Vec2i& end, unsigned long color, int width);
	virtual void DDALine(const Vec2i& start, const Vec2i& end, unsigned long color, int width, int style);
	virtual void MidPointLine(const Vec2i& start, const Vec2i& end, unsigned long color);
	virtual void MidPointLine(const Vec2i& start, const Vec2i& end, unsigned long color, int width);
	virtual void MidPointLine(const Vec2i& start, const Vec2i& end, unsigned long color, int width, int style);
	virtual void BresenhamLine(const Vec2i& start, const Vec2i& end, unsigned long color);
	virtual void BresenhamLine(const Vec2i& start, const Vec2i& end, unsigned long color, int width);
	virtual void BresenhamLine(const Vec2i& start, const Vec2i& end, unsigned long color, int width, int style);
	
	//Բ�����㷨
	virtual void MidPointCircle(const Vec2i& center, int radius, unsigned long color);
	virtual void BresenhamCircle(const Vec2i& center, int radius, unsigned long color);
	/*
	virtual void CircleArc(const Vec2i& center, int radius, unsigned long color, float startAngle, float sweepAngle); //��ʱ��
	
	//��Բ�����㷨���������Բ��
	virtual void MidPointEllipse(const Vec2i& center, int a, int b, unsigned long color);
	virtual void EllipseArc(const Vec2i& center, int a, int b, unsigned long color, float startAngle, float sweepAngle); //��ʱ��
	//��Ч�߱�����ɨ��������㷨
	virtual void ScanLinePolygonFill(const Vec2iArray& pnts, unsigned long fillcolor);
	//�߽��ʾ����������㷨
	virtual void BoundFill4(int x, int y, unsigned long boundcolor, unsigned long fillcolor);
	virtual void BoundFill8(int x, int y, unsigned long boundcolor, unsigned long fillcolor);
	//�ڵ��ʾ����������㷨
	virtual void FloodFill4(int x, int y, unsigned long innercolor, unsigned long fillcolor);
	virtual void FloodFill8(int x, int y, unsigned long innercolor, unsigned long fillcolor);
	//ɨ������������㷨
	virtual void ScanLineSeedFill(int x, int y, unsigned long boundcolor, unsigned long fillcolor);*/
protected:
	CGView* mView; //ͨ����ͼ����Է��ʳ���������е�һЩ���ã����統ǰ���͡��߿�ȡ�
	HWND mHWND; //ͨ��mView����
	HDC mHDC; //ͨ��mView����
	HGLRC mHGLRC;//ͨ��mView���ã���άͼ����
	int mWidth, mHeight; //��ͼ�ͻ�������ͼ���ڵĿ��ߣ�
};
CG_NAMESPACE_EXIT
#endif //_CGRENDERCONTEXT_H_INCLUDED
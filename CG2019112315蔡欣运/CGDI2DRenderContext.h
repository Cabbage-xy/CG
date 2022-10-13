#ifndef _CGDI2DRENDERCONTEXT_H_INCLUDED
#define _CGDI2DRENDERCONTEXT_H_INCLUDED
#define USEMEMDC //��άͼ���Ƿ�ʹ���ڴ�DC��˫���棩
#include "CGRenderContext.h"
CG_NAMESPACE_ENTER
class CGDI2DView; //ʵ���ж�ά��ͼ��Ļ��࣬������������ֻ��Ҫ����ָ�룬������Ԥ������
class CGDI2DRenderContext : public CGRenderContext
{
public:
	CGDI2DRenderContext();
	CGDI2DRenderContext(CGDI2DView* pView);
	virtual ~CGDI2DRenderContext();
	//�Զ�������
	virtual void setView(CGView* pView); //���ǻ���setView
#ifdef USEMEMDC
	HDC hmemDC() const { return mMemDC; }
	HBITMAP hmemBMP() const { return mMemBMP; }
	void SwapBackBuffer();
#endif
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
	void CirclePlot(const Vec2i& center, int x, int y, unsigned long color); //������MidPoint��Bresenham�л��ư˸��Գ�λ�õ�����
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
#ifdef USEMEMDC
	//��άͼ���ã�˫����֧�֣�
	HDC mMemDC;
	HBITMAP mMemBMP;
#endif
};
CG_NAMESPACE_EXIT
#endif //_CGDI2DRENDERCONTEXT_H_INCLUDED
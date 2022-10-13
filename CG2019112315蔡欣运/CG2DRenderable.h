#ifndef _CG2DRENDERABLE_H_INCLUDED
#define _CG2DRENDERABLE_H_INCLUDED
#include "AABBox2.h"
#include "CGRenderable.h"
CG_NAMESPACE_ENTER
class CG2DRenderable : public CGRenderable
{
	DECLARE_SERIAL(CG2DRenderable)
public:
	CG2DRenderable();
	CG2DRenderable(const CString& name);
	virtual ~CG2DRenderable();
	//���л�
	virtual void Serialize(CArchive& ar);
	//һ���άͼ�����ԣ��߿����͡���ɫ��
	void setPenColor(COLORREF color);
	COLORREF penColor() const;
	void setPenWidth(int width);
	int penWidth() const;
	void setPenStyle(int style);
	int penStyle() const;
	//��ά���ͼ���������
	void setBrushUse(bool use);
	bool brushUse() const;
	void setBrushColor(COLORREF color);
	COLORREF brushColor() const;
	void setBrushIndex(int index);
	int brushIndex() const;
public:
	virtual void Render(CGRenderContext* pRC, CGCamera* pCamera); //���ƶ���ʹ��ָ�����
	//��άͼ�ζ����Χ��
	ABox2d& BoundingABox(); //AABB��Χ�У�����������
	virtual void computeBoundingBox(); //�����Χ�У���Ҫ����������ʵ��
	virtual bool Picked(const Vec2d& p, double radius); //����ά���Ƿ�ʰȡ��
protected:
	COLORREF mPenColor; //������ɫ
	int mPenWidth; //�����߿�
	int mPenStyle; //��������
	bool mBrushUse; //�Ƿ����
	COLORREF mBrushColor; //��ˢ��ɫ
	int mBrushIndex; //��ˢ����
	ABox2d mABox;//�������ΰ�Χ�У���Ҫ����mBoundsDirty�ж��Ƿ����¼���
};
CG_NAMESPACE_EXIT
#endif //_CG2DRENDERABLE_H_INCLUDED
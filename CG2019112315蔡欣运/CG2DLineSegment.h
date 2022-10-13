#ifndef _CG2DLINESEGMENT_H_INCLUDED
#define _CG2DLINESEGMENT_H_INCLUDED
#include "Vector2.h"
#include "CG2DRenderable.h"
CG_NAMESPACE_ENTER
class CG2DLineSegment : public CG2DRenderable
{
	DECLARE_SERIAL(CG2DLineSegment)
public:
	CG2DLineSegment();
	CG2DLineSegment(const Vec2d& s, const Vec2d& e); //�������㹹��
	CG2DLineSegment(const Vec2d& s, const Vec2d& dir, double length); //������㡢���򡢳��ȹ���
	CG2DLineSegment(const CG2DLineSegment& other);
	virtual ~CG2DLineSegment();
	//���л�
	virtual void Serialize(CArchive& ar);
public:
	virtual void Render(CGRenderContext* pRC, CGCamera* pCamera); //���ƶ���ʹ��ָ�����
	virtual void computeBoundingBox(); //�����Χ��
	virtual bool Picked(const Vec2d& p, double radius); //�Ƿ�ʰȡ��
protected:
	Vec2d mStart, mEnd; //��㡢�յ�����
};
CG_NAMESPACE_EXIT
#endif //_CG2DLINESEGMENT_H_INCLUDED
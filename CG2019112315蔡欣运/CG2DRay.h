#ifndef _CG2DRay_H_INCLUDED
#define _CG2DRay_H_INCLUDED
#include "Vector2.h"
#include "CG2DRenderable.h"
CG_NAMESPACE_ENTER
class CG2DRay : public CG2DRenderable
{
	DECLARE_SERIAL(CG2DRay)
public:
	CG2DRay();
	CG2DRay(const Vec2d& s, const Vec2d& e); //�������㹹��
	//CG2DRay(const Vec2d& s, const Vec2d& dir); //������㡢���򹹽�
	CG2DRay(const CG2DRay& other);
	virtual ~CG2DRay();
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
#endif //_CG2DRay_H_INCLUDED
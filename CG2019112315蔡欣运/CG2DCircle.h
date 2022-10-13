#ifndef _CG2DCIRCLE_H_INCLUDED
#define _CG2DCIRCLE_H_INCLUDED

#include "Vector2.h"
#include "CG2DRenderable.h"
CG_NAMESPACE_ENTER
class CG2DCircle : public CG2DRenderable
{
	DECLARE_SERIAL(CG2DCircle)
public:
	CG2DCircle();
	CG2DCircle(const Vec2d& c, const double r); //����Բ�ĺͰ뾶����
	CG2DCircle(const Vec2d& m1, const Vec2d& m2); //��ֱ�߶�Ϊֱ������
	CG2DCircle(const CG2DCircle& other);
	virtual ~CG2DCircle();
	//���л�
	virtual void Serialize(CArchive& ar);
public:
	virtual void Render(CGRenderContext* pRC, CGCamera* pCamera); //���ƶ���ʹ��ָ�����
protected:
	Vec2d mCenter; //Բ������
	double r;	//�뾶
};
CG_NAMESPACE_EXIT
#endif //_CG2DCIRCLE_H_INCLUDED
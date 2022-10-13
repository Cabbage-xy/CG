#ifndef _CG2DPOLYLINE_H_INCLUDED
#define _CG2DPOLYLINE_H_INCLUDED
#include "Vector2.h"
#include "CG2DRenderable.h"
CG_NAMESPACE_ENTER
class CG2DPolyLine : public CG2DRenderable
{
	DECLARE_SERIAL(CG2DPolyLine)
public:
	CG2DPolyLine();
	CG2DPolyLine(const std::vector<Vec2d>& points); //���ݵ㼯��˳�򹹽�
	CG2DPolyLine(const CG2DPolyLine& other);
	virtual ~CG2DPolyLine();
	//���л�
	virtual void Serialize(CArchive& ar);
public:
	virtual void Render(CGRenderContext* pRC, CGCamera* pCamera); //���ƶ���ʹ��ָ�����
	virtual void computeBoundingBox(); //�����Χ��
	virtual bool Picked(const Vec2d& p, double radius); //�Ƿ�ʰȡ��
protected:
	std::vector<Vec2d> mPoints; //���ߵ����꼯��
};
CG_NAMESPACE_EXIT
#endif //_CG2DPOLYLINE_H_INCLUDED
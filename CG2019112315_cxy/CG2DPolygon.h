#ifndef _CG2DPOLYGON_H_INCLUDED
#define _CG2DPOLYGON_H_INCLUDED

#include "Vector2.h"
#include "CG2DRenderable.h"
CG_NAMESPACE_ENTER
class CG2DPolygon : public CG2DRenderable
{
	DECLARE_SERIAL(CG2DPolygon)
public:
	CG2DPolygon();
	CG2DPolygon(const std::vector<Vec2d> points); //����Բ�ĺͰ뾶����
	CG2DPolygon(const CG2DPolygon& other);
	virtual ~CG2DPolygon();
	//���л�
	virtual void Serialize(CArchive& ar);
public:
	virtual void Render(CGRenderContext* pRC, CGCamera* pCamera); //���ƶ���ʹ��ָ�����
protected:
	std::vector<Vec2d> mPoints; //
};
CG_NAMESPACE_EXIT
#endif //_CG2DPOLYGON_H_INCLUDED
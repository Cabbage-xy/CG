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
public:
	virtual void computeBoundingBox();
public:
	//��άͼ�ζ���ļ��α任����Ҫ����������������д��
	virtual void Translate(double tx, double ty); //ƽ��
	virtual void Rotate(double angle, double cx, double cy); //��ת����ʱ��Ϊ�����ȣ�
	virtual void Scale(double sx, double sy); //���ţ���������ԭ�����ţ�
	virtual void Scale(double sx, double sy, double cx, double cy); //���ţ�����ָ���ο������ţ�
	virtual void Scale(double sx, double sy, double cx, double cy, const Vec2d& xDir); //���ţ�ָ���ο��㣬���ŷ���
	virtual void MirrorXAxis(); //����X��Գƣ���ά����ά��
	virtual void MirrorYAxis(); //����Y��Գƣ���ά����ά��
	virtual void MirrorYeqPosX(); //����y=x�Գƣ���ά����ά��
	virtual void MirrorYeNegPX(); //����y=-x�Գƣ���ά����ά��
	virtual void MirrorOrigin(); //����ԭ��Գƣ���ά����ά��
	virtual void ShearXAxis(double shx); //��X�����
	virtual void ShearYAxis(double shy); //��Y�����
	virtual void ShearXYAxis(double shx, double shy); //��X��Y�����
	virtual void Transform(const Mat3d& mat); //���α任����˸�������
protected:
	std::vector<Vec2d> mPoints; //
};
CG_NAMESPACE_EXIT
#endif //_CG2DPOLYGON_H_INCLUDED
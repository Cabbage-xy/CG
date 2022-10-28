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
	Vec2d mStart, mEnd; //��㡢�յ�����
};
CG_NAMESPACE_EXIT
#endif //_CG2DLINESEGMENT_H_INCLUDED
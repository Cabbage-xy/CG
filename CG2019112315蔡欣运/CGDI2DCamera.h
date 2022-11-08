#ifndef _CGDI2DCAMERA_H_INCLUDED
#define _CGDI2DCAMERA_H_INCLUDED
#include "CGCamera.h"
CG_NAMESPACE_ENTER
class CGDI2DCamera : public CGCamera
{
	DECLARE_SERIAL(CGDI2DCamera)
public:
	CGDI2DCamera();
	CGDI2DCamera(const CString& name);
	virtual ~CGDI2DCamera() = default;
	//���л�
	virtual void Serialize(CArchive& ar);
	//��ʼ�����
	virtual void InitCamera();
	//��������ϵת�����ӿڣ���ά��
	virtual Vec2i WorldtoViewPort(const Vec2d& p);
	//�ӿ�ת������������ϵ����ά��
	virtual Vec2d ViewPorttoWorld(const Vec2i& p);

public://�������
	//������ƣ��۲���ƣ�
	virtual void Move(double tx, double ty); //�ƶ��۲�����ϵ����ά��
	virtual void Zoom(double ratio); //�۲촰�����ţ���ά��
	virtual void Zoom(const Vec2d& lb, const Vec2d& rt); //�۲촰�����ţ���ά��
	virtual void Rotate(double degree); //��ת�۲�����ϵ��������ϵԭ�㣩����ά��
	virtual void Reset(); //���õ�Ĭ�ϲ�������ά��
public:
	bool CohenSutherlandLineClip(double xl, double yb, double xr, double yt, const Vec2d& s, const Vec2d& e, Vec2d& rs, Vec2d& re) override;


protected://�۲�任
//��άͼ�ι۲�任����������ϵ���۲�����ϵ������ά��
	virtual Vec2d WCStoVCS(const Vec2d& p);
	//��άͼ�δ��ӱ任���۲�����ϵ���淶���豸����ϵ������ά����ʵ����ʹ�������豸����ϵ����淶���豸����ϵ��
	virtual Vec2d VCStoNCS(const Vec2d& p);
	//��άͼ���ӿڱ任���淶���豸����ϵ���豸����ϵ������ά����ʵ����ʹ�������豸����ϵ����淶���豸����ϵ��
	virtual Vec2i NCStoDCS(const Vec2d& p);
	//�豸����ϵ���淶���豸����ϵ����ά����ʵ����ʹ�������豸����ϵ����淶���豸����ϵ��
	virtual Vec2d DCStoNCS(const Vec2i& p);
	//�淶���豸����ϵ���۲�����ϵ����ά����ʵ����ʹ�������豸����ϵ����淶���豸����ϵ��
	virtual Vec2d NCStoVCS(const Vec2d& p);
	//�۲�����ϵ����������ϵ����ά��
	virtual Vec2d VCStoWCS(const Vec2d& p);
protected:
};
CG_NAMESPACE_EXIT
#endif //_CGDI2DCAMERA_H_INCLUDED
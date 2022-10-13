#ifndef _CGCAMERA_H_INCLUDED
#define _CGCAMERA_H_INCLUDED
#include "AABBox2.h"
#include "CGViewPort.h"
CG_NAMESPACE_ENTER
class CGCamera : public CGObject
{
	DECLARE_SERIAL(CGCamera)
public:
	CGCamera();
	CGCamera(const CString& name);
	virtual ~CGCamera() = default;
	//���л�
	virtual void Serialize(CArchive& ar);
	//��ʼ�����
	virtual void InitCamera();
	//�ӿڣ���ά����ά��
	virtual void setViewPortBox(int xl, int yb, int xr, int yt);
	virtual void setViewPort(const CGViewPort& vp);
	//�ͻ�������ά����ά��
	virtual void setClientRect(int xl, int yb, int xr, int yt);
	virtual void setClientRect(const ABox2i& rc);
	//��������ϵת�����ӿڣ���ά��
	virtual Vec2i WorldtoViewPort(const Vec2d& p);
		//�ӿ�ת������������ϵ����ά��
		virtual Vec2d ViewPorttoWorld(const Vec2i & p);
protected:
	CGViewPort mViewPort; //��Ӧ�ӿڣ����豸����ϵ���ͻ������ж���
	ABox2i mClienRect; //��ͼ�ͻ�������
};
CG_NAMESPACE_EXIT
#endif //_CGCAMERA_H_INCLUDED
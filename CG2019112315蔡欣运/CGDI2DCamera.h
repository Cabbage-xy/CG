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
protected:
};
CG_NAMESPACE_EXIT
#endif //_CGDI2DCAMERA_H_INCLUDED
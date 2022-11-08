#include "pch.h"
#include "CGDI2DCamera.h"
CG_NAMESPACE_ENTER
IMPLEMENT_SERIAL(CGDI2DCamera, CGCamera, 1)
CGDI2DCamera::CGDI2DCamera()
	:CGCamera(CString("CGDI2DCamera"))
{
}
CGDI2DCamera::CGDI2DCamera(const CString& name)
	: CGCamera(CString(name))
{
}
void CGDI2DCamera::Serialize(CArchive& ar)
{
	CGCamera::Serialize(ar);
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}
void CGDI2DCamera::InitCamera()
{
}
//��������ϵת�����ӿڣ���ά��
Vec2i CGDI2DCamera::WorldtoViewPort(const Vec2d& p)
{
	//�˴���ӳ��ʵ�����ڲ��ԣ���������ϵ���ڿͻ������½ǣ�x���ң�y���ϡ�
	//�۲촰�����ӿ�һ���Ĵ�С���ӿ���ͻ����ص�
	//return Vec2i(int(p.x()), int(-p.y()) + mClienRect.height());
	//��������ϵ�ڿͻ������ģ�x���ң�y���ϡ�
	return Vec2i(int(p.x()+ mClienRect.width()/2.0), int(-p.y() + mClienRect.height()/2.0));
}
//�ӿ�ת������������ϵ����ά��
Vec2d CGDI2DCamera::ViewPorttoWorld(const Vec2i& p)
{
	//�˴���ӳ��ʵ�����ڲ��ԣ���������ϵ���ڿͻ������½ǣ�x���ң�y���ϡ�
	//�۲촰�����ӿ�һ���Ĵ�С���ӿ���ͻ����ص�
	//return Vec2d(p.x(), double(mClienRect.height()) - p.y());
	//��������ϵ�ڿͻ������ģ�x���ң�y���ϡ�
	return Vec2d(p.x() - mClienRect.width()/2.0, mClienRect.height()/2.0 - p.y());
}
CG_NAMESPACE_EXIT

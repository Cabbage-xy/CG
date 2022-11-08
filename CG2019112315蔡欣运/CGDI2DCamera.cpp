#include "pch.h"
#include "CGDI2DCamera.h"
#include "Vector3.h"
#include "Matrix33.h"
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
	CGCamera::InitCamera();
}
//��������ϵת�����ӿڣ���ά��
Vec2i CGDI2DCamera::WorldtoViewPort(const Vec2d& p)
{
	//�˴���ӳ��ʵ�����ڲ��ԣ���������ϵ���ڿͻ������½ǣ�x���ң�y���ϡ�
	//�۲촰�����ӿ�һ���Ĵ�С���ӿ���ͻ����ص�
	//return Vec2i(int(p.x()), int(-p.y()) + mClienRect.height());
	//��������ϵ�ڿͻ������ģ�x���ң�y���ϡ�
	//return Vec2i(int(p.x()+ mClienRect.width()/2.0), int(-p.y() + mClienRect.height()/2.0));
	Vec2d v(p);
	v = WCStoVCS(v);//��������ϵ���۲�����ϵ
	v = VCStoNCS(v);//�۲�����ϵ�������豸����ϵ
	return NCStoDCS(v);//�����豸����ϵ���豸����ϵ
}
//�ӿ�ת������������ϵ����ά��
Vec2d CGDI2DCamera::ViewPorttoWorld(const Vec2i& p)
{
	//�˴���ӳ��ʵ�����ڲ��ԣ���������ϵ���ڿͻ������½ǣ�x���ң�y���ϡ�
	//�۲촰�����ӿ�һ���Ĵ�С���ӿ���ͻ����ص�
	//return Vec2d(p.x(), double(mClienRect.height()) - p.y());
	//��������ϵ�ڿͻ������ģ�x���ң�y���ϡ�
	//return Vec2d(p.x() - mClienRect.width()/2.0, mClienRect.height()/2.0 - p.y());
	Vec2d v = DCStoNCS(p);//�����豸����ϵ���豸����ϵ
	v = NCStoVCS(v);//�۲�����ϵ�������豸����ϵ
	return VCStoWCS(v);//��������ϵ���۲�����ϵ
}

//������ƣ��۲���ƣ�
void CGDI2DCamera::Move(double tx, double ty) //�ƶ��۲�����ϵ����ά��
{
	mEyeX += tx;
	mEyeY += ty;
}
//�۲촰�����ţ���������ͬ�������ţ����ڿ�߱����ӿڿ�߱���ͬ��
void CGDI2DCamera::Zoom(double ratio)
{
	if (ratio < 0)
		return;
	double xc = (mLeft + mRight) / 2.0;
	double yc = (mBottom + mTop) / 2.0;
	double w = (mRight - mLeft) / 2.0;
	double h = (mTop - mBottom) / 2.0;
	mLeft = xc - w * ratio;
	mRight = xc + w * ratio;
	mBottom = yc - h * ratio;
	mTop = yc + h * ratio;
}

//�۲촰�����ţ����ڿ�߱����ӿڿ�߱���ͬ�������ڽ�����ȡ�۲촰�ڣ��ڿͻ����п����
void CGDI2DCamera::Zoom(const Vec2d& lb, const Vec2d& rt)
{
	////�ӿڿ�߱�
	//double aspect = double(mViewPort.width()) / double(mViewPort.height());
	//double h = rt.y() - lb.y();
	////double w = rt.x() - lb.x();
	//double w = aspect * h;//�Ը߶�Ϊ��׼�����ֹ۲촰�����ӿڵĸ߿����ͬ��ʹ�۲�Ч��������
	//mBottom = lb.y();
	//mTop = rt.y();
	//mLeft = -w / 2;
	//mRight = w / 2;
	
	//�ӿڿ�߱�
	double aspectViewPort = double(mViewPort.width()) / double(mViewPort.height());
	//��ֹΪ0
	if (rt.y() - lb.y() == 0) return;
	double aspectZoomBox = abs((rt.x() - lb.x()) / (rt.y() - lb.y()));

	double w, h;
	if (aspectViewPort > aspectZoomBox)
	{
		h = abs(rt.y() - lb.y());
		w = aspectViewPort * h; //�Ը߶�Ϊ��׼�����ֹ۲촰�����ӿڵĸ߿����ͬ��ʹ�۲�Ч��������
	}
	else
	{
		w = abs(rt.x() - lb.x());
		h = w / aspectViewPort; //�Կ��Ϊ��׼�����ֹ۲촰�����ӿڵĸ߿����ͬ��ʹ�۲�Ч��������
	}
	mBottom = -h / 2;
	mTop = h / 2;
	mLeft = -w / 2;
	mRight = w / 2;
}

void CGDI2DCamera::Rotate(double degree) //��ת�۲�����ϵ������������ϵԭ�㣬��ʱ�뷽��Ϊ������λ���ȣ�
{
	Mat3d mat = Mat3d::getRotation(degree);
	Vec3d vec = operator *(mat, Vec3d(mUpX, mUpY, 1)); //�۲�����ϵY����������������ʾ��mUpX,mUpY, 1��
	mUpX = vec.x();
	mUpY = vec.y();
}
void CGDI2DCamera::Reset() //���õ�Ĭ�ϲ���
{
	//�˴��������۲�����ϵ�����ֹ۲촰�ڲ���
	mEyeX = 0.0;
	mEyeY = 0.0;
	mUpX = 0.0;
	mUpY = 1.0;
}
//��άͼ�ι۲�任����������ϵ���۲�����ϵ������ά�� ���ƶ��۲�����ϵ
Vec2d CGDI2DCamera::WCStoVCS(const Vec2d& p)
{
	//��������ԭ���ڴ�������
	int x = p.x() - mEyeX; //ת��Ϊ�۲�����
	int y = p.y() - mEyeY;
	Vec2d v(x, y);
	double degrees = atan(mUpX / mUpY); //�۲�����ϵ����������ϵ�ļн�
	Mat3d mat = Mat3d::getRotation(degrees);//��������ϵת��Ϊ�۲�����ϵ���۲�����ϵ�������ʱ����ת
	v = operator*(mat, v);
	return v;
}

//��άͼ�δ��ӱ任���۲�����ϵ�������豸����ϵ������ά����ʵ����ʹ�������豸����ϵ����淶���豸����ϵ��
Vec2d CGDI2DCamera::VCStoNCS(const Vec2d& p)
{
	return Vec2d(p.x() / WidthFactorWindowtoViewPort(), p.y() / HeightFactorWindowtoViewPort());
}

//��άͼ���ӿڱ任�������豸����ϵ���豸����ϵ������ά����ʵ����ʹ�������豸����ϵ����淶���豸����ϵ��
Vec2i CGDI2DCamera::NCStoDCS(const Vec2d& p)
{
	Vec2i v(p.x() + (double)mClienRect.width() / 2, -p.y() + (double)mClienRect.height() / 2); //�����겻�䣬�����귭ת
	return v;
}
//�豸����ϵ�������豸����ϵ����ά����ʵ����ʹ�������豸����ϵ����淶���豸����ϵ��
Vec2d CGDI2DCamera::DCStoNCS(const Vec2i& p)
{
	Vec2d v((p.x() - (double)mClienRect.width() / 2), (-p.y() + (double)mClienRect.height() / 2));
	return v;
}
//�����豸����ϵ���۲�����ϵ����ά����ʵ����ʹ�������豸����ϵ����淶���豸����ϵ��
Vec2d CGDI2DCamera::NCStoVCS(const Vec2d& p)
{
	return Vec2d(p.x() * WidthFactorWindowtoViewPort(), p.y() * HeightFactorWindowtoViewPort());
}
//�۲�����ϵ����������ϵ����ά��
Vec2d CGDI2DCamera::VCStoWCS(const Vec2d& p)
{
	int x = p.x() + mEyeX; //ת��Ϊ�۲�����
	int y = p.y() + mEyeY;
	Vec2d v(x, y);
	double degrees = atan(mUpX / mUpY); //�۲�����ϵ����������ϵ�ļн�
	Mat3d mat = Mat3d::getRotation(-degrees);//�۲�����ϵת��Ϊ��������ϵ����������ϵ�����˳ʱ����ת
	v = operator*(mat, v);
	return v;
}
CG_NAMESPACE_EXIT

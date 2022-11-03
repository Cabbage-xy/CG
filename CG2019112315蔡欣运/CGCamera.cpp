#include "pch.h"
#include "CGCamera.h"
CG_NAMESPACE_ENTER
IMPLEMENT_SERIAL(CGCamera, CGObject, 1)
CGCamera::CGCamera()
	:CGObject(CString("CGCamera"))
	, mViewPort(0, 0, 1, 1) //��Ҫ���ݾ������ý����޸�
	, mClienRect(Vec2i(0, 0), Vec2i(1, 1), 0) //��Ҫ���ݾ������ý����޸�
{
	InitCamera();
}
CGCamera::CGCamera(const CString& name)
	: CGObject(CString(name))
	, mViewPort(0, 0, 1, 1) //��Ҫ���ݾ������ý����޸�
	, mClienRect(Vec2i(0, 0), Vec2i(1, 1), 0) //��Ҫ���ݾ������ý����޸�
{
	InitCamera();
}

void CGCamera::InitCamera()
{
	mLeft = -1000.0;
	mBottom = -1000.0;
	mRight = 1000.0;
	mTop = 1000.0;
	mEyeX = 0.0;
	mEyeY = 0.0;
	mUpX = 0.0;
	mUpY = 1.0;
	//��������ʵ��������ʼ��
}
void CGCamera::Serialize(CArchive& ar)
{
	CGObject::Serialize(ar);
	mViewPort.Serialize(ar);
	if (ar.IsStoring())
	{
		ar << mClienRect.minCorner().x() << mClienRect.minCorner().y() << mClienRect.maxCorner().x() <<
			mClienRect.maxCorner().y();
	}
	else
	{
		ar >> mClienRect.minCorner().x() >> mClienRect.minCorner().y() >> mClienRect.maxCorner().x() >>
			mClienRect.maxCorner().y();
	}
}
void CGCamera::setViewPortBox(int xl, int yb, int xr, int yt)
{
	mViewPort.set(xl, yb, xr, yt);
}
void CGCamera::setViewPort(const CGViewPort& vp)
{
	//Ҫ��֤xl<xr, yb<yt
	mViewPort.set(vp.box().minCorner().x(), vp.box().minCorner().y(), vp.box().maxCorner().x(),
		vp.box().maxCorner().y());
	//�Ƿ�Ҫ������۲촰�ڵĵȱ�����
}
void CGCamera::setClientRect(int xl, int yb, int xr, int yt)
{
	//Ҫ��֤xl<xr, yb<yt
	if (xl < xr)
	{
		mClienRect.minCorner().x() = xl;
		mClienRect.maxCorner().x() = xr;
	}
	else
	{
		mClienRect.minCorner().x() = xr;
		mClienRect.maxCorner().x() = xl;
	}
	if (yb < yt)
	{
		mClienRect.minCorner().y() = yb;
		mClienRect.maxCorner().y() = yt;
	}
	else
	{
		mClienRect.minCorner().y() = yt;
		mClienRect.maxCorner().y() = yb;
	}
}
void CGCamera::setClientRect(const ABox2i& rc)
{
	mClienRect = rc;
}
//��������ϵת�����ӿڣ���ά��
Vec2i CGCamera::WorldtoViewPort(const Vec2d& p)
{
	//��������ʵ��
	return Vec2i(0, 0);
}
//�ӿ�ת������������ϵ����ά��
Vec2d CGCamera::ViewPorttoWorld(const Vec2i& p)
{
	//��������ʵ��
	return Vec2d(0, 0);
}
//�۲촰�ڿ�����ӿڿ�ȵı���
double CGCamera::WidthFactorWindowtoViewPort()
{
	return (mRight - mLeft) / mViewPort.width();
}
//�۲촰�ڸ߶����ӿڸ߶ȵı���
double CGCamera::HeightFactorWindowtoViewPort()
{
	return (mTop - mBottom) / mViewPort.height();
}

//�������λ�ã���ά����ά��
void CGCamera::setEye(double eyex, double eyey, double eyez)
{
	mEyeX = eyex;
	mEyeY = eyey;
	mEyeZ = eyez;
}
//����������Ϸ��򣨶�ά����ά��
void CGCamera::setUp(double upx, double upy, double upz)
{
	mUpX = upx;
	mUpY = upy;
	mUpZ = upz;
}

//�ͻ�������ά����ά��
void CGCamera::setClientRect(int cx, int cy)
{
	if (cx < 1 || cy < 1)
		return;
	mClienRect.minCorner().x() = 0;
	mClienRect.minCorner().y() = 0;
	mClienRect.maxCorner().x() = cx;
	mClienRect.maxCorner().y() = cy;
	ClientResized(cx, cy); //�����ӿ���Ӧ�仯
}
//�ͻ�����С�����任ʱ�������۲촰�����ӿڣ���ʹ�߿����ͬ������������
void CGCamera::ClientResized(int cx, int cy)
{
	//����ӿ���ͻ���һ����
	setViewPortBox(0, 0, cx, cy);
	//�ӿڴ�С�仯��Ҫ���´��ڱ��ֱ���һ�£�
	Zoom(Vec2d(Left(), Bottom()), Vec2d(Right(), Top()));
}
//������ƣ��۲���ƣ�
void CGCamera::Move(double tx, double ty) //�ƶ��۲�����ϵ����ά��
{
	//��������ʵ��
}
void CGCamera::Zoom(double ratio) //�۲촰������
{
	//��������ʵ��
}
void CGCamera::Zoom(const Vec2d& lb, const Vec2d& rt) //�۲촰������
{
	//��������ʵ��
}
void CGCamera::Rotate(double degree) //��ת�۲�����ϵ��������ϵԭ�㣩
{
	//��������ʵ��
}
void CGCamera::Reset() //���õ�Ĭ�ϲ���
{
	//��������ʵ��
}
//��άͼ�ι۲�任����������ϵ���۲�����ϵ������ά��
Vec2d CGCamera::WCStoVCS(const Vec2d& p)
{
	//��������ʵ��
	return Vec2d(0, 0);
}
//��άͼ�δ��ӱ任���۲�����ϵ���淶���豸����ϵ������ά����ʵ����ʹ�������豸����ϵ����淶���豸����ϵ��
Vec2d CGCamera::VCStoNCS(const Vec2d& p)
{
	//��������ʵ��
	return Vec2d(0, 0);
}
//��άͼ���ӿڱ任���淶���豸����ϵ���豸����ϵ������ά����ʵ����ʹ�������豸����ϵ����淶���豸����ϵ��
Vec2i CGCamera::NCStoDCS(const Vec2d& p)
{
	//��������ʵ��
	return Vec2i(0, 0);
}
//�豸����ϵ���淶���豸����ϵ����ά����ʵ����ʹ�������豸����ϵ����淶���豸����ϵ��
Vec2d CGCamera::DCStoNCS(const Vec2i& p)
{
	//��������ʵ��
	return Vec2d(0, 0);
}
//�淶���豸����ϵ���۲�����ϵ����ά����ʵ����ʹ�������豸����ϵ����淶���豸����ϵ��
Vec2d CGCamera::NCStoVCS(const Vec2d& p)
{
	//��������ʵ��
	return Vec2d(0, 0);
}
//�۲�����ϵ����������ϵ
Vec2d CGCamera::VCStoWCS(const Vec2d& p)
{
	//��������ʵ��
	return Vec2d(0, 0);
}
CG_NAMESPACE_EXIT
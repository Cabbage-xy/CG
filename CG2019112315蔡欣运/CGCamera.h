#ifndef _CGCAMERA_H_INCLUDED
#define _CGCAMERA_H_INCLUDED
#include "AABBox2.h"
#include "CGViewPort.h"
#include "Vector2.h"
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
	//�۲촰�ڼ��۲���
	double Left() const { return mLeft; }
	double Bottom() const { return mBottom; }
	double Right() const { return mRight; }
	double Top() const { return mTop; }

	//�۲�����ϵ
	double EyeX() const { return mEyeX; }
	double EyeY() const { return mEyeY; }
	double EyeZ() const { return mEyeZ; }
	double UpX() const { return mUpX; }
	double UpY() const { return mUpY; }
	double UpZ() const { return mUpZ; }

	//�����豸����ϵ���ӿڲ�������ʵ���ӿ�����һֱ�����±߽���������ͻ������ӿ�
	int NCSViewPortLeft() const { return mViewPort.left(); }
	int NCSViewPortBottom() const { return mViewPort.bottom(); }
	int NCSViewPortRight() const { return mViewPort.right(); }
	int NCSViewPortTop() const { return mViewPort.top(); }

	//�۲촰�ڸ߶����ӿڸ߶ȵı���
	double WidthFactorWindowtoViewPort();
	//�۲촰�ڸ߶����ӿڸ߶ȵı���
	double HeightFactorWindowtoViewPort();

	//�������λ�ã���ά����ά��
	void setEye(double eyex, double eyey, double eyez = 0);
	//����������Ϸ��򣨶�ά����ά��
	void setUp(double upx, double upy, double upz = 0);

	//�ͻ�������ά����ά��
	virtual void setClientRect(int cx, int cy);
	//�ͻ�����С�����任ʱ�������۲촰�����ӿڣ���ʹ�߿����ͬ������������
	void ClientResized(int cx, int cy);

	virtual void Move(double tx, double ty); //�ƶ��۲�����ϵ����ά��
	virtual void Zoom(double ratio); //�۲촰�����ţ���ά������������ͬ�������ţ�����Ӧ����0��
	virtual void Zoom(const Vec2d& lb, const Vec2d& rt); //�۲촰�����ţ���ά����ָ�����ڲ�������Ҫ��֤������ͬ�������ţ�
	virtual void Rotate(double degree); //��ת�۲�����ϵ��������ϵԭ�㣬��ʱ�뷽��Ϊ������λ���ȣ�����ά��
	virtual void Reset(); //���õ�Ĭ�ϲ�������ά��
public:
	//ֱ�߶βü��㷨��ʹ�ý��������ü����ڶ�ѡ�е��߶ν��вü���
	//Cohen-Sutherland�����룩ֱ�߶βü�
	//xl��yb��xr��yt��Ӧ�ü����ڵ����¡��ҡ��ϡ�s��e�����߶�����յ㣬rs��re�ü�������ޣ��򷵻�false�����򷵻�true
	virtual bool CohenSutherlandLineClip(double xl, double yb, double xr, double yt, const Vec2d& s, const Vec2d& e, Vec2d& rs, Vec2d& re);
	//�����ü��㷨��ѡ����
	//�е�ָ�ֱ�߶βü��㷨
	//bool MidpointSplitLineClip(double xl, double yb, double xr, double yt, const Vec2d& s, const Vec2d& e, Vec2d& rs, Vec2d& re);
	//��-Barskyֱ�߶βü��㷨
	//bool LiangBarskyLineClip(double xl, double yb, double xr, double yt, const Vec2d& s, const Vec2d& e, Vec2d& rs, Vec2d& re);
	//����βü��㷨��ʹ�ý��������ü����ڶ�ѡ�еĶ���ν��вü���
	//Sutherland-Hodgman(���)����βü��㷨��������βü����ڡ����ü�����Σ����һ����������
	//bool SutherlandHodgmanPolygonClip(double xl, double yb, double xr, double yt, const Vec2dArray& in, Vec2dArray& out);
	//Werler-Atherton(˫��)����βü��㷨������ü����ڶ���Ρ����ü�����Σ�������������������
	//bool WerlerAthertonPolygonClip(const Vec2dArray& win, const Vec2dArray& in, std::vector<Vec2dArray>& out);
protected:
	//�任֧�ֺ���
	//��άͼ�ι۲�任����������ϵ���۲�����ϵ������ά��
	virtual Vec2d WCStoVCS(const Vec2d& p);
	//��άͼ�δ��ӱ任���۲�����ϵ���淶���豸����ϵ������ά����ʵ����ʹ�������豸����ϵ����淶���豸����ϵ��
	virtual Vec2d VCStoNCS(const Vec2d& p);
	//��άͼ���ӿڱ任���淶����ϵ���豸����ϵ������ά����ʵ����ʹ�������豸����ϵ����淶���豸����ϵ��
	virtual Vec2i NCStoDCS(const Vec2d& p);
	//�豸����ϵ���淶���豸����ϵ����ά����ʵ����ʹ�������豸����ϵ����淶���豸����ϵ��
	virtual Vec2d DCStoNCS(const Vec2i& p);
	//�淶���豸����ϵ���۲�����ϵ����ά����ʵ����ʹ�������豸����ϵ����淶���豸����ϵ��
	virtual Vec2d NCStoVCS(const Vec2d& p);
	//�۲�����ϵ����������ϵ����ά��
	virtual Vec2d VCStoWCS(const Vec2d& p);
protected:
	CGViewPort mViewPort; //��Ӧ�ӿڣ����豸����ϵ���ͻ������ж���
	ABox2i mClienRect; //��ͼ�ͻ�������
	double mLeft, mBottom, mRight, mTop; //�۲촰�ڣ��ڹ۲�����ϵ�ж��壩���ε����¡��ҡ��ϣ�Ĭ��0,0,1,1��
	double mEyeX, mEyeY, mEyeZ; //���λ�ã�Ĭ��0,0,0������ά���õ���x��y����ʾ�۲�����ϵԭ������������ϵ�е�λ�ã�mEyeZ������ά����ά��Ĭ��Ϊ0
	double mUpX, mUpY, mUpZ; //���Ϸ���Ĭ��0,1,0������ά���õ�x��y����ʾ�۲�����ϵY��ķ���ʸ����mUpZ������ά����ά��Ĭ��Ϊ0
};
CG_NAMESPACE_EXIT
#endif //_CGCAMERA_H_INCLUDED
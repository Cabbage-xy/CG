#include "pch.h"
#include "CGView.h"
#include "CGRenderContext.h"
#include "UIEventListener.h"
#include "CGRenderable.h"
CG_NAMESPACE_ENTER
IMPLEMENT_DYNCREATE(CGView, CView)
CGView::CGView()
{
	mRenderContext = nullptr; // �������г�ʼ�� new CGRenderContext(this);
	mCommand = nullptr;
}
CGView::~CGView()
{
	if (mRenderContext != nullptr)
	{
		delete mRenderContext;
		mRenderContext = nullptr;
	}
	if (mCommand != nullptr)
	{
		mCommand->Cancel();
		delete mCommand;
		mCommand = nullptr;
	}
}
void CGView::OnDraw(CDC* pDC)
{
	//��������ʵ��
}
CGRenderContext* CGView::GetRenderContext()
{
	return mRenderContext;
}
bool CGView::RenderScene()
{
	//��������ʵ��
	return false;
}
//ͼ�ζ�����ӵ�����
bool CGView::addRenderable(CGRenderable * r)
{
	//��������ʵ��
	return false;
}
bool CGView::delReaderable(CGRenderable* r)
{
	//��������ʵ��
	return false;
}
//��������
COLORREF CGView::PenColor() const
{
	//��������ʵ��
	return RGB(0, 0, 0);
}
int CGView::PenWidth() const
{
	//��������ʵ��
	return 1;
}
int CGView::PenStyle() const
{
	//��������ʵ��
	return PS_SOLID;
}
//��ˢ����
bool CGView::UseBrush() const
{
	//��������ʵ��
	return false;
}
COLORREF CGView::BrushColor() const
{
	//��������ʵ��
	return RGB(255, 255, 255);
}
int CGView::BrushIndex() const
{
	//��������ʵ��
	return 0;
}
//�����㷨
int CGView::LineAlgorithm() const
{
	//��������ʵ��
	return 0;
}
//Բ���㷨
int CGView::CircleAlgorithm() const
{
	//��������ʵ��
	return 0;
}
//����㷨
int CGView::FillAlgorithm() const
{
	//��������ʵ��
	return 0;
}
int CGView::SeedAlgorithm() const
{
	//��������ʵ��
	return 0;
}
//��������ı߽���ɫ
COLORREF CGView::BoundColor() const
{
	//��������ʵ��
	return RGB(0, 0, 0);
}
//����������ڵ���ɫ
COLORREF CGView::FloodColor() const
{
	//��������ʵ��
	return RGB(255, 255, 255);
}
void CGView::Prompt(const CString& str)
{
	//��������ʵ��
	UNUSED(str);
}
//�����ӿ������ȡ��Ӧ�������꣨��ά��
Vec2d CGView::ViewPortToWorld(const Vec2i& p)
{
	//��������ʵ��
	return Vec2d();
}
Vec2i CGView::WorldToViewPort(const Vec2d& p)
{
	//��������ʵ��
	return Vec2i();
}
//ͼ�ζ����ʰȡ����άͼ�Σ�
void CGView::UpdatePicked(const Vec2d& p, double radius) //����ѡ��
{
	//��������ʵ��
}
void CGView::AppendPicked(const Vec2d& p, double radius) //���ѡ��
{
	//��������ʵ��
}
//��άͼ�ζ���ļ��α任�����ѡ���еĶ���
void CGView::Translate(double tx, double ty) //ƽ��
{
	//��������ʵ��
}
void CGView::Rotate(double angle, double cx, double cy) //��ת����ʱ��Ϊ�����ȣ�
{
	//��������ʵ��
}
void CGView::Scale(double sx, double sy) //����
{
	//��������ʵ��
}
void CGView::Scale(double sx, double sy, double cx, double cy) //���ţ�����ָ���ο������ţ�
{
	//��������ʵ��
}
void CGView::Scale(double sx, double sy, double cx, double cy, const Vec2d& xDir) //���ţ�ָ���ο��㣬���ŷ���
{
	//��������ʵ��
}
void CGView::ShearXYAxis(double shx, double shy) //��X��Y�����
{
	//��������ʵ��
}
CG_NAMESPACE_EXIT
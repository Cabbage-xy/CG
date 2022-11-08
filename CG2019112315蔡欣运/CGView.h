#ifndef _CGVIEW_H_INCLUDED
#define _CGVIEW_H_INCLUDED
#include <afxwin.h>
#include "Vector2.h"
CG_NAMESPACE_ENTER
class CGRenderContext;//������������ֻ��Ҫ����ָ�룬������Ԥ������
class UIEventListener;//����ģʽ�¼�����꽻�����õ��Ļ���
class CGRenderable; //ͼ�ζ��󣨼��Ρ��任�����ԣ�����
class CGView : public CView
{
	DECLARE_DYNCREATE(CGView)
protected: // �������л������������ǳ�����
	CGView();
	// ����
public:
	CGRenderContext* GetRenderContext(); //��ȡ�������Ⱦ����
	//��Ҫ������������д�ĺ���
	virtual bool RenderScene();
	//ͼ�ζ�����ӵ����������ڽ�����������
	virtual bool addRenderable(CGRenderable* r);
	virtual bool delReaderable(CGRenderable* r);
	//��������
	virtual COLORREF PenColor() const;
	virtual int PenWidth() const;
	virtual int PenStyle() const;
	//��ˢ����
	virtual bool UseBrush() const;
	virtual COLORREF BrushColor() const;
	virtual int BrushIndex() const;
	//�����㷨
	virtual int LineAlgorithm() const;
	//Բ���㷨
	virtual int CircleAlgorithm() const;
	//����㷨
	virtual int FillAlgorithm() const;
	virtual int SeedAlgorithm() const;
	//��������ı߽���ɫ
	virtual COLORREF BoundColor() const;
	//����������ڵ���ɫ
	virtual COLORREF FloodColor() const;
	//��ʾ��ʾ��Ϣ
	virtual void Prompt(const CString& str);
	//�����ӿ������ȡ��Ӧ�������꣨��ά��
	virtual Vec2d ViewPortToWorld(const Vec2i& p);
	virtual Vec2i WorldToViewPort(const Vec2d& p);
	//ͼ�ζ����ʰȡ����άͼ�Σ�
	virtual void UpdatePicked(const Vec2d& p, double radius); //����ѡ��
	virtual void AppendPicked(const Vec2d& p, double radius); //���ѡ��
	//��άͼ�ζ���ļ��α任�����ѡ���еĶ���
	virtual void Translate(double tx, double ty); //ƽ��
	virtual void Rotate(double angle, double cx, double cy); //��ת����ʱ��Ϊ�����ȣ�
	virtual void Scale(double sx, double sy); //����
	virtual void Scale(double sx, double sy, double cx, double cy); //���ţ�����ָ���ο������ţ�
	virtual void Scale(double sx, double sy, double cx, double cy, const Vec2d& xDir); //���ţ�ָ���ο��㣬���ŷ���
	virtual void ShearXYAxis(double shx, double shy); //��X��Y�����
	// ʵ��
public:
	virtual ~CGView();
	// ��д
public:
	virtual void OnDraw(CDC* pDC); // �������Ǵ��麯��������������������д�Ի��Ƹ���ͼ
protected:
	CGRenderContext * mRenderContext; //��Ⱦ����
	UIEventListener* mCommand; //��������
};
CG_NAMESPACE_EXIT
#endif //_CGVIEW_H_INCLUDED
#ifndef _CGSCENE_H_INCLUDED
#define _CGSCENE_H_INCLUDED
#include "Vector2.h"
#include "AABBox2.h"
#include "CGObject.h"
#include "Matrix33.h"
CG_NAMESPACE_ENTER
class CGRenderable;
class CGCamera;
class CGRenderContext;
class CGScene : public CGObject
{
	DECLARE_SERIAL(CGScene)
public:
	CGScene();
	virtual ~CGScene();
	virtual void Serialize(CArchive& ar);
	//ͼ�ζ���
	bool addRenderable(CGRenderable*);
	CGRenderable* detachRenderable(CGRenderable*);
	bool delRenderable(CGRenderable*);
	void removeAllRenderable();
	CGRenderable* getRenderable(unsigned int index);
	//��Ⱦ����
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera); //Ӧ����������д
	//ͼ�ζ���ѡȡ������������
	CGRenderable* RenderableSelected(const CString& name);
	bool RenderableUnselect(const CString& name);
	bool RenderableUnselect(CGRenderable* r);
	bool RenderableUnselectAll();
	bool RenderableSelectAll();
	//ͼ�ζ����ʰȡ����άͼ�Σ�
	virtual CGRenderable* UpdatePicked(const Vec2d& p, double radius); //����ѡ�����ʰȡ����ɹ������滻ѡ�񼯣�
	virtual CGRenderable* AppendPicked(const Vec2d& p, double radius); //���ѡ�����ʰȡ����ɹ��������ѡ�񼯣�
public:
	//��άͼ�ζ���ļ��α任
	virtual bool Translate(double tx, double ty); //ƽ��
	virtual bool Rotate(double angle, double cx, double cy); //��ת����ʱ��Ϊ�����ȣ�
	virtual bool Scale(double sx, double sy); //���ţ���������ԭ�����ţ�
	virtual bool Scale(double sx, double sy, double cx, double cy); //���ţ�����ָ���ο������ţ�
	virtual bool Scale(double sx, double sy, double cx, double cy, const Vec2d& xDir); //���ţ�ָ���ο��㣬���ŷ���
	virtual bool MirrorXAxis(); //����X��Գƣ���ά����ά��
	virtual bool MirrorYAxis(); //����Y��Գƣ���ά����ά��
	virtual bool MirrorYeqPosX(); //����y=x�Գƣ���ά����ά��
	virtual bool MirrorYeNegPX(); //����y=-x�Գƣ���ά����ά��
	virtual bool MirrorOrigin(); //����ԭ��Գƣ���ά����ά��
	virtual bool ShearXAxis(double shx); //��X�����
	virtual bool ShearYAxis(double shy); //��Y�����
	virtual bool ShearXYAxis(double shx, double shy); //��X��Y�����
	virtual bool Transform(const Mat3d& mat); //���α任����˸�������
protected:
	CTypedPtrArray<CObArray, CGRenderable*> mRenderables;//ͼ�ζ����б�
	//ͼ�ζ���ѡ��
	CTypedPtrArray<CObArray, CGRenderable*> mSelections;
};
CG_NAMESPACE_EXIT
#endif //_CGSCENE_H_INCLUDED
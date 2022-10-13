#ifndef _CGSCENE_H_INCLUDED
#define _CGSCENE_H_INCLUDED
#include "Vector2.h"
#include "AABBox2.h"
#include "CGObject.h"
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
protected:
	CTypedPtrArray<CObArray, CGRenderable*> mRenderables;//ͼ�ζ����б�
	//ͼ�ζ���ѡ��
	CTypedPtrArray<CObArray, CGRenderable*> mSelections;
};
CG_NAMESPACE_EXIT
#endif //_CGSCENE_H_INCLUDED
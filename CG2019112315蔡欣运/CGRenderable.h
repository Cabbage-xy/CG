#ifndef _CGRENDERABLE_H_INCLUDED
#define _CGRENDERABLE_H_INCLUDED
#include "CGObject.h"
#include "Vector2.h"
CG_NAMESPACE_ENTER
class CGRenderContext;
class CGCamera;
class CGScene; //Ԥ�����ĳ�����
class CGRenderable : public CGObject
{
		DECLARE_SERIAL(CGRenderable)
public:
	CGRenderable();
	CGRenderable(const CString& name);
	virtual ~CGRenderable();
	//���л�
	virtual void Serialize(CArchive& ar);
	//������ӵ������������볡���Ĺ��������Ӷ���Ҳ������������
	void addToScene(CGScene* s);
	CGScene* scene() const;
public:
	virtual void Render(CGRenderContext* pRC, CGCamera* pCamera); //���ƶ���ʹ��ָ�����
	//����״̬���壨Ҳ����ö�����ͣ�
	static const int sNormal = 0; //����״̬
	static const int sSelected = 1; //ѡ��״̬
	int status() const { return mStatus; }
	void setStatus(int s) { mStatus = s; }
	//�����Χ���Ƿ���Ҫ���¼���
	bool boundsDirty() const { return mBoundsDirty; }
	void setBoundsDirty(bool dirty) { mBoundsDirty = dirty; }
	virtual void computeBoundingBox(); //�������İ�Χ��,����������д
	virtual bool Picked(const Vec2d& p, double radius); //����ά���Ƿ�ʰȡ��
protected:
	CGScene* mScene; //����ʵ�������ĳ�������������볡��ʱ�Զ��������á�
	int mStatus = 0; //״̬
	bool mBoundsDirty = true; //��Χ���Ƿ��Ѹı�
};
CG_NAMESPACE_EXIT
#endif //_CGRENDERABLE_H_INCLUDED
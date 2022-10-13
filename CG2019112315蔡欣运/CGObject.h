#ifndef _CGOBJECT_H_INCLUDED
#define _CGOBJECT_H_INCLUDED
#include "CGBase.h"
CG_NAMESPACE_ENTER
class CGObject : public CObject
{
	DECLARE_SERIAL(CGObject)
public:
	CGObject();
	CGObject(const CString& name);
	virtual ~CGObject();
	//���л���������Ӧ��д���麯����
	virtual void Serialize(CArchive& ar);
	const CString& name() const { return mName; }
	CString& name() { return mName; }
protected:
	CString mName; //�������ƣ�Ĭ���ɡ�����+��š����ɣ�������ʾ
	static long sID; //����ID�������ڸ�����������������Ψһ��ʶ
};
CG_NAMESPACE_EXIT
#endif //_CGOBJECT_H_INCLUDED

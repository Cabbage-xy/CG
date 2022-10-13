#include "pch.h"
#include "CGObject.h"
CG_NAMESPACE_ENTER
IMPLEMENT_SERIAL(CGObject, CObject, 1) //1���Կ��������ݰ汾�ţ����ڼ����������������ݳ�Ա��
long CGObject::sID = 0L;
CGObject::CGObject()
{
	mName.Format(_T("CGObject%ld"), sID);
	sID++;
}
CGObject::CGObject(const CString& name)
	: mName(name)
{
	sID++;
}
CGObject::~CGObject()
{
}
void CGObject::Serialize(CArchive& ar)
{
	CObject::Serialize(ar); //�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ��
	if (ar.IsStoring()) //����
	{
		ar << mName;
	}
	else //��ȡ
	{
		ar >> mName;
	}
}
CG_NAMESPACE_EXIT
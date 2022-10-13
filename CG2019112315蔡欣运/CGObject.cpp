#include "pch.h"
#include "CGObject.h"
CG_NAMESPACE_ENTER
IMPLEMENT_SERIAL(CGObject, CObject, 1) //1可以看作是数据版本号，用于兼容升级（增加数据成员）
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
	CObject::Serialize(ar); //先调用基类的序列化函数，再序列化自己的成员（根据需要）
	if (ar.IsStoring()) //保存
	{
		ar << mName;
	}
	else //读取
	{
		ar >> mName;
	}
}
CG_NAMESPACE_EXIT
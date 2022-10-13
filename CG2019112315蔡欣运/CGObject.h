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
	//序列化（派生类应重写该虚函数）
	virtual void Serialize(CArchive& ar);
	const CString& name() const { return mName; }
	CString& name() { return mName; }
protected:
	CString mName; //对象名称，默认由“类名+序号”构成，用于显示
	static long sID; //对象ID，仅用于辅助对象命名，不能唯一标识
};
CG_NAMESPACE_EXIT
#endif //_CGOBJECT_H_INCLUDED

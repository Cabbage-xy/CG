#ifndef _CGBASE_H_INCLUDED
#define _CGBASE_H_INCLUDED

//名称空间
#define CG_NAMESPACE cg //根据需要自定义名称空间名称
#define CG_NAMESPACE_ENTER namespace CG_NAMESPACE { 
#define CG_NAMESPACE_EXIT }

CG_NAMESPACE_ENTER
typedef signed char Int8;
typedef short Int16;
typedef int Int32;
typedef long long Int64;
typedef unsigned char UInt8;
typedef unsigned short UInt16;
typedef unsigned int UInt32;
typedef unsigned long long UInt64;
typedef float Real32;
typedef double Real64;
const double dPi =
3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093845;
const double dDEG_TO_RAD = dPi / 180.0;
const double dRAD_TO_DEG = 180.0 / dPi;
const float fPi =
(float)3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093845;
const float fDEG_TO_RAD = float(dPi / 180.0);
const float fRAD_TO_DEG = float(180.0 / dPi);
// 弧度转度
class Radian
{
public:
	Radian(double val) : mValue(val) {}
	double value() { return mValue; }
	double degree() { return (double)(mValue * dRAD_TO_DEG); }
private:
	double mValue;
};
//度转弧度
class Degree
{
public:
	Degree(double val) : mValue(val) {}
	double value() { return mValue; }
	double radian() { return (double)(mValue * dDEG_TO_RAD); }
private:
	double mValue;
};
CG_NAMESPACE_EXIT

#endif //_CGBASE_H_INCLUDED
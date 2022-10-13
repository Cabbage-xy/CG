#ifndef _AABBOX2_H_INCLUDED
#define _AABBOX2_H_INCLUDED
#include "Vector2.h"
CG_NAMESPACE_ENTER
template <typename T> class AABBox2
{
public:
	AABBox2() { setNull(); };
	AABBox2(const AABBox2& other)
	{
		mMax = other.maxCorner();
		mMin = other.minCorner();
	};
	AABBox2(const Vector2<T>& center, T radius)
	{
		mMax = center + radius;
		mMin = center - radius;
	}
	AABBox2(const Vector2<T>& point)
	{
		mMax = point;
		mMin = point;
	}
	AABBox2(const Vector2<T>& pt1, const Vector2<T>& pt2, T displace = 0)
	{
		mMax = mMin = pt1;
		if (mMax.x() < pt2.x()) mMax.x() = pt2.x();
		if (mMax.y() < pt2.y()) mMax.y() = pt2.y();
		if (mMin.x() > pt2.x()) mMin.x() = pt2.x();
		if (mMin.y() > pt2.y()) mMin.y() = pt2.y();
		mMax = mMax + displace;
		mMin = mMin - displace;
	}
	void setInfinite()
	{
		mMin = std::numeric_limits<T>::lowest();
		mMax = std::numeric_limits<T>::max();
	}
	bool isInfinite() const
	{
		if (mMin.x() != std::numeric_limits<T>::lowest() || mMax.x() != std::numeric_limits<T>::max() ||
			mMin.y() != std::numeric_limits<T>::lowest() || mMax.y() != std::numeric_limits<T>::max())
			return false;
		return true;
	}
	void setNull() { mMin = 1; mMax = -1; }
	bool isNull() const { return mMin.x() > mMax.x() || mMin.y() > mMax.y(); }
	bool isPoint() const { return mMin == mMax; }
	void enlarge(T displace)
	{
		if (isNull())
			return;
		mMax = mMax + displace;
		mMin = mMin - displace;
	}
		bool isInside(const Vector2<T>&v) const
	{
		return v.x() >= minCorner().x() && v.x() <= maxCorner().x() &&
			v.y() >= minCorner().y() && v.y() <= maxCorner().y();
	}
	T width() const
	{
		if (isNull())
			return 0;
		else
			return mMax.x() - mMin.x();
	}
	T height() const
	{
		if (isNull())
			return 0;
		else
			return mMax.y() - mMin.y();
	}
	const Vector2<T>& minCorner() const { return mMin; }
	Vector2<T>& minCorner() { return mMin; }
	const Vector2<T>& maxCorner() const { return mMax; }
	Vector2<T>& maxCorner() { return mMax; }
	void setMinCorner(T x, T y) { mMin.x() = x; mMin.y() = y; }
	void setMinCorner(const Vector2<T>& v) { mMin = v; }
	void setMaxCorner(T x, T y) { mMax.x() = x; mMax.y() = y; }
	void setMaxCorner(const Vector2<T>& v) { mMax = v; }
	//��������㣨���뾶��Χ����չ��Χ�У�radius > 0��
	AABBox2& addPoint(const Vector2<T>& v, T radius)
	{
		if (isNull())
		{
			mMax = v;
			mMin = v;
		}
		if (mMax.x() < v.x() + radius) mMax.x() = v.x() + radius;
		if (mMax.y() < v.y() + radius) mMax.y() = v.y() + radius;
		if (mMin.x() > v.x() - radius) mMin.x() = v.x() - radius;
		if (mMin.y() > v.y() - radius) mMin.y() = v.y() - radius;
		return *this;
	}
	//�����������չ��Χ��
	AABBox2& addPoint(const Vector2<T>& p)
	{
		if (isNull())
		{
			mMax = p;
			mMin = p;
			return *this;
		}
		if (mMax.x() < p.x()) mMax.x() = p.x();
		if (mMax.y() < p.y()) mMax.y() = p.y();
		if (mMin.x() > p.x()) mMin.x() = p.x();
		if (mMin.y() > p.y()) mMin.y() = p.y();
		return *this;
	}
	//��չ�������Ҫ������Χ���԰���������Χ��
	AABBox2& operator+=(const AABBox2& other)
	{
		*this = *this + other;
		return *this;
	}
	//��չ�������Ҫ������Χ���԰���������Χ��
	AABBox2& extend(const AABBox2& other)
	{
		*this = *this + other;
		return *this;
	}
	//��չ����Χ�У������Ҫ���԰���������
	AABBox2& operator+=(const Vector2<T>& p)
	{
		addPoint(p);
		return *this;
	}
	//��������������Χ�е��°�Χ��
	AABBox2 operator+(const AABBox2& box) const
	{
		if (isNull())
			return box;
		if (box.isNull())
			return *this;
		AABBox2 tmp = box;
		tmp.addPoint(mMin);
		tmp.addPoint(mMax);
		return tmp;
	}
	//���ذ�������Χ�к͸�������°�Χ��
	AABBox2 operator+(const Vector2<T>& p)
	{
		AABBox2 AABBox2 = *this;
		AABBox2 += p;
		return AABBox2;
	}
	//���ذ�������Χ�к͸�������°�Χ��
	AABBox2 extend(const Vector2<T>& p)
	{
		AABBox2 AABBox2 = *this;
		AABBox2 += p;
		return AABBox2;
	}
	//�ж�����һ����Χ���Ƿ��ཻ
	bool intersects(const AABBox2& bb) const
	{
		if (isNull() || bb.isNull())
			return false;
			if (mMax.x() < bb.mMin.x())
				return false;
		if (mMin.x() > bb.mMax.x())
			return false;
		if (mMax.y() < bb.mMin.y())
			return false;
		if (mMin.y() > bb.mMax.y())
			return false;
		return true;
	}
	//�ж�����Χ���Ƿ����
	bool operator==(const AABBox2& box) const
	{
		return mMin == box.mMin && mMax == box.mMax;
	}
	//�ж�����Χ���Ƿ񲻵�
	bool operator!=(const AABBox2& box) const
	{
		return !operator==(box);
	}
	//���ر���Χ�е�����
	Vector2<T> center() const
	{
		Vector2<T> c = (minCorner() + maxCorner()) / 2.0f;
		return c;
	}
protected:
	Vector2<T> mMin;
	Vector2<T> mMax;
};
typedef AABBox2<int> ABox2i;
typedef AABBox2<float> ABox2f;
typedef AABBox2<double> ABox2d;
CG_NAMESPACE_EXIT
#endif //_AABBOX2_H_INCLUDED
#include "Vec2D.h"

template <typename T>
Vec2D<T> Vec2D<T>::operator+(Vec2D<T> l)
{
	Vec2D<T> ret;
	ret.x = x + l.x;
	ret.y = y + l.y;
	return ret;
}

template<> Vec2D<int> Vec2D<int>::operator+(Vec2D<int> l)
{
	Vec2D<int> ret(0,0);
	ret.x = x + l.x;
	ret.y = y + l.y;
	return ret;
}

template<> Vec2D<float> Vec2D<float>::operator+(Vec2D<float> l)
{
	Vec2D<float> ret(0,0);
	ret.x = x + l.x;
	ret.y = y + l.y;
	return ret;
}

template <typename T>
Vec2D<T> Vec2D<T>::operator-(Vec2D<T> l)
{
	Vec2D<T> ret;
	ret.x = x - l.x;
	ret.y = y - l.y;
	return ret;
}

template <typename T>
Vec2D<T> Vec2D<T>::operator-(T l)
{
	Vec2D<T> ret;
	ret.x = x - l;
	ret.y = y - l;
	return ret;
}

template<> Vec2D<int> Vec2D<int>::operator-(int l)
{
	Vec2D<int> ret(0,0);
	ret.x = x - l;
	ret.y = y - l;
	return ret;
}

template<> Vec2D<float> Vec2D<float>::operator-(float l)
{
	Vec2D<float> ret(0.0,0.0);
	ret.x = x - l;
	ret.y = y - l;
	return ret;
}

template <typename T>
T Vec2D<T>::operator*(Vec2D<T> l)
{
	return (x * l.x) + (y * l.y);
}

template<> int Vec2D<int>::operator*(Vec2D<int> l)
{
	return (x * l.x) + (y * l.y);
}

template<> float Vec2D<float>::operator*(Vec2D<float> l)
{
	return (x * l.x) + (y * l.y);
}

template <typename T>
Vec2D<T> Vec2D<T>::operator*(T l)
{
	Vec2D<T> ret;
	ret.x = x * l;
	ret.y = y * l;
	return ret;
}

template<> Vec2D<int> Vec2D<int>::operator*(int l)
{
	Vec2D<int> ret(0,0);
	ret.x = x * l;
	ret.y = y * l;
	return ret;
}

template<> Vec2D<float> Vec2D<float>::operator*(float l)
{
	Vec2D<float> ret(0.0,0.0);
	ret.x = x * l;
	ret.y = y * l;
	return ret;
}


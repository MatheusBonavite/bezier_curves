#include "Vec2D.h"

template <typename T>
Vec2D<T> Vec2D<T>::operator+(Vec2D<T> l)
{
	Vec2D<T> ret;
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
T Vec2D<T>::operator*(Vec2D<T> l)
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

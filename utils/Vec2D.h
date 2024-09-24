template <typename T>
class Vec2D
{
public:
	Vec2D(T x, T y) : x(x), y(y) {};
	Vec2D<T> operator+(Vec2D<T> l);
	Vec2D<T> operator-(Vec2D<T> l);
	Vec2D<T> operator-(T l);
	T operator*(Vec2D<T> l);
	Vec2D<T> operator*(T l);
	T x;
	T y;
};

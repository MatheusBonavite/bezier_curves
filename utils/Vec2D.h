template <typename T>
class Vec2D
{
public:
	Vec2D(T x, T y) : x(x), y(x) {};
	Vec2D<T> operator+(Vec2D<T> l);
	T operator*(Vec2D<T> l);

private:
	T x;
	T y;
};

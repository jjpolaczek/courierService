#ifndef POINT_H
#define POINT_H


class Point
{
public:
    Point(int ux, int uy) :
        x(ux),
        y(uy)
    {}
    Point() :
        x(0),
        y(0)
    {}
    Point &operator+=(const Point &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    Point &operator-=(const Point &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    bool operator ==(const Point &other)
    {
        if (other.x == x && other.y == y)
            return true;
        return false;
    }
    int x;
    int y;
};
inline Point operator-(Point lhs, const Point &rhs)
{
    lhs -= rhs;
    return lhs;
}
inline Point operator+(Point lhs, const Point &rhs)
{
    lhs += rhs;
    return lhs;
}


#endif // POINT_H

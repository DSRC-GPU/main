
#include "Point.hpp"

#include <cstdlib>

Point::Point(): _x(0), _y(0)
{

}

Point::Point(float nx, float ny)
{
  _x = nx;
  _y = ny;
}

float Point::x() const
{
  return _x;
}

float Point::x(float nx)
{
  _x = nx;
  return _x;
}

float Point::y() const
{
  return _y;
}

float Point::y(float ny)
{
  _y = ny;
  return _y;
}

bool Point::closeTo(Point& other, int max) const
{
  return abs(_x - other.x()) + abs(_y - other.y()) <= max;
}

bool Point::operator==(const Point& p)
{
  return _x == p.x() && _y == p.y();
}

bool Point::operator!=(const Point& p)
{
  return !(*this == p);
}


#ifndef __CIRCLE_H__
#define __CIRCLE_H__
#include "point.h"

class Circle
{
 private:
  Point center;
  const double radius;

 public:
  Circle();
  Circle(Point & point_input, double length);
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};

#endif

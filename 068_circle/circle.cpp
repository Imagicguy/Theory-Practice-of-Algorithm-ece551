#include "circle.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
Circle::Circle(Point & point_input, double length) : center(point_input), radius(length) {}

Circle::Circle() : radius(0) {}

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  if (this == &otherCircle)
    return pow(radius, 2) * atan(1) * 4;
  double r1 = radius;
  double r2 = otherCircle.radius;
  double d = center.distanceFrom(otherCircle.center);
  //if (d >= r1 + r2) {
  //  return 0;  //not intersection
  //}
  if (d < abs(r1 - r2)) {
    return atan(1) * 4 * std::min(pow(r1, 2), pow(r2, 2));
  }  //one circle is included by another

  double x = acos((d * d + r2 * r2 - r1 * r1) / (2 * d * r2));
  double y = acos((d * d + r1 * r1 - r2 * r2) / (2 * d * r1));
  //double angleA = 2 * asin(y / r1);
  //double angleB = 2 * asin(y / r2);
  double arcA = pow(r2, 2) * x;
  double arcB = pow(r1, 2) * y;
  double tri = 0.5 * pow((-d + r2 + r1) * (d + r2 - r1) * (d - r2 + r1) * (d + r2 + r1), 0.5);
  return arcA + arcB - tri;
}

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <map>
#include <set>
#include <limits>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// struct of point, (x, y)
struct Point
{
  double x, y;

  Point(): x(0),y(0) {}

  Point(double k, double s) : x(k), y(s) {}

  void operator = (const Point& str) {
        x=str.x;
        y=str.y;
  }

};


//std::sort(vec.begin(), vec.end(), less_than_x());
struct less_than_x
{
    inline bool operator() (const Point& struct1, const Point& struct2)
    {
      //kp++;
        return (struct1.x < struct2.x);
    }
};
//std::sort(vec.begin(), vec.end(), less_than_y());
struct less_than_y
{
    inline bool operator() (const Point& struct1, const Point& struct2)
    {
      //kp++;
        return (struct1.y < struct2.y);
    }
};

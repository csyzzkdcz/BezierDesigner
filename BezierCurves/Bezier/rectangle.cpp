#include"rectangle.h"
#include<cmath>
using namespace std;
void Rectangle::Generate(double x1,double y1, double x2,double y2)
{
	double min_x = x1<x2 ? x1:x2;
	double max_x = x1>x2 ? x1:x2;
	double min_y = y1<y2 ? y1:y2;
	double max_y = y1>y2 ? y1:y2;
	left_down.setX(min_x);
	left_down.setY(min_y);
	right_down.setX(max_x);
	right_down.setY(min_y);
	left_top.setX(min_x);
	left_top.setY(max_y);
	right_top.setX(max_x);
	right_top.setY(max_y);
}

void Rectangle::Generate(QPointF p1, QPointF p2)
{
	Generate(p1.rx(),p1.ry(),p2.rx(),p2.ry());
}
bool Rectangle::intersection(Rectangle* R)
{
	double min_x1 = left_down.rx() < right_top.rx() ? left_down.rx() : right_top.rx();
	double min_y1 = left_down.ry() < right_top.ry() ? left_down.ry() : right_top.ry();
	double max_x1 = left_down.rx() > right_top.rx() ? left_down.rx() : right_top.rx();
	double max_y1 = left_down.ry() > right_top.ry() ? left_down.ry() : right_top.ry();

	double min_x2 = R->left_down.rx() < R->right_top.rx() ? R->left_down.rx() : R->right_top.rx();
	double min_y2 = R->left_down.ry() < R->right_top.ry() ? R->left_down.ry() : R->right_top.ry();
	double max_x2 = R->left_down.rx() > R->right_top.rx() ? R->left_down.rx() : R->right_top.rx();
	double max_y2 = R->left_down.ry() > R->right_top.ry() ? R->left_down.ry() : R->right_top.ry();

	double min_x = min_x1 > min_x2 ? min_x1 : min_x2;
	double min_y = min_y1 > min_y2 ? min_y1 : min_y2;
	double max_x = max_x1 < max_x2 ? max_x1 : max_x2;
	double max_y = max_y1 < max_y2 ? max_y1 : max_y2;

	if(min_x > max_x || min_y >max_y)
		return false;
	else
		return true;
}
bool Rectangle::is_in(QPointF P)
{
	double min_x = left_down.rx();
	double min_y = left_down.ry();
	double max_x = right_top.rx();
	double max_y = right_top.ry();
	return (min_x - P.rx()) * (max_x - P.rx()) <= 0 && (min_y - P.ry()) * (max_y - P.ry()) <=0;
}
 double Rectangle::diam()
 {
	 return sqrt( pow(left_down.rx()-right_top.rx(),2.0) + pow(left_down.ry() - right_top.ry(),2.0));
 }
 QPointF Rectangle::Center()
 {
	 QPointF p = 0.5 * (left_down + right_top);
	 return p;
 }
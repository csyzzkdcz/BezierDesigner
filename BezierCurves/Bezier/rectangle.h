#include<iostream>
#include<qpainter.h>
class Rectangle
{
public:
	Rectangle(void){};
	~Rectangle(void){};
public:
	QPointF left_down;
	QPointF left_top;
	QPointF right_down;
	QPointF right_top;
public:
	void Generate(QPointF p1, QPointF p2);
	void Generate(double x1,double y1, double x2, double y2);
	bool is_in(QPointF P);
	bool intersection(Rectangle* R); //charge whether two rectangle have intersection;
	double diam();
	QPointF Center();

};
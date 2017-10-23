#pragma once
#include <qpainter.h>
#include <vector>
#include<queue>
#include<cmath>
#include<qrect.h>
#include"rectangle.h"
using namespace std;
class Bezier
{
public:
	vector<QPointF> points;   //store the points for control polygon
	vector<QPointF> points_composite_;//store the points for composite control_polygon;
	vector<QPointF> points_curve;//store the points for bezier curve
	QPointF evaluation_point_;	//store the point got by evaluation algorithm
	int selected_index_;		//record the index of the selected point
	bool selected_curve_;		//record whether this curve is chosed to do operations
	bool selected_curve_right_;	//record whether this curve is chosed by the click of right button
	bool evaluation_;			//record whether this curve is chosed to do evaluation algorithm
	Rectangle* convex_rect; 
	QRectF BBox_;
public:	
	Bezier (void);
	Bezier (const QPoint &point);
	~Bezier (void) {};
	void DrawPoint( QPointF &point, QPainter &paint,int flag );
	void Draw_polygon(QPainter &painter);
	void Draw_curve(QPainter &painter);
	void AddPoint (QPoint &point );
	void AddPoint (QPointF &point);
	void InsertPoint (QPoint &point);
	void ChangeLastPoint(QPoint &point);					
	void Get_simple_Bezier();				//draw simple bezier curve
	void Get_composite_Bezier();			//draw composite bezier curve
	void Get_Interpolate_Curve();			//draw interpolated curve
	vector<QPointF> Four_points_op(vector<QPointF> op_points);
	bool Intersections(Bezier *curve, vector<QPointF> &points);
	void Selected_Point(QPoint &point);		//select point on the control polygon
	void DeletePoint(QPoint &point);
	void ChangeSelectedPoint(QPoint &point);
	void SaveCurveAsImage(QImage *image);
	double Distance(QPointF p1, QPointF p2, QPointF p3);
	void Get_convex_rect();
	void CalcBoundingBox();

public:
	void Subdivision(Bezier &left, Bezier &right,float t);		//do subdivision on Bezier one time
	void Subdivision(Bezier *Left, Bezier *right,float t);
	void Degree_Elevation();
	QPointF  Evaluation(float t);
	Bezier* Copy_Curve();
	void Selected_curve(QPoint &point, int flag);		//charge whether this curve is selected, flag=0 means that you click rightbutton and flag=1 means you click leftbutton
	void Move_curve(QPoint &point_start_, QPoint &point_end_);//move the curve corresponding to the vecter
	void End();					//change all of thing into initial situation
	vector<QPointF> intersection(Bezier* C);
	
};
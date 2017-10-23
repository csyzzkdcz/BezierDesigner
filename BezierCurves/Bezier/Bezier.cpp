#include "Bezier.h"
#include <iostream>
#include <Eigen>
#include <cmath>
using namespace Eigen;
using namespace std;
#define REFINE_TIME_ 5
#define POINT_SIZE 5
#define EPSILON 3
#define TOL 1e-3
#define INF 1000000
#define LINE_SIZE 2
Bezier::Bezier (void)  
{
	selected_index_=INT_MAX;
	selected_curve_=false;
	selected_curve_right_=false;
}
Bezier::Bezier (const QPoint &point) 
{
	points.push_back(point);
	selected_index_=INT_MAX;
	selected_curve_=false;
	selected_curve_right_=false;
	evaluation_=false;
}
void Bezier::End()
{
	selected_index_=INT_MAX;
	selected_curve_=false;
	evaluation_=false;
}
void Bezier::AddPoint(QPoint &point )    //添加节点
{
	QPointF new_point_;
	new_point_.setX(point.rx());
	new_point_.setY(point.ry());
	points.push_back(new_point_);
}
void Bezier::AddPoint(QPointF &point )	//添加节点
{
	points.push_back(point);
}

void Bezier::InsertPoint(QPoint &point )
{
	QPointF new_point_;
	new_point_.setX(point.rx());
	new_point_.setY(point.ry());
	int i;
	double dist,dist1;
	dist=Distance(new_point_, points[0],points[1]);
	int index_=0;
	int size=points.size();
	for(i=1;i<points.size()-1;i++)
	{
		dist1=Distance(new_point_, points[i],points[i+1]);
		if(dist>dist1)
		{
			dist=dist1;
			index_=i;
		}
	}
	points.push_back(points[size-1]);
	for(i=size-1;i>index_+1;i--)
	{
		points[i].setX(points[i-1].rx());
		points[i].setY(points[i-1].ry());
	}
	points[index_+1].setX(new_point_.rx());
	points[index_+1].setY(new_point_.ry());
}

double Bezier::Distance(QPointF p1, QPointF p2, QPointF p3)
{
	if(p2.rx()==p3.rx())
		return (abs(p1.rx()-p2.rx()));
	double dist;
	dist=abs((p2.ry()-p3.ry())*(p1.rx()-p2.rx()) + (p2.rx()-p3.rx())*(p1.ry()-p2.ry()))/sqrt(pow((p2.rx()-p3.rx()),2.0) + pow(p2.ry()-p3.ry(),2.0));
	return dist;
}

void Bezier::ChangeLastPoint(QPoint &point)
{
	points.pop_back();
	QPointF new_point_;
	new_point_.setX(point.rx());
	new_point_.setY(point.ry());
	points.push_back(new_point_);
}

void Bezier::DeletePoint(QPoint &point)
{
	int i;
	int index_=0;
	double dist;
	for(i=0;i<points.size();i++)
	{
		dist=sqrt((points[i].rx()-point.rx())*(points[i].rx()-point.rx())+(points[i].ry()-point.ry())*(points[i].ry()-point.ry()));
		if(dist<5*POINT_SIZE)
			index_=i;
	}
	vector<QPointF > New_Points;
	for(i=0;i<points.size();i++)
		if(i!=index_)
			New_Points.push_back(points[i]);
	points.clear();
	for(i=0;i<New_Points.size();i++)
		points.push_back(New_Points[i]);

}
void Bezier::Selected_Point(QPoint &point)
{
	int i,selected;
	double dist;
	for(i=0;i<points.size();i++)
	{
		dist=sqrt((points[i].rx()-point.rx())*(points[i].rx()-point.rx())+(points[i].ry()-point.ry())*(points[i].ry()-point.ry()));
		if(dist<5*POINT_SIZE)
		{
			selected_index_=i;
			selected_curve_=false;
			selected_curve_right_=false;
		}
	}
}
void Bezier::ChangeSelectedPoint(QPoint &point)
{
	if(selected_index_<INT_MAX)
	{
		points[selected_index_].setX(point.rx());
		points[selected_index_].setY(point.ry());
	}
	//selected_index_=INT_MAX;
}
void Bezier::Selected_curve(QPoint &point, int flag)
{
	double distance;
	int i;
	for(i=0;i<points_curve.size();i++)
	{
		distance=sqrt((point.rx()-points_curve[i].rx())*(point.rx()-points_curve[i].rx())+(point.ry()-points_curve[i].ry())*(point.ry()-points_curve[i].ry()));
		if(distance<3*POINT_SIZE)
		{
			if(flag)
			{
				selected_curve_=true;
				selected_curve_right_=false;
			}
			else
			{
				selected_curve_right_=true;
				selected_curve_=false;
			}
			selected_index_=INT_MAX;
		}
	}
}

void Bezier::Move_curve(QPoint &point_start_, QPoint &point_end_)
{
	if(!selected_curve_)
		return;
	float move_x,move_y;
	move_x=point_end_.rx()-point_start_.rx();
	move_y=point_end_.ry()-point_start_.ry();
	int i;
	for(i=0;i<points.size();i++)
	{
		points[i].setX(points[i].rx()+move_x);
		points[i].setY(points[i].ry()+move_y);
	}
	for(i=0;i<points_curve.size();i++)
	{
		points_curve[i].setX(points_curve[i].rx()+move_x);
		points_curve[i].setY(points_curve[i].ry()+move_y);
	}
}
void Bezier::DrawPoint( QPointF &point, QPainter &painter, int flag )
{
	int dx,dy;
	for( dx=-POINT_SIZE; dx<=POINT_SIZE; dx++ )
		for( dy=-POINT_SIZE; dy<=POINT_SIZE; dy++ )
			if( dx*dx+dy*dy < POINT_SIZE*POINT_SIZE )
			{
				if(flag==0)		//this point is not chosen
					painter.setPen(Qt::black);
				else if(flag==1) 
					painter.setPen(QPen(QColor(0,155,100)));
				else
					painter.setPen(QPen(QColor(100,155,0)));
				painter.drawPoint(point.rx()+dx,point.ry()+dy);
			}
}
void Bezier::Draw_polygon(QPainter &painter)
{
	int i;
	int flag=0;
	for(i=0;i<points.size();i++)
	{
		if(i==selected_index_)
			flag=1;
		DrawPoint( points[i],painter, flag );
		flag=0;
	}
	painter.setPen(QPen(Qt::blue, LINE_SIZE));
	for(i=1;i<points.size();i++)
		painter.drawLine(points[i-1],points[i]);
	if(evaluation_)
		DrawPoint(evaluation_point_,painter, -1 );
}
void Bezier::Draw_curve(QPainter &painter)
{
	int i;
	if(!selected_curve_ && !selected_curve_right_)
		painter.setPen(QPen(Qt::red, LINE_SIZE));
	else if(selected_curve_)
		painter.setPen(QPen(QColor(0,155,100), LINE_SIZE));
	else
		painter.setPen(QPen(QColor(155,0,100), LINE_SIZE));
	for(i=1;i<points_curve.size();i++)
		painter.drawLine(points_curve[i-1],points_curve[i]);
}
QPointF Bezier::Evaluation(float t)
{
	Bezier *temp_curve_;
	Bezier left,right;
	temp_curve_=new Bezier; 
	int size_=points.size();
	int i,j;
	for(i=0;i<size_;i++)
		temp_curve_->AddPoint(points[i]);
	temp_curve_->Subdivision(left,right,t);
	double rx= left.points[size_-1].rx();
	double ry= left.points[size_-1].ry();
	evaluation_point_.setX(rx);
	evaluation_point_.setY(ry);
	evaluation_=true;
	selected_curve_=false;
	selected_curve_right_=false;
	return evaluation_point_;
}
void Bezier::Subdivision(Bezier &left, Bezier &right,float t)
{
	QPointF point_;
	int num=points.size();
	int i,k;
	float rx_ins_,ry_ins_,rx,ry;
 	for(i=0;i<num-1;i++)
	{
		rx_ins_=(1-t)*points[i].rx()+t*points[i+1].rx();
		ry_ins_=(1-t)*points[i].ry()+t*points[i+1].ry();
		//point_ins.setX(rx);
		//point_ins.setY(ry);
		//Bezier->points.insert(points.begin()+i+1,point_ins);
		int num_=points.size();
		point_.setX(points[num_-1].rx());
		point_.setY(points[num_-1].ry());
		points.push_back(point_);
		for(k=num_-2;k>i;k--)
		{
			rx=points[k].rx();
			ry=points[k].ry();
			points[k+1].setX(rx);
			points[k+1].setY(ry);
		}
		points[i+1].setX(rx_ins_);
		points[i+1].setY(ry_ins_);
		for(k=i+2;k<num;k++)
		{
			rx=(1-t)*points[k].rx()+t*points[k+1].rx();
			ry=(1-t)*points[k].ry()+t*points[k+1].ry();
			points[k].setX(rx);
			points[k].setY(ry);
		}
	}
	num=points.size();
	if(left.points.size())
		left.points.clear();
	if(right.points.size())
		right.points.clear();
	for(i=0;i<=num/2;i++)
		left.AddPoint(points[i]);
	for(i=num/2;i<num;i++)
		right.AddPoint(points[i]);

}
void Bezier::Subdivision(Bezier *left, Bezier *right,float t)
{
	QPointF point_;
	vector<QPointF> points_temp;
	int num=points.size();
	int i,k;
	float rx_ins_,ry_ins_,rx,ry;
	for(i=0;i<num;i++)
		points_temp.push_back(points[i]);
 	for(i=0;i<num-1;i++)
	{
		rx_ins_=(1-t)*points_temp[i].rx()+t*points_temp[i+1].rx();
		ry_ins_=(1-t)*points_temp[i].ry()+t*points_temp[i+1].ry();
		//point_ins.setX(rx);
		//point_ins.setY(ry);
		//Bezier->points.insert(points.begin()+i+1,point_ins);
		int num_=points_temp.size();
		point_.setX(points_temp[num_-1].rx());
		point_.setY(points_temp[num_-1].ry());
		points_temp.push_back(point_);
		for(k=num_-2;k>i;k--)
		{
			rx=points_temp[k].rx();
			ry=points_temp[k].ry();
			points_temp[k+1].setX(rx);
			points_temp[k+1].setY(ry);
		}
		points_temp[i+1].setX(rx_ins_);
		points_temp[i+1].setY(ry_ins_);
		for(k=i+2;k<num;k++)
		{
			rx=(1-t)*points_temp[k].rx()+t*points_temp[k+1].rx();
			ry=(1-t)*points_temp[k].ry()+t*points_temp[k+1].ry();
			points_temp[k].setX(rx);
			points_temp[k].setY(ry);
		}
	}
	num=points_temp.size();
	if(left->points.size())
		left->points.clear();
	if(right->points.size())
		right->points.clear();
	for(i=0;i<=num/2;i++)
		left->AddPoint(points_temp[i]);
	for(i=num/2;i<num;i++)
		right->AddPoint(points_temp[i]);

}


void Bezier::Degree_Elevation()
{
	int size_=points.size();
	QPointF New_Point_;
	int i;
	New_Point_.setX(points[size_-1].rx());
	New_Point_.setY(points[size_-1].ry());
	for(i=size_-1;i>0;i--)
	{
		points[i].rx()=(size_-i)*points[i].rx()/size_+i*points[i-1].rx()/size_;
		points[i].ry()=(size_-i)*points[i].ry()/size_+i*points[i-1].ry()/size_;
	}
	points.push_back(New_Point_);
}

Bezier* Bezier::Copy_Curve()
{
	Bezier* New_Poly_;
	New_Poly_=new Bezier;
	int k;
	for(k=0;k<points.size();k++)
	{
		QPoint New_Point_;
		int x,y;
		x=points[k].rx();
		y=points[k].ry();
		New_Point_.setX(x);
		New_Point_.setY(y);
		New_Poly_->AddPoint(New_Point_);
	}
	return New_Poly_;
}
void Bezier::SaveCurveAsImage(QImage *image)
{
	if (points.size()< 1)
	{
		return;
	}
	float delta_t=0.00001;
	float t = 0;
	QPointF p;
	for(;t<1.0;t=t+delta_t)
	{
		p = Evaluation(t);
		image->setPixel(p.x(), p.y(), qRgb(255, 0, 0));
	}
}
void Bezier::Get_simple_Bezier()
{
	Bezier Mid_polygon_,Left_polygon_,Right_polygon_;
	queue<Bezier > Mid_polygons_;
	int i,j;
	for(i=0;i<points.size();i++)
		Mid_polygon_.AddPoint(points[i]);
	Mid_polygons_.push(Mid_polygon_);
	for(i=0;i<REFINE_TIME_;i++)
	{
		int num_=pow(2.0,i);	//the number of polygon will be popped out
		for(j=0;j<num_;j++)
		{
			Mid_polygon_=Mid_polygons_.front();
			Mid_polygon_.Subdivision(Left_polygon_,Right_polygon_,0.5);
			Mid_polygons_.push(Left_polygon_);
			Mid_polygons_.push(Right_polygon_);
			Mid_polygons_.pop();
		}
	}
	Bezier Poly_;
	int member_num_=Mid_polygons_.size();
	int point_num_;
	Poly_=Mid_polygons_.front();
	Mid_polygons_.pop();
	for(i=0;i<Poly_.points.size();i++)
		points_curve.push_back(Poly_.points[i]);
	for(i=1;i<member_num_;i++)
	{	
		Poly_=Mid_polygons_.front();
		Mid_polygons_.pop();
		for(j=1;j<Poly_.points.size();j++)
		{
			points_curve.push_back(Poly_.points[j]);
		}
	}
}
void Bezier::Get_composite_Bezier()
{
	Bezier *New_Poly_;
	vector<Bezier*> New_Curves_;
	QPointF Point_,Point_L_,Point_R_,Point_P0_,Point_P1_;
	int size_=points.size();
	int i,j,k;

	float rx,ry;

	MatrixXd A;
	VectorXd q_x(size_),p_x(size_),q_y(size_),p_y(size_);
	A=MatrixXd::Identity(size_,size_);
	A=2.0/3*A;
	for(i=0;i<size_-1;i++)
		A(i,i+1)=1.0/6;
	for(i=1;i<size_;i++)
		A(i,i-1)=1.0/6;
	A(0,size_-1)=1.0/6;
	A(size_-1,0)=1.0/6;
	for(i=0;i<size_;i++)
	{
		Point_=points[i];
		p_x(i)=Point_.rx();
		p_y(i)=Point_.ry();
	}
	q_x=A.lu().solve(p_x);
	q_y=A.lu().solve(p_y);
	

	for(i=0;i<size_-1;i++)
	{
		New_Poly_=new Bezier;
		Point_P0_=points[i];
		Point_P1_=points[i+1];
		//得到L（i+1）的坐标
		rx=(q_x(i)+2*q_x(i+1))/3;
		ry=(q_y(i)+2*q_y(i+1))/3;
		Point_L_.setX(rx);
		Point_L_.setY(ry);
		//得到R(i)的坐标
		rx=(2*q_x(i)+q_x(i+1))/3;
		ry=(2*q_y(i)+q_y(i+1))/3;
		Point_R_.setX(rx);
		Point_R_.setY(ry);
		New_Poly_->AddPoint(Point_P0_);
		New_Poly_->AddPoint(Point_R_);
		New_Poly_->AddPoint(Point_L_);
		New_Poly_->AddPoint(Point_P1_);
		New_Poly_->Get_simple_Bezier();
		New_Curves_.push_back(New_Poly_);
	}
	New_Poly_=new Bezier;
	Point_P0_=points[size_-1];
	Point_P1_=points[0];

	rx=(q_x(size_-1)+2*q_x(0))/3;
	ry=(q_y(size_-1)+2*q_y(0))/3;
	Point_L_.setX(rx);
	Point_L_.setY(ry);

	rx=(2*q_x(size_-1)+q_x(0))/3;
	ry=(2*q_y(size_-1)+q_y(0))/3;
	Point_R_.setX(rx);
	Point_R_.setY(ry);
	New_Poly_->AddPoint(Point_P0_);
	New_Poly_->AddPoint(Point_R_);
	New_Poly_->AddPoint(Point_L_);
	New_Poly_->AddPoint(Point_P1_);
	New_Poly_->Get_simple_Bezier();
	New_Curves_.push_back(New_Poly_);

	for(i=0;i<New_Curves_.size();i++)
	{
		for(j=0;j<New_Curves_[i]->points.size();j++)
			points_composite_.push_back(New_Curves_[i]->points[j]);
		for(j=0;j<New_Curves_[i]->points_curve.size();j++)
			points_curve.push_back(New_Curves_[i]->points_curve[j]);
	}
	
}

void Bezier::Get_Interpolate_Curve()
{
	int i,k;
	points_curve.clear();
	for(i=0;i<points.size();i++)
		points_curve.push_back(points[i]);
	for(k=0;k<REFINE_TIME_;k++)
		points_curve=Four_points_op(points_curve);
	points_curve.push_back(points_curve[0]);

}

vector<QPointF> Bezier::Four_points_op(vector<QPointF> op_points)
{
	vector<QPointF> new_points;
	QPointF new_point;
	if(new_points.size())
		new_points.clear();
	int i,j,k;
	int size_=op_points.size();
	double x,y;
	for(i=0;i<size_;i++)
	{
		new_points.push_back(op_points[i]);
		x = 1.0/16 *(-op_points[(i-1+size_)%size_].rx() + 9*op_points[i%size_].rx() + 9*op_points[(i+1)%size_].rx() - op_points[(i+2)%size_].rx());
		y = 1.0/16 *(-op_points[(i-1+size_)%size_].ry() + 9*op_points[i%size_].ry() + 9*op_points[(i+1)%size_].ry() - op_points[(i+2)%size_].ry());
		new_point.setX(x);
		new_point.setY(y);
		new_points.push_back(new_point);
	}
	//new_points.push_back(new_points[0]);
	return new_points;
}
 void Bezier::Get_convex_rect()
 {
	 convex_rect = new Rectangle;
	 if(!points.size())
		 convex_rect->Generate(0,0,0,0);
	 else
	 {
		 double min_x = points[0].rx();
		 double min_y = points[0].ry();
		 double max_x = points[0].rx();
		 double max_y = points[0].ry();
		 int i;
		 for(i=1;i<points.size();i++)
		 {
			min_x = points[i].rx() < min_x ? points[i].rx(): min_x;
			max_x = points[i].rx() > max_x ? points[i].rx(): max_x;
			min_y = points[i].ry() < min_y ? points[i].ry(): min_y;
			max_y = points[i].ry() > max_y ? points[i].ry(): max_y;
		 }
		 convex_rect->Generate(min_x, min_y, max_x, max_y);
	 }
 }

 vector<QPointF> Bezier::intersection(Bezier* C)
 {
	 Bezier* temp_curve_1=Copy_Curve();
	 Bezier* temp_curve_2=C->Copy_Curve();
	 queue<Bezier* > Bezier_pairs;
	 Bezier_pairs.push(temp_curve_1);
	 Bezier_pairs.push(temp_curve_2);
	 vector<QPointF> intersection_points;
	 QPointF point;
	 double x1, x2, y1, y2;
	 Bezier *temp_curve_11,*temp_curve_12, *temp_curve_21, *temp_curve_22;
	 //Bezier Left,Right;
	 for(;;)
	 {
		 if(Bezier_pairs.size() < 2)
			 break;
		 temp_curve_1=Bezier_pairs.front();
		 Bezier_pairs.pop();
		 temp_curve_2=Bezier_pairs.front();
		 Bezier_pairs.pop();
		 temp_curve_1->Get_convex_rect();
		 temp_curve_2->Get_convex_rect();
		// temp_curve_1->CalcBoundingBox();
		 //temp_curve_2->CalcBoundingBox();
		// QRectF bbox1 = temp_curve_1->BBox_;
		 //QRectF bbox2 = temp_curve_2->BBox_;
		 
		 //float size1 = sqrt(bbox1.width()*bbox1.width() + bbox1.height()*bbox1.height());
		 //float size2 = sqrt(bbox2.width()*bbox2.width() + bbox2.height()*bbox2.height());

		 float size1 = temp_curve_1->convex_rect->diam();
		 float size2 = temp_curve_2->convex_rect->diam();
		// if(!bbox1.intersects(bbox2))
			// continue;
		 if(!temp_curve_1->convex_rect->intersection(temp_curve_2->convex_rect))
			 continue;
		 else if (size1 < EPSILON && size2 < EPSILON)
		 {
			//QPointF p = 0.5*(bbox1.center() + bbox2.center());
			 QPointF p = 0.5 * (temp_curve_1->convex_rect->Center() + temp_curve_2->convex_rect->Center());
			intersection_points.push_back(p);
		 }
		 else
		 {
			 temp_curve_11 = new Bezier;
			 temp_curve_12 = new Bezier;
			 temp_curve_21 = new Bezier;
			 temp_curve_22 = new Bezier;

			 temp_curve_1->Subdivision(temp_curve_11,temp_curve_12, 0.5);
			 temp_curve_2->Subdivision(temp_curve_21,temp_curve_22, 0.5);

			 Bezier_pairs.push(temp_curve_11);
			 Bezier_pairs.push(temp_curve_21);

			 Bezier_pairs.push(temp_curve_11);
			 Bezier_pairs.push(temp_curve_22);

			 Bezier_pairs.push(temp_curve_12);
			 Bezier_pairs.push(temp_curve_21);

			 Bezier_pairs.push(temp_curve_12);
			 Bezier_pairs.push(temp_curve_22);
		 }
	 }
	
	 return intersection_points;
 }

 void Bezier::CalcBoundingBox()
{
	float xMin, xMax, yMin, yMax;
	xMin =  INF;  yMin =  INF;
	xMax = -INF;  yMax = -INF;
	for (int i=0; i<points.size(); i++)
	{
		QPointF p = points[i];
		if (p.x() < xMin) xMin = p.x();
		if (p.x() > xMax) xMax = p.x();
		if (p.y() < yMin) yMin = p.y();
		if (p.y() > yMax) yMax = p.y();
	}
	QPointF topLeft = QPointF(xMin, yMin);
	QPointF bottomRight = QPointF(xMax, yMax);
	BBox_ = QRectF(topLeft, bottomRight);
}

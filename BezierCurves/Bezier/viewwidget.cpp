#include "viewwidget.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include <QFileDialog>
#define MAX_MM 10000000
using namespace std;
ViewWidget::ViewWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	draw_status_=false;
	flag_draw_=0;
	Delete_point_=false;
	Insert_=false;
	intersection_= false;
	Control_polygon_=NULL;
	point_prev.setX(0);
	point_prev.setY(0);
}
void ViewWidget::Check_Draw_Polygon_(bool bv)
{
	is_draw_ctr_=bv;
	update();
}

void ViewWidget::Check_Draw_Bezier_(bool bv)
{
	is_draw_bezier_=bv;
	update();
}

void ViewWidget::Check_Simple_(bool bv)
{
	
	if(bv)
		Curve_Type_=Simple_;
	update();
}

void ViewWidget::Check_Design_name_(bool bv)
{
	if(bv)
		Curve_Type_=Composite_;
	update();
}

void ViewWidget::Check_Interpolate_(bool bv)
{
	if(bv)
		Curve_Type_=Interpolate_; 
	update();
}

void ViewWidget::Check_Intersection_(bool bv)
{
	intersection_ = bv;
	if(!bv)
	{
		if(Intersection_points.size())
			Intersection_points.clear();
	}
	update();
}
void ViewWidget::setDrawStatus()
{
	draw_status_=true;
	
}
ViewWidget::~ViewWidget()
{

}
void ViewWidget::delete_Polygon()
{
	if(Control_polygons_.size()!=0)
		Control_polygons_.pop_back();
}

void ViewWidget::Save_Curve()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("Images(*.png *.bmp *.jpg);;CtrlPts(*.ctrlpts)"));
	if (filename.isNull())
	{
		return;
	}	
	if (filename.at(filename.length()-1) == 's')
	{
		string ctrlptsfile = filename.toLocal8Bit().constData();
		std::ofstream out(ctrlptsfile);  
		if (out.is_open())   
		{
			if (Control_polygon_->points.size()>0)
			{
				out <<"curves " << Control_polygons_.size()<<"\n";
			}
			else
			{
				out <<"curves " << Control_polygons_.size() <<"\n";
			}
			
			for (int i=0; i<Control_polygons_.size(); i++)
			{
				out <<"#"<<i+1<<" "<<Control_polygons_[i]->points.size()<<"\n";
				for (int j=0; j<Control_polygons_[i]->points.size(); j++)
				{
					out << Control_polygons_[i]->points[j].rx()<<" "<< Control_polygons_[i]->points[j].ry()  <<"\n";
				}
			}
		/*	if (Control_polygon_->points.size()>0)
			{
				out <<"#"<<Control_polygons_.size()+1<<" "<<Control_polygon_->points.size()<<"\n";
				for (int i=0; i<Control_polygon_->points.size(); i++)
				{
					out << Control_polygon_->points[i].rx()<<" "<<  Control_polygon_->points[i].ry()  <<"\n";
				}
			}*/
			out.close();  
		}
	}
	else
	{
		QImage *image;
		image = new QImage(width(), height(), QImage::Format_RGB32);
		//image_->invertPixels();
		Control_polygon_->SaveCurveAsImage(image);
		for (int i=0; i<Control_polygons_.size(); i++)
		{
			Control_polygons_[i]->SaveCurveAsImage(image);
		}
		image->save(filename);
	}
}


void ViewWidget::Open_Curve()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("CtrlPts(*.ctrlpts)"));
	std::string file = filename.toLocal8Bit().constData();
	std::ifstream infile; 
	infile.open(file.data());
	assert(infile.is_open());   

	string s, temps;
	getline(infile, s);
	temps.assign(s, 7, s.length()-7);
	int curveCnt = atoi(temps.c_str());
	for (int i=0; i<curveCnt; i++)
	{
		getline(infile, s);
		int ctrlptCnt = 0;
		for (int j=0; j<s.length(); j++)
		{
			if (s.at(j) != ' ')
			{
				continue;
			}
			else
			{
				j++;
				temps.clear();
				int nn=s.length();
				temps.assign(s, j, nn-j);
				ctrlptCnt = atoi(temps.c_str());
				break;
			}
		}
		Bezier *bctemp;
		bctemp = new Bezier();
		for (int pi=0; pi<ctrlptCnt; pi++)
		{
			if (getline(infile,s))
			{
				string sxy[2];
				int k0 = 0;
				for (int j=0; j<2; j++)
				{
					for (int k=k0; k<s.length(); k++)
					{
						if (s.at(k) != ' ')
						{
							sxy[j] += s.at(k);
						}
						else
						{
							k0 = k;
							k0++;
							break;
						}
					}
				}
				bctemp->AddPoint(QPointF(atof(sxy[0].c_str()), atof(sxy[1].c_str())));
			}
		}
		bctemp->Get_simple_Bezier();
		Control_polygons_.push_back(bctemp);
	}

	infile.close();          
	cout<<"Control Points Read Finished!"<<endl;
	update();
}
void ViewWidget::Subdivision_op(double t)
{
	Bezier *Left,*Right;
	for(int i=0;i < Control_polygons_.size();i++)
	{
		if(Control_polygons_[i]->selected_curve_right_)
		{
			Left=new Bezier;
			Right=new Bezier;
			Control_polygons_[i]->Subdivision(*Left, *Right, t);
			Right->Get_simple_Bezier();
			Control_polygons_[i]=Left->Copy_Curve();
			Control_polygons_[i]->Get_simple_Bezier();
			Control_polygons_.insert(Control_polygons_.begin()+i+1,Right);
		}
	}
	update();
}

QPointF ViewWidget::Evaluation_op(double t)
{
	int index=INT_MAX;
	QPointF Point_;
	for(int i=0;i < Control_polygons_.size();i++)
	{
		if(Control_polygons_[i]->selected_curve_right_)
		{
			Point_=Control_polygons_[i]->Evaluation(t);
			index=i;
		}
	}
	update();
	if(index<INT_MAX)
		return Control_polygons_[index]->evaluation_point_;
	else
	{
		Point_.setX(INT_MAX);
		Point_.setY(INT_MAX);
		return Point_;
	}

}
void ViewWidget::Elevation_op()
{
	for(int i=0;i<Control_polygons_.size();i++)
	{
		if(Control_polygons_[i]->selected_curve_right_)
		{
			Control_polygons_[i]->Degree_Elevation();
			Control_polygons_[i]->selected_curve_right_=false;
		}
	}
	update();
}

void ViewWidget::Insert_op()
{
	Insert_=true;
}

void ViewWidget::Delete_point_op()
{
	Delete_point_=true;
}

void ViewWidget::Intersection_op()
{
	Intersection_points.clear();
	for(int i=0;i<Control_polygons_.size();i++)
	{
		if(Control_polygons_[i]->selected_curve_right_)
		{
			for(int j=i+1; j<Control_polygons_.size();j++)
				if(Control_polygons_[j]->selected_curve_right_)
				{
					Bezier *Curve = new Bezier;
					Curve->points=Control_polygons_[i]->intersection(Control_polygons_[j]);
					//Control_polygons_[i]->Intersections(Control_polygons_[j],Curve->points);
					Intersection_points.push_back(Curve);
					Control_polygons_[j]->selected_curve_right_=false;
				}
				Control_polygons_[i]->selected_curve_right_=false;
		}
	}
	update();
}
void ViewWidget::mousePressEvent(QMouseEvent *event)
{
	if(!draw_status_ && Control_polygons_.size()!=0)
	{
		if(Qt::LeftButton==event->button() )
		{
			if(!Insert_ && !Delete_point_)
				for(int i=0;i<Control_polygons_.size();i++)
				{
					Control_polygons_[i]->Selected_curve(event->pos(),1);
					if(Control_polygons_[i]->selected_curve_)
						point_prev=event->pos();
					Control_polygons_[i]->Selected_Point(event->pos());
				}
			else
			{
				if(Insert_)
				{	for(int i=0;i<Control_polygons_.size();i++)
					{
						if(Control_polygons_[i]->selected_curve_right_)
						{
							Control_polygons_[i]->InsertPoint(event->pos());
							Control_polygons_[i]->selected_curve_right_=false;
						}
					}
				Insert_=false;
				}
				if(Delete_point_)
				{
					for(int i=0;i<Control_polygons_.size();i++)
					{
						if(Control_polygons_[i]->selected_curve_right_)
						{
							Control_polygons_[i]->DeletePoint(event->pos());
							Control_polygons_[i]->selected_curve_right_=false;
						}
					}
				Delete_point_=false;
				}
			}
		}
		else if(Qt::RightButton==event->button() )
		{
			for(int i=0;i<Control_polygons_.size();i++)
			{
				Control_polygons_[i]->Selected_curve(event->pos(),0);
			}
			for(int i=0;i<Control_polygons_.size();i++)
				if(Control_polygons_[i]->selected_curve_right_)
					Control_polygons_[i]->Selected_Point(event->pos());

		}
	}
	if( draw_status_ && Qt::LeftButton == event->button() )
	{
		if(!flag_draw_)
		{
			flag_draw_=1;
			Control_polygon_=new Bezier(event->pos());
			Control_polygons_.push_back(Control_polygon_);
		}
			Control_polygon_->AddPoint(event->pos());
	}
	else if(draw_status_ && Qt::RightButton == event->button())
	{
		
		if(Control_polygon_)
		{
			flag_draw_=0;
			draw_status_=false;
		}
	}
}
void ViewWidget::mouseMoveEvent(QMouseEvent *event)
{
	if(flag_draw_)
	{
		setMouseTracking(true);
		Control_polygon_->ChangeLastPoint(event->pos());
	}
	if(!flag_draw_)
	{
		setMouseTracking(false);
		for(int i=0;i<Control_polygons_.size();i++)
		{
				Control_polygons_[i]->ChangeSelectedPoint(event->pos());
				if(!point_prev.rx() && !point_prev.ry())
					point_prev=event->pos();
				Control_polygons_[i]->Move_curve(point_prev,event->pos());
				if(intersection_)
				{
					Intersection_points.clear();
					for(int j =0 ;j<Control_polygons_.size();j++)
					{
						if(j==i) continue;
						else
						{
							Bezier *Curve = new Bezier;
							Curve->points=Control_polygons_[i]->intersection(Control_polygons_[j]);
							Intersection_points.push_back(Curve);
						}
					}
				}
			
		}
		point_prev=event->pos();
		
	}

}
void ViewWidget::mouseReleaseEvent(QMouseEvent *event)
{
	int record;
	if(!flag_draw_)
	{
		switch(Curve_Type_)
		{
		case Simple_:
			for(int i=0;i<Control_polygons_.size();i++)
			{
				Control_polygons_[i]->points_curve.clear();
				Control_polygons_[i]->Get_simple_Bezier();
				Control_polygons_[i]->End();
			}
			break;
		case Composite_:
			for(int i=0;i<Control_polygons_.size();i++)
			{
				Control_polygons_[i]->points_curve.clear();
				Control_polygons_[i]->Get_composite_Bezier();
				Control_polygons_[i]->End();
			}
			break;
		case Interpolate_:
			for(int i=0;i<Control_polygons_.size();i++)
			{
				Control_polygons_[i]->points_curve.clear();
				Control_polygons_[i]->Get_Interpolate_Curve();
				Control_polygons_[i]->End();
			}

		}
	}
}
void ViewWidget::paintEvent(QPaintEvent *)
 {
	 QPainter painter(this);
	 int i,j,k;
	 if(is_draw_ctr_)
		for(i=0;i<Control_polygons_.size();i++)
			 Control_polygons_[i]->Draw_polygon(painter);
	 if(is_draw_bezier_)
		for(k=0;k<Control_polygons_.size();k++)
			Control_polygons_[k]->Draw_curve(painter);
	 if(Intersection_points.size())
		 for(i=0;i<Intersection_points.size();i++)
			 for(j=0;j<Intersection_points[i]->points.size();j++)
				 Intersection_points[i]->DrawPoint(Intersection_points[i]->points[j],painter, 1);
	 update();
 }
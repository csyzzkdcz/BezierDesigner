#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QWidget>
#include "ui_viewwidget.h"
#include <qevent.h>
#include <qpainter.h>
#include "Bezier.h"
#include <queue>
#include <Eigen>

enum Type_{Simple_,Composite_,Interpolate_};

class ViewWidget : public QWidget
{
	Q_OBJECT

public:

	ViewWidget(QWidget *parent = 0);
	~ViewWidget();
	bool draw_status_;
	bool is_draw_ctr_;
	bool is_draw_bezier_;
	bool design_name_;
	bool simple_;
	bool Insert_;
	bool Delete_point_;
	bool intersection_;
	int flag_draw_;
	QPoint point_prev;	//store the previous point;
	Bezier *Control_polygon_;
	
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *);
	

	public slots:
	void setDrawStatus();
	void delete_Polygon();
	void Open_Curve();
	void Save_Curve();
	void Subdivision_op(double t);
	void Elevation_op();
	void Insert_op();
	void Delete_point_op();
	QPointF Evaluation_op(double t);
	void Intersection_op();

	void Check_Draw_Polygon_(bool bv);
	void Check_Draw_Bezier_(bool bv);
	void Check_Simple_(bool bv);
	void Check_Design_name_(bool bv);
	void Check_Interpolate_(bool bv);
	void Check_Intersection_(bool bv);

private:
	Ui::ViewWidget ui;
	vector<Bezier* > Control_polygons_;
	vector<Bezier* > Intersection_points;
	Type_	Curve_Type_;
};

#endif // VIEWWIDGET_H

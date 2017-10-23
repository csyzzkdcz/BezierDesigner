#ifndef BEZIER_H
#define BEZIER_H

#include <QtWidgets/QMainWindow>
#include "ui_bezier.h"
#include "viewwidget.h"

class QLabel;
class QPushButton;
class QCheckBox;
class QRadioButton;
class QGroupBox;
class RenderingWidget;
class QSlider;
class QSpinBox;
class QLineEdit;

class mainwindow : public QMainWindow
{
	Q_OBJECT

public:
	mainwindow(QWidget *parent = 0);
	~mainwindow();

	QAction* Bezier_action_;
	QAction* delete_action_;
	QAction* Open_action_;
	QAction* Save_action_;
	QAction* Subdivision_;
	QAction* Elevation_;
	QAction* Evaluation_;
	QAction* Insert_;
	QAction* Delete_point;
	QAction* Intersection_;

	QMenu* Menu;
	QMenu* Options;
	QMenu* Bezier_Curves_;
	QToolBar* Tool_Bar_File_;
	QToolBar* Tool_Bar_Op_;

	QGroupBox* groupbox_render_;
	QGroupBox* groupbox_options_;

	QCheckBox* check_box_ctr_poly_;
	QCheckBox* check_box_bezier_;
	QCheckBox* check_box_intersection_;

	QRadioButton* check_box_design_name_;
	QRadioButton* check_box_simple_;
	QRadioButton* check_box_interpolate_;

	QSlider* Slider_;
	QLineEdit* Result_x;
	QLineEdit* Result_y;
	QSpinBox* doubleSpinBox_;
	
	void Init();
	private slots:
	void subdivision_();
	void evaluation_();
	
private:
	Ui::BezierClass ui;
	ViewWidget*	view_widget_;
};

#endif // BEZIER_H

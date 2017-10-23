#include "mainwindow.h"
#include <QtWidgets>
#include "qdesktopwidget.h"
#include "qstring.h"
#include <qpainter.h>
mainwindow::mainwindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	view_widget_=new ViewWidget();
	Init();
	setCentralWidget(view_widget_);
	QDesktopWidget *desktop=QApplication::desktop();
	int width=desktop->width();
    int height=desktop->height();
    setGeometry(width*1.0/5,height*1.0/5,3.0*width/5.0,3.0*height/5);
	
	QVBoxLayout *layout_left = new QVBoxLayout;
	layout_left->addWidget(groupbox_render_);
	layout_left->addWidget(groupbox_options_);
	layout_left->addStretch(2);

	QVBoxLayout *layout_main = new QVBoxLayout;

	layout_main->addLayout(layout_left);
	//layout_main->addWidget(renderingwidget_);
	layout_main->setStretch(1, 1);
	this->centralWidget()->setLayout(layout_main);
}

mainwindow::~mainwindow()
{

}
void mainwindow::Init()
{
	Open_action_=new QAction(QIcon(":/Resources/images/open.png"), tr("&Open"),this);
	Save_action_=new QAction(QIcon(":/Resources/images/Save.png"), tr("&Save"),this);
	Bezier_action_= new QAction(QIcon(":/Resources/images/draw.png"), tr("&Draw"), this);
	delete_action_=new QAction(QIcon(":/Resources/images/delete.png"), tr("&Delete"),this);
	Subdivision_=new QAction(QIcon(":/Resources/images/cut.png"),tr("&Subdivision"),this);
	Elevation_=new QAction(QIcon(":/Resources/images/up.png"),tr("&Elevation"),this);
	Evaluation_=new QAction(QIcon(":/Resources/images/evaluation.png"),tr("&Evaluation"),this);
	Insert_=new QAction(QIcon(":/Resources/images/insert.png"), tr("&Insert"), this);
	Delete_point=new QAction(QIcon(":/Resources/images/clear.png"), tr("&Delete Point"), this);
	Intersection_ = new QAction(QIcon(":/Resources/images/intersections.png"), tr("&Intersection"), this);
	
	connect(Open_action_, SIGNAL(triggered()), view_widget_, SLOT(Open_Curve()));
	connect(Save_action_,SIGNAL(triggered()), view_widget_, SLOT(Save_Curve()));
	connect(Bezier_action_, SIGNAL(triggered()), view_widget_, SLOT(setDrawStatus()));
	connect(delete_action_, SIGNAL(triggered()), view_widget_, SLOT(delete_Polygon()));

	connect(Subdivision_, SIGNAL(triggered()), this, SLOT(subdivision_()));
	connect(Evaluation_, SIGNAL(triggered()), this, SLOT(evaluation_()));
	connect(Elevation_, SIGNAL(triggered()), view_widget_, SLOT(Elevation_op()));
	connect(Insert_,SIGNAL(triggered()), view_widget_, SLOT(Insert_op()));
	connect(Delete_point, SIGNAL(triggered()), view_widget_, SLOT(Delete_point_op()));
	connect(Intersection_, SIGNAL(triggered()), view_widget_, SLOT(Intersection_op()));

	Menu=menuBar()->addMenu(tr("&Menu"));
	Menu->addAction(Bezier_action_);
	Menu->addAction(delete_action_);
	Menu->addAction(Open_action_);
	Menu->addAction(Save_action_);

	Options=menuBar()->addMenu(tr("&Options"));
	Options->addAction(Subdivision_);
	Options->addAction(Elevation_);
	Options->addAction(Evaluation_);
	Options->addAction(Insert_);
	Options->addAction(Delete_point);
	Options->addAction(Intersection_);


	Tool_Bar_File_=addToolBar(tr("&ToolBar"));
	Tool_Bar_File_->addAction(Open_action_);
	Tool_Bar_File_->addAction(Save_action_);

	Tool_Bar_Op_=addToolBar(tr("&Operator"));
	Tool_Bar_Op_->addAction(Bezier_action_);
	Tool_Bar_Op_->addAction(delete_action_);

	check_box_ctr_poly_ = new QCheckBox(tr("Control Ploygon"), this);
	connect(check_box_ctr_poly_, SIGNAL(clicked(bool)), view_widget_, SLOT(Check_Draw_Polygon_(bool)));
	check_box_ctr_poly_->setChecked(true);

	check_box_bezier_ = new QCheckBox(tr("Bezier Curve"), this);
	connect(check_box_bezier_, SIGNAL(clicked(bool)), view_widget_, SLOT(Check_Draw_Bezier_(bool)));
	check_box_bezier_->setChecked(true);

	check_box_intersection_ = new QCheckBox(tr("Intersection"), this);
	connect(check_box_intersection_,SIGNAL(clicked(bool)), view_widget_, SLOT(Check_Intersection_(bool)));
	check_box_intersection_->setChecked(false);

	check_box_simple_=new QRadioButton(tr("simple Bezier Curve"),this);
	connect(check_box_simple_, SIGNAL(clicked(bool)), view_widget_, SLOT(Check_Simple_(bool)));
	
	check_box_design_name_=new QRadioButton(tr("Design name"), this);
	connect(check_box_design_name_, SIGNAL(clicked(bool)), view_widget_, SLOT(Check_Design_name_(bool)));

	check_box_interpolate_=new QRadioButton(tr("Interpolation curve"), this);
	connect(check_box_interpolate_, SIGNAL(clicked(bool)), view_widget_, SLOT(Check_Interpolate_(bool)));

	groupbox_render_ = new QGroupBox(tr("Choice"), this);

	QHBoxLayout* render_layout = new QHBoxLayout(groupbox_render_);
	render_layout->addWidget(check_box_ctr_poly_);
	render_layout->addWidget(check_box_bezier_);
	render_layout->addWidget(check_box_intersection_);
	render_layout->addWidget(check_box_simple_);
	render_layout->addWidget(check_box_design_name_);
	render_layout->addWidget(check_box_interpolate_);

	groupbox_options_=new QGroupBox(tr("Options"),this);

	QHBoxLayout* render_layout_op_ = new QHBoxLayout(groupbox_options_);
	


	Slider_=new QSlider(Qt::Horizontal);
	doubleSpinBox_=new QSpinBox;
	Slider_->setRange(0,100);
	Slider_->setFixedWidth(900);
	doubleSpinBox_->setRange(0,100);
	doubleSpinBox_->setFixedWidth(100);

	connect(Slider_, SIGNAL(valueChanged(int)),doubleSpinBox_, SLOT(setValue(int)));
	connect(doubleSpinBox_, SIGNAL(valueChanged(int)),Slider_, SLOT(setValue(int)));
	render_layout_op_->addWidget(Slider_);
	render_layout_op_->addWidget(doubleSpinBox_);

	Result_x= new QLineEdit;
	Result_y= new QLineEdit;
	Result_x->setFixedWidth(100);
	Result_y->setFixedWidth(100);
	render_layout_op_->addWidget(Result_x);
	render_layout_op_->addWidget(Result_y);
}

void mainwindow::subdivision_()
{
	double t=1.0*Slider_->value()/100;
	view_widget_->Subdivision_op(t);
}

void mainwindow::evaluation_()
{
	double t=1.0*Slider_->value()/100;
	QPointF point_;
	point_=view_widget_->Evaluation_op(t);
	double rx=point_.rx();
	double ry=point_.ry();
	QString strX=QString::number(rx);
	QString strY=QString::number(ry);
	Result_x->setText(strX);
	Result_y->setText(strY);
}
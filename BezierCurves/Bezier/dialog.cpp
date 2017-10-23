#include "dialog.h"


dialog::dialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	doubleSpinBox =new QSpinBox;
	horizontalSlider =new QSlider(Qt::Horizontal);
	connect(doubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(SetSliderValue()));
	connect(horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(SetSpinerBoxValue()));

}

dialog::~dialog()
{

}

double dialog::GetData()
{
	double value = doubleSpinBox->value();
	return value;
}

void dialog::SetX(double x)
{
	QString strX = QString::number(x);
	lineEditResultX->setText(strX);
}

void dialog::SetY(double y)
{
	QString strY = QString::number(y);
	lineEditResultY->setText(strY);
}

void dialog::SetSliderValue()
{
	double t = doubleSpinBox->value();
	horizontalSlider->setValue(100*t);
}

void dialog::SetSpinerBoxValue()
{
	int t = horizontalSlider->value();
	doubleSpinBox->setValue(t*1.0f/100.0f);
}
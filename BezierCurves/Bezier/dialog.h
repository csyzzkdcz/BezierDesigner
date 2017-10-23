#ifndef DIALOG_H
#define DIALOG_H

#include <QtWidgets/QDialog>
#include "ui_dialog.h"
#include <qslider.h>
#include <qspinbox.h>
#include <qlineedit.h>

class dialog : public QDialog
{
	Q_OBJECT

public:
	dialog(QWidget *parent = 0);
	~dialog();

private:
	Ui::dialog ui;

public:
	double GetData();
	void SetX(double x);
	void SetY(double);

public:
	QSlider* horizontalSlider;
	QSpinBox* doubleSpinBox;
	QLineEdit* lineEditResultX;
	QLineEdit* lineEditResultY;


private slots:
	void SetSliderValue();
	void SetSpinerBoxValue();

};

#endif // DIALOG_H

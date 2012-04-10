#pragma once

#include <QtGui/QMainWindow>
#include "ui_application.h"


class application : public QMainWindow
{
	Q_OBJECT

public:
	application(QWidget *parent = 0, Qt::WFlags flags = 0);
	~application();

signals:

public slots:

protected:

private:
	Ui::applicationClass ui;
};

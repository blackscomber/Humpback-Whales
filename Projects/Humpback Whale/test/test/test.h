#ifndef SKELETONKEY_H
#define SKELETONKEY_H

#include <QtGui/QMainWindow>
#include "ui_test.h"

class SkeletonKey : public QMainWindow
{
	Q_OBJECT

public:
	SkeletonKey(QWidget *parent = 0, Qt::WFlags flags = 0);
	~SkeletonKey();

private:
	Ui::SkeletonKeyClass ui;
};

#endif // SKELETONKEY_H

#include "test.h"
#include "d3dwidget.h"
#include <QStandardItem>
#include <QStandardItemModel>

D3DWidget* d3dWidget;
SkeletonKey::SkeletonKey(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	d3dWidget = new D3DWidget( ui.preview );

	//QStandardItem* item = new QStandardItem("Basic Sphere");
	//QStandardItemModel* model = new QStandardItemModel(ui.toc);
	//model->appendRow(item);
	//ui.toc->setModel(model);
}

SkeletonKey::~SkeletonKey()
{

}

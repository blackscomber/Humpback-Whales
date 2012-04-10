#include "application.h"
#include "mainwidget.h"
 

__declspec(selectany) MainWidget* g_pMainWidget = NULL;

application::application(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)

{
	ui.setupUi(this);

	g_pMainWidget = new MainWidget(ui.mainwidget);
}

application::~application()
{
}
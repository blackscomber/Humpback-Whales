#include "d3dwidget.h"
#include "Renderer.h"

D3DWidget::D3DWidget(QWidget* parent, Qt::WindowFlags flags) 
	:	QWidget(parent, flags)
{
	setFixedSize(parent->width(), parent->height());
	setAttribute(Qt::WA_PaintOnScreen, true);
	setUpdatesEnabled(false);
	startTimer(30);

	theRenderer.StaticConstructor();
	theRenderer.CreateDevice( winId(), width(), height() );
}

D3DWidget::~D3DWidget()
{
	theRenderer.StaticDestructor();
}

void D3DWidget::timerEvent(QTimerEvent *)
{
	theRenderer.DoRender();
}

void D3DWidget::mousePressEvent(QMouseEvent* e)
{
#if 0
	if( e->buttons() & Qt::RightButton )
	{
		theLightArcBall.DragStart( e->x(), e->y() );
	}
	else
	{
		theModelArcBall.DragStart( e->x(), e->y() );
	}
#endif
}

void D3DWidget::mouseMoveEvent(QMouseEvent* e)
{
#if 0
	if( e->buttons() & Qt::RightButton )
	{
		theLightArcBall.Drag( e->x(), e->y() );
	}
	else
	{
		theModelArcBall.Drag( e->x(), e->y() );
	}
#endif
}
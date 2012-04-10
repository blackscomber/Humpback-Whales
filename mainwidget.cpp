#include "mainwidget.h"
#include "D3DRenderer.h"
#include "ArcBall.h"


MainWidget::MainWidget(QWidget *parent)
	: QWidget(parent)
{

	setFixedSize(parent->width(), parent->height());
	setAttribute(Qt::WA_PaintOnScreen, true);
	setUpdatesEnabled(false);
	startTimer(30);

	startTime = GetTickCount();
	
	g_Renderer.StaticConstructor();
	g_Renderer.CreateDevice(parent->winId(), parent->width(), parent->height());

	g_ModelArcBall.StaticConstructor();
	g_ModelArcBall.SetWindowSize(parent->width(), parent->height());
}

MainWidget::~MainWidget()
{
	g_Renderer.StaticDestructor();
}

void MainWidget::paintEvent(QPaintEvent *e)
{
	QPainter painter(this);

	painter.drawText(100, 100, "Hello");
}

void MainWidget::timerEvent( QTimerEvent * )
{
	// Clacualte the delta time
	DWORD t = GetTickCount();
	float deltaTime = (t - startTime) * 0.001f;

	Update(deltaTime);
	g_Renderer.Render();

	QPainter painter(this);
	painter.drawText(100, 100, "Hello");

	startTime = t;
}

void MainWidget::mousePressEvent( QMouseEvent * e )
{
	if(e->buttons() == Qt::LeftButton)
	{
		g_ModelArcBall.DragStart( e->x(), e->y() );
	}
}

void MainWidget::mouseMoveEvent( QMouseEvent *e )
{
	if(e->buttons() == Qt::LeftButton)
	{
		g_ModelArcBall.Drag( e->x(), e->y() );
	}	
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
}

//void MainWidget::convertToD3DXMATRIX(D3DXMATRIX* pOut, const Matrix4fT& MT)
//{
//	for(int i = 0, k = 0; i < 16; i = i+4, ++k)
//		for(int j = 0; j < 4; ++j)
//			pOut->m[k][j] = MT.M[i+j];
//}

void MainWidget::Update(float deltaTime)
{
	// TODO: Change into a camera class later.
	UpdateCamera();
}

void MainWidget::UpdateCamera()
{
	D3DXMATRIX world, newView, proj;
	GetCurrentWorldMatrix(&world);
	GetCurrentProjectionMatrix(&proj);

	D3DXVECTOR3 newCameraLocation;
	D3DXVec3TransformCoord( &newCameraLocation, &g_Renderer.GetCameraVec(), g_ModelArcBall.GetRotationMatrix() );
	D3DXMatrixLookAtLH( &newView, &newCameraLocation, &D3DXVECTOR3(0.f, 1.f, 0.f), &D3DXVECTOR3(0.f, 1.f, 0.f) );
	g_pEffect->SetMatrix("matW", &world);
	g_pEffect->SetMatrix("matVP", &(newView*proj));
}
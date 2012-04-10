#pragma once

#include <QWidget>
#include <QtCore>
#include <QtGui>

#include <d3dx9math.h>

class MainWidget : public QWidget
{
	Q_OBJECT

public:
	MainWidget(QWidget *parent);
	~MainWidget();

	void timerEvent(QTimerEvent *);
	void paintEvent(QPaintEvent *e);

	void mousePressEvent(QMouseEvent * e);
	void mouseMoveEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	

private:

	void Update(float deltaTime = 0.f);
	void UpdateCamera();

	//void convertToD3DXMATRIX(D3DXMATRIX* pOut, const Matrix4fT& MT);

	DWORD startTime;
	
	
};

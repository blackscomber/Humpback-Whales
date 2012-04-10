#pragma once

#include <QWidget>

class D3DWidget : public QWidget
{
	Q_OBJECT
public:
	D3DWidget(QWidget* parent = NULL, Qt::WindowFlags flags = 0);
	~D3DWidget();

	virtual void timerEvent(QTimerEvent *);
	void paintEvent(QPaintEvent *) {}
	void mousePressEvent(QMouseEvent* e);
	void mouseMoveEvent(QMouseEvent* e);
	QPaintEngine* paintEngine() const { return 0; }
};

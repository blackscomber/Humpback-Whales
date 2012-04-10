/********************************************************************************
** Form generated from reading UI file 'test.ui'
**
** Created: Tue Apr 3 16:17:09 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_H
#define UI_TEST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHeaderView>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SkeletonKeyClass
{
public:
    QWidget *centralWidget;
    QWidget *preview;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QListView *toc;

    void setupUi(QMainWindow *SkeletonKeyClass)
    {
        if (SkeletonKeyClass->objectName().isEmpty())
            SkeletonKeyClass->setObjectName(QString::fromUtf8("SkeletonKeyClass"));
        SkeletonKeyClass->resize(1280, 860);
        centralWidget = new QWidget(SkeletonKeyClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        preview = new QWidget(centralWidget);
        preview->setObjectName(QString::fromUtf8("preview"));
        preview->setGeometry(QRect(0, 0, 800, 600));
        preview->setStyleSheet(QString::fromUtf8("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(255, 255, 0, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));"));
        SkeletonKeyClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SkeletonKeyClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 21));
        SkeletonKeyClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SkeletonKeyClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SkeletonKeyClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SkeletonKeyClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SkeletonKeyClass->setStatusBar(statusBar);
        dockWidget = new QDockWidget(SkeletonKeyClass);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dockWidget->sizePolicy().hasHeightForWidth());
        dockWidget->setSizePolicy(sizePolicy);
        dockWidget->setMinimumSize(QSize(200, 38));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        toc = new QListView(dockWidgetContents);
        toc->setObjectName(QString::fromUtf8("toc"));
        toc->setGeometry(QRect(0, 0, 200, 700));
        toc->setEditTriggers(QAbstractItemView::NoEditTriggers);
        toc->setProperty("showDropIndicator", QVariant(false));
        dockWidget->setWidget(dockWidgetContents);
        SkeletonKeyClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);

        retranslateUi(SkeletonKeyClass);

        QMetaObject::connectSlotsByName(SkeletonKeyClass);
    } // setupUi

    void retranslateUi(QMainWindow *SkeletonKeyClass)
    {
        SkeletonKeyClass->setWindowTitle(QApplication::translate("SkeletonKeyClass", "SkeletonKey", 0, QApplication::UnicodeUTF8));
        dockWidget->setWindowTitle(QApplication::translate("SkeletonKeyClass", "Features", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SkeletonKeyClass: public Ui_SkeletonKeyClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_H

/********************************************************************************
** Form generated from reading UI file 'application.ui'
**
** Created: Mon Apr 9 17:38:28 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPLICATION_H
#define UI_APPLICATION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_applicationClass
{
public:
    QWidget *mainwidget;

    void setupUi(QWidget *applicationClass)
    {
        if (applicationClass->objectName().isEmpty())
            applicationClass->setObjectName(QString::fromUtf8("applicationClass"));
        applicationClass->resize(1024, 768);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(applicationClass->sizePolicy().hasHeightForWidth());
        applicationClass->setSizePolicy(sizePolicy);
        mainwidget = new QWidget(applicationClass);
        mainwidget->setObjectName(QString::fromUtf8("mainwidget"));
        mainwidget->setGeometry(QRect(19, 29, 991, 711));

        retranslateUi(applicationClass);

        QMetaObject::connectSlotsByName(applicationClass);
    } // setupUi

    void retranslateUi(QWidget *applicationClass)
    {
        applicationClass->setWindowTitle(QApplication::translate("applicationClass", "application", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mainwidget->setToolTip(QApplication::translate("applicationClass", "<html><head/><body><p>Preview of the 3D Object.</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class applicationClass: public Ui_applicationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPLICATION_H

/********************************************************************************
** Form generated from reading UI file 'taskform.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKFORM_H
#define UI_TASKFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TaskForm
{
public:
    QLabel *statusLabel;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QLabel *taskText;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *TryButton;
    QPushButton *LoseButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *YourAnswerlabel;
    QLineEdit *AnswerLineEdit;

    void setupUi(QWidget *TaskForm)
    {
        if (TaskForm->objectName().isEmpty())
            TaskForm->setObjectName("TaskForm");
        TaskForm->resize(431, 305);
        statusLabel = new QLabel(TaskForm);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setGeometry(QRect(10, 260, 211, 20));
        widget = new QWidget(TaskForm);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 0, 421, 251));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        taskText = new QLabel(widget);
        taskText->setObjectName("taskText");
        QFont font;
        font.setPointSize(18);
        taskText->setFont(font);

        gridLayout_2->addWidget(taskText, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        TryButton = new QPushButton(widget);
        TryButton->setObjectName("TryButton");

        horizontalLayout->addWidget(TryButton);

        LoseButton = new QPushButton(widget);
        LoseButton->setObjectName("LoseButton");

        horizontalLayout->addWidget(LoseButton);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        YourAnswerlabel = new QLabel(widget);
        YourAnswerlabel->setObjectName("YourAnswerlabel");

        horizontalLayout_2->addWidget(YourAnswerlabel);

        AnswerLineEdit = new QLineEdit(widget);
        AnswerLineEdit->setObjectName("AnswerLineEdit");

        horizontalLayout_2->addWidget(AnswerLineEdit);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);


        retranslateUi(TaskForm);

        QMetaObject::connectSlotsByName(TaskForm);
    } // setupUi

    void retranslateUi(QWidget *TaskForm)
    {
        TaskForm->setWindowTitle(QCoreApplication::translate("TaskForm", "Form", nullptr));
        statusLabel->setText(QString());
        taskText->setText(QCoreApplication::translate("TaskForm", "\320\242\320\265\320\272\321\201\321\202 \320\227\320\260\320\264\320\260\320\275\320\270\321\217", nullptr));
        TryButton->setText(QCoreApplication::translate("TaskForm", "\320\241\320\264\320\260\321\202\321\214", nullptr));
        LoseButton->setText(QCoreApplication::translate("TaskForm", "\320\222\321\213\320\271\321\202\320\270", nullptr));
        YourAnswerlabel->setText(QCoreApplication::translate("TaskForm", "\320\222\320\260\321\210 \320\276\321\202\320\262\320\265\321\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TaskForm: public Ui_TaskForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKFORM_H

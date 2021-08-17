/********************************************************************************
** Form generated from reading UI file 'lbm_stream_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LBM_STREAM_DIALOG_H
#define UI_LBM_STREAM_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include "widgets/display_filter_edit.h"

QT_BEGIN_NAMESPACE

class Ui_LBMStreamDialog
{
public:
    QAction *actionCopyAsCSV;
    QAction *actionCopyAsYAML;
    QVBoxLayout *verticalLayout;
    QTreeWidget *lbm_stream_TreeWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    DisplayFilterEdit *displayFilterLineEdit;
    QPushButton *applyFilterButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *LBMStreamDialog)
    {
        if (LBMStreamDialog->objectName().isEmpty())
            LBMStreamDialog->setObjectName(QStringLiteral("LBMStreamDialog"));
        LBMStreamDialog->resize(652, 459);
        actionCopyAsCSV = new QAction(LBMStreamDialog);
        actionCopyAsCSV->setObjectName(QStringLiteral("actionCopyAsCSV"));
#ifndef QT_NO_SHORTCUT
        actionCopyAsCSV->setShortcut(QStringLiteral("Ctrl+C"));
#endif // QT_NO_SHORTCUT
        actionCopyAsYAML = new QAction(LBMStreamDialog);
        actionCopyAsYAML->setObjectName(QStringLiteral("actionCopyAsYAML"));
#ifndef QT_NO_SHORTCUT
        actionCopyAsYAML->setShortcut(QStringLiteral("Ctrl+Y"));
#endif // QT_NO_SHORTCUT
        verticalLayout = new QVBoxLayout(LBMStreamDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lbm_stream_TreeWidget = new QTreeWidget(LBMStreamDialog);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setTextAlignment(3, Qt::AlignLeft|Qt::AlignVCenter);
        lbm_stream_TreeWidget->setHeaderItem(__qtreewidgetitem);
        lbm_stream_TreeWidget->setObjectName(QStringLiteral("lbm_stream_TreeWidget"));

        verticalLayout->addWidget(lbm_stream_TreeWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(LBMStreamDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        displayFilterLineEdit = new DisplayFilterEdit(LBMStreamDialog);
        displayFilterLineEdit->setObjectName(QStringLiteral("displayFilterLineEdit"));

        horizontalLayout->addWidget(displayFilterLineEdit);

        applyFilterButton = new QPushButton(LBMStreamDialog);
        applyFilterButton->setObjectName(QStringLiteral("applyFilterButton"));

        horizontalLayout->addWidget(applyFilterButton);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(LBMStreamDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Help);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(LBMStreamDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), LBMStreamDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), LBMStreamDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(LBMStreamDialog);
    } // setupUi

    void retranslateUi(QDialog *LBMStreamDialog)
    {
        LBMStreamDialog->setWindowTitle(QApplication::translate("LBMStreamDialog", "Dialog", Q_NULLPTR));
        actionCopyAsCSV->setText(QApplication::translate("LBMStreamDialog", "Copy as CSV", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionCopyAsCSV->setToolTip(QApplication::translate("LBMStreamDialog", "Copy the tree as CSV", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionCopyAsYAML->setText(QApplication::translate("LBMStreamDialog", "Copy as YAML", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionCopyAsYAML->setToolTip(QApplication::translate("LBMStreamDialog", "Copy the tree as YAML", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        QTreeWidgetItem *___qtreewidgetitem = lbm_stream_TreeWidget->headerItem();
        ___qtreewidgetitem->setText(6, QApplication::translate("LBMStreamDialog", "Last Frame", Q_NULLPTR));
        ___qtreewidgetitem->setText(5, QApplication::translate("LBMStreamDialog", "First Frame", Q_NULLPTR));
        ___qtreewidgetitem->setText(4, QApplication::translate("LBMStreamDialog", "Bytes", Q_NULLPTR));
        ___qtreewidgetitem->setText(3, QApplication::translate("LBMStreamDialog", "Messages", Q_NULLPTR));
        ___qtreewidgetitem->setText(2, QApplication::translate("LBMStreamDialog", "Endpoint B", Q_NULLPTR));
        ___qtreewidgetitem->setText(1, QApplication::translate("LBMStreamDialog", "Endpoint A", Q_NULLPTR));
        ___qtreewidgetitem->setText(0, QApplication::translate("LBMStreamDialog", "Stream", Q_NULLPTR));
        label->setText(QApplication::translate("LBMStreamDialog", "Display filter:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        applyFilterButton->setToolTip(QApplication::translate("LBMStreamDialog", "Regenerate statistics using this display filter", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        applyFilterButton->setText(QApplication::translate("LBMStreamDialog", "Apply", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LBMStreamDialog: public Ui_LBMStreamDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LBM_STREAM_DIALOG_H

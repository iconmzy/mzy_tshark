/********************************************************************************
** Form generated from reading UI file 'voip_calls_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOIP_CALLS_DIALOG_H
#define UI_VOIP_CALLS_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_VoipCallsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTreeView *callTreeView;
    QLabel *hintLabel;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QCheckBox *todCheckBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *VoipCallsDialog)
    {
        if (VoipCallsDialog->objectName().isEmpty())
            VoipCallsDialog->setObjectName(QStringLiteral("VoipCallsDialog"));
        VoipCallsDialog->resize(750, 430);
        verticalLayout = new QVBoxLayout(VoipCallsDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        callTreeView = new QTreeView(VoipCallsDialog);
        callTreeView->setObjectName(QStringLiteral("callTreeView"));
        callTreeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        callTreeView->setTextElideMode(Qt::ElideMiddle);
        callTreeView->setRootIsDecorated(false);
        callTreeView->setUniformRowHeights(true);
        callTreeView->setItemsExpandable(false);

        verticalLayout->addWidget(callTreeView);

        hintLabel = new QLabel(VoipCallsDialog);
        hintLabel->setObjectName(QStringLiteral("hintLabel"));

        verticalLayout->addWidget(hintLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        todCheckBox = new QCheckBox(VoipCallsDialog);
        todCheckBox->setObjectName(QStringLiteral("todCheckBox"));

        horizontalLayout->addWidget(todCheckBox);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(VoipCallsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Help|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(VoipCallsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), VoipCallsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), VoipCallsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(VoipCallsDialog);
    } // setupUi

    void retranslateUi(QDialog *VoipCallsDialog)
    {
        VoipCallsDialog->setWindowTitle(QApplication::translate("VoipCallsDialog", "VoIP Calls", Q_NULLPTR));
        hintLabel->setText(QApplication::translate("VoipCallsDialog", "<small></small>", Q_NULLPTR));
        todCheckBox->setText(QApplication::translate("VoipCallsDialog", "Time of Day", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class VoipCallsDialog: public Ui_VoipCallsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOIP_CALLS_DIALOG_H

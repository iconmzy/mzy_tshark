/********************************************************************************
** Form generated from reading UI file 'uat_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UAT_DIALOG_H
#define UI_UAT_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include "widgets/elided_label.h"
#include "widgets/stock_icon_tool_button.h"
#include "widgets/tabnav_tree_view.h"

QT_BEGIN_NAMESPACE

class Ui_UatDialog
{
public:
    QVBoxLayout *verticalLayout;
    TabnavTreeView *uatTreeView;
    QLabel *hintLabel;
    QHBoxLayout *horizontalLayout;
    StockIconToolButton *newToolButton;
    StockIconToolButton *deleteToolButton;
    StockIconToolButton *copyToolButton;
    StockIconToolButton *moveUpToolButton;
    StockIconToolButton *moveDownToolButton;
    StockIconToolButton *clearToolButton;
    ElidedLabel *pathLabel;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *UatDialog)
    {
        if (UatDialog->objectName().isEmpty())
            UatDialog->setObjectName(QStringLiteral("UatDialog"));
        UatDialog->resize(566, 403);
        verticalLayout = new QVBoxLayout(UatDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        uatTreeView = new TabnavTreeView(UatDialog);
        uatTreeView->setObjectName(QStringLiteral("uatTreeView"));

        verticalLayout->addWidget(uatTreeView);

        hintLabel = new QLabel(UatDialog);
        hintLabel->setObjectName(QStringLiteral("hintLabel"));
        hintLabel->setStyleSheet(QStringLiteral("QLabel { color: red; }"));
        hintLabel->setTextFormat(Qt::RichText);
        hintLabel->setWordWrap(true);

        verticalLayout->addWidget(hintLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        newToolButton = new StockIconToolButton(UatDialog);
        newToolButton->setObjectName(QStringLiteral("newToolButton"));

        horizontalLayout->addWidget(newToolButton);

        deleteToolButton = new StockIconToolButton(UatDialog);
        deleteToolButton->setObjectName(QStringLiteral("deleteToolButton"));
        deleteToolButton->setEnabled(false);

        horizontalLayout->addWidget(deleteToolButton);

        copyToolButton = new StockIconToolButton(UatDialog);
        copyToolButton->setObjectName(QStringLiteral("copyToolButton"));
        copyToolButton->setEnabled(false);

        horizontalLayout->addWidget(copyToolButton);

        moveUpToolButton = new StockIconToolButton(UatDialog);
        moveUpToolButton->setObjectName(QStringLiteral("moveUpToolButton"));
        moveUpToolButton->setEnabled(false);

        horizontalLayout->addWidget(moveUpToolButton);

        moveDownToolButton = new StockIconToolButton(UatDialog);
        moveDownToolButton->setObjectName(QStringLiteral("moveDownToolButton"));
        moveDownToolButton->setEnabled(false);

        horizontalLayout->addWidget(moveDownToolButton);

        clearToolButton = new StockIconToolButton(UatDialog);
        clearToolButton->setObjectName(QStringLiteral("clearToolButton"));
        clearToolButton->setEnabled(false);

        horizontalLayout->addWidget(clearToolButton);

        pathLabel = new ElidedLabel(UatDialog);
        pathLabel->setObjectName(QStringLiteral("pathLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pathLabel->sizePolicy().hasHeightForWidth());
        pathLabel->setSizePolicy(sizePolicy);
        pathLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pathLabel->setOpenExternalLinks(true);

        horizontalLayout->addWidget(pathLabel);

        horizontalLayout->setStretch(6, 1);

        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(UatDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Help|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(UatDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), UatDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), UatDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(UatDialog);
    } // setupUi

    void retranslateUi(QDialog *UatDialog)
    {
        hintLabel->setText(QString());
#ifndef QT_NO_TOOLTIP
        newToolButton->setToolTip(QApplication::translate("UatDialog", "Create a new entry.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        newToolButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        deleteToolButton->setToolTip(QApplication::translate("UatDialog", "Remove this entry.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        copyToolButton->setToolTip(QApplication::translate("UatDialog", "Copy this entry.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        copyToolButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        moveUpToolButton->setToolTip(QApplication::translate("UatDialog", "Move entry up.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        moveUpToolButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        moveDownToolButton->setToolTip(QApplication::translate("UatDialog", "Move entry down.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        moveDownToolButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        clearToolButton->setToolTip(QApplication::translate("UatDialog", "Clear all entries.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        clearToolButton->setText(QString());
        pathLabel->setText(QString());
        Q_UNUSED(UatDialog);
    } // retranslateUi

};

namespace Ui {
    class UatDialog: public Ui_UatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UAT_DIALOG_H

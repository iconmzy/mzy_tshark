/********************************************************************************
** Form generated from reading UI file 'decode_as_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DECODE_AS_DIALOG_H
#define UI_DECODE_AS_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "widgets/elided_label.h"
#include "widgets/stock_icon_tool_button.h"
#include "widgets/tabnav_tree_view.h"

QT_BEGIN_NAMESPACE

class Ui_DecodeAsDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    TabnavTreeView *decodeAsTreeView;
    QHBoxLayout *horizontalLayout;
    StockIconToolButton *newToolButton;
    StockIconToolButton *deleteToolButton;
    StockIconToolButton *copyToolButton;
    StockIconToolButton *clearToolButton;
    QSpacerItem *horizontalSpacer;
    ElidedLabel *pathLabel;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DecodeAsDialog)
    {
        if (DecodeAsDialog->objectName().isEmpty())
            DecodeAsDialog->setObjectName(QStringLiteral("DecodeAsDialog"));
        DecodeAsDialog->resize(750, 460);
        verticalLayout_2 = new QVBoxLayout(DecodeAsDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        decodeAsTreeView = new TabnavTreeView(DecodeAsDialog);
        decodeAsTreeView->setObjectName(QStringLiteral("decodeAsTreeView"));
        decodeAsTreeView->setIndentation(0);

        verticalLayout_2->addWidget(decodeAsTreeView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        newToolButton = new StockIconToolButton(DecodeAsDialog);
        newToolButton->setObjectName(QStringLiteral("newToolButton"));

        horizontalLayout->addWidget(newToolButton);

        deleteToolButton = new StockIconToolButton(DecodeAsDialog);
        deleteToolButton->setObjectName(QStringLiteral("deleteToolButton"));
        deleteToolButton->setEnabled(false);

        horizontalLayout->addWidget(deleteToolButton);

        copyToolButton = new StockIconToolButton(DecodeAsDialog);
        copyToolButton->setObjectName(QStringLiteral("copyToolButton"));

        horizontalLayout->addWidget(copyToolButton);

        clearToolButton = new StockIconToolButton(DecodeAsDialog);
        clearToolButton->setObjectName(QStringLiteral("clearToolButton"));
        clearToolButton->setEnabled(false);

        horizontalLayout->addWidget(clearToolButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pathLabel = new ElidedLabel(DecodeAsDialog);
        pathLabel->setObjectName(QStringLiteral("pathLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pathLabel->sizePolicy().hasHeightForWidth());
        pathLabel->setSizePolicy(sizePolicy);
        pathLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pathLabel->setOpenExternalLinks(true);

        horizontalLayout->addWidget(pathLabel);

        horizontalLayout->setStretch(5, 1);

        verticalLayout_2->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(DecodeAsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Help|QDialogButtonBox::Ok|QDialogButtonBox::Save);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(DecodeAsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), DecodeAsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DecodeAsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(DecodeAsDialog);
    } // setupUi

    void retranslateUi(QDialog *DecodeAsDialog)
    {
#ifndef QT_NO_TOOLTIP
        newToolButton->setToolTip(QApplication::translate("DecodeAsDialog", "Change the dissection behavior for a protocol.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        newToolButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        deleteToolButton->setToolTip(QApplication::translate("DecodeAsDialog", "Remove this dissection behavior.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        copyToolButton->setToolTip(QApplication::translate("DecodeAsDialog", "Copy this dissection behavior.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        copyToolButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        clearToolButton->setToolTip(QApplication::translate("DecodeAsDialog", "Clear all dissection behaviors.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pathLabel->setText(QString());
        Q_UNUSED(DecodeAsDialog);
    } // retranslateUi

};

namespace Ui {
    class DecodeAsDialog: public Ui_DecodeAsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DECODE_AS_DIALOG_H

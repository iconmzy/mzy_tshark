/********************************************************************************
** Form generated from reading UI file 'filter_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTER_DIALOG_H
#define UI_FILTER_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include "widgets/elided_label.h"
#include "widgets/stock_icon_tool_button.h"

QT_BEGIN_NAMESPACE

class Ui_FilterDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTreeView *filterTreeView;
    QHBoxLayout *horizontalLayout;
    StockIconToolButton *newToolButton;
    StockIconToolButton *deleteToolButton;
    StockIconToolButton *copyToolButton;
    QSpacerItem *horizontalSpacer;
    ElidedLabel *pathLabel;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FilterDialog)
    {
        if (FilterDialog->objectName().isEmpty())
            FilterDialog->setObjectName(QStringLiteral("FilterDialog"));
        FilterDialog->resize(584, 390);
        verticalLayout = new QVBoxLayout(FilterDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        filterTreeView = new QTreeView(FilterDialog);
        filterTreeView->setObjectName(QStringLiteral("filterTreeView"));
        filterTreeView->setDragDropMode(QAbstractItemView::DragDrop);
        filterTreeView->setSortingEnabled(true);
        filterTreeView->header()->setProperty("showSortIndicator", QVariant(true));

        verticalLayout->addWidget(filterTreeView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        newToolButton = new StockIconToolButton(FilterDialog);
        newToolButton->setObjectName(QStringLiteral("newToolButton"));

        horizontalLayout->addWidget(newToolButton);

        deleteToolButton = new StockIconToolButton(FilterDialog);
        deleteToolButton->setObjectName(QStringLiteral("deleteToolButton"));
        deleteToolButton->setEnabled(false);

        horizontalLayout->addWidget(deleteToolButton);

        copyToolButton = new StockIconToolButton(FilterDialog);
        copyToolButton->setObjectName(QStringLiteral("copyToolButton"));
        copyToolButton->setEnabled(false);

        horizontalLayout->addWidget(copyToolButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pathLabel = new ElidedLabel(FilterDialog);
        pathLabel->setObjectName(QStringLiteral("pathLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pathLabel->sizePolicy().hasHeightForWidth());
        pathLabel->setSizePolicy(sizePolicy);
        pathLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pathLabel->setOpenExternalLinks(true);

        horizontalLayout->addWidget(pathLabel);

        horizontalLayout->setStretch(4, 1);

        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(FilterDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Help|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(FilterDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), FilterDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FilterDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(FilterDialog);
    } // setupUi

    void retranslateUi(QDialog *FilterDialog)
    {
        FilterDialog->setWindowTitle(QApplication::translate("FilterDialog", "Dialog", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        newToolButton->setToolTip(QApplication::translate("FilterDialog", "Create a new filter.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        newToolButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        deleteToolButton->setToolTip(QApplication::translate("FilterDialog", "Remove this filter.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        copyToolButton->setToolTip(QApplication::translate("FilterDialog", "Copy this filter.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        copyToolButton->setText(QString());
        pathLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FilterDialog: public Ui_FilterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTER_DIALOG_H

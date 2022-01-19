/********************************************************************************
** Form generated from reading UI file 'column_preferences_frame.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLUMN_PREFERENCES_FRAME_H
#define UI_COLUMN_PREFERENCES_FRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include "widgets/stock_icon_tool_button.h"

QT_BEGIN_NAMESPACE

class Ui_ColumnPreferencesFrame
{
public:
    QVBoxLayout *verticalLayout;
    QTreeView *columnTreeView;
    QHBoxLayout *horizontalLayout;
    StockIconToolButton *newToolButton;
    StockIconToolButton *deleteToolButton;
    QCheckBox *chkShowDisplayedOnly;
    QSpacerItem *horizontalSpacer;

    void setupUi(QFrame *ColumnPreferencesFrame)
    {
        if (ColumnPreferencesFrame->objectName().isEmpty())
            ColumnPreferencesFrame->setObjectName(QStringLiteral("ColumnPreferencesFrame"));
        ColumnPreferencesFrame->resize(550, 456);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ColumnPreferencesFrame->sizePolicy().hasHeightForWidth());
        ColumnPreferencesFrame->setSizePolicy(sizePolicy);
        ColumnPreferencesFrame->setLineWidth(0);
        verticalLayout = new QVBoxLayout(ColumnPreferencesFrame);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        columnTreeView = new QTreeView(ColumnPreferencesFrame);
        columnTreeView->setObjectName(QStringLiteral("columnTreeView"));
        columnTreeView->setDragEnabled(true);
        columnTreeView->setDragDropMode(QAbstractItemView::InternalMove);
        columnTreeView->setRootIsDecorated(false);
        columnTreeView->setSortingEnabled(false);
        columnTreeView->header()->setProperty("showSortIndicator", QVariant(false));

        verticalLayout->addWidget(columnTreeView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        newToolButton = new StockIconToolButton(ColumnPreferencesFrame);
        newToolButton->setObjectName(QStringLiteral("newToolButton"));

        horizontalLayout->addWidget(newToolButton);

        deleteToolButton = new StockIconToolButton(ColumnPreferencesFrame);
        deleteToolButton->setObjectName(QStringLiteral("deleteToolButton"));

        horizontalLayout->addWidget(deleteToolButton);

        chkShowDisplayedOnly = new QCheckBox(ColumnPreferencesFrame);
        chkShowDisplayedOnly->setObjectName(QStringLiteral("chkShowDisplayedOnly"));

        horizontalLayout->addWidget(chkShowDisplayedOnly);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(ColumnPreferencesFrame);

        QMetaObject::connectSlotsByName(ColumnPreferencesFrame);
    } // setupUi

    void retranslateUi(QFrame *ColumnPreferencesFrame)
    {
        ColumnPreferencesFrame->setWindowTitle(QApplication::translate("ColumnPreferencesFrame", "Frame", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        newToolButton->setToolTip(QApplication::translate("ColumnPreferencesFrame", "Add a new column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        newToolButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        deleteToolButton->setToolTip(QApplication::translate("ColumnPreferencesFrame", "Delete selected column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        deleteToolButton->setText(QString());
        chkShowDisplayedOnly->setText(QApplication::translate("ColumnPreferencesFrame", "Show displayed columns only", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ColumnPreferencesFrame: public Ui_ColumnPreferencesFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLUMN_PREFERENCES_FRAME_H

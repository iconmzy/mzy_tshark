/********************************************************************************
** Form generated from reading UI file 'coloring_rules_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORING_RULES_DIALOG_H
#define UI_COLORING_RULES_DIALOG_H

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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "widgets/elided_label.h"
#include "widgets/stock_icon_tool_button.h"
#include "widgets/tabnav_tree_view.h"

QT_BEGIN_NAMESPACE

class Ui_ColoringRulesDialog
{
public:
    QVBoxLayout *verticalLayout;
    TabnavTreeView *coloringRulesTreeView;
    QLabel *hintLabel;
    QHBoxLayout *horizontalLayout;
    StockIconToolButton *newToolButton;
    StockIconToolButton *deleteToolButton;
    StockIconToolButton *copyToolButton;
    StockIconToolButton *clearToolButton;
    QPushButton *fGPushButton;
    QPushButton *bGPushButton;
    QPushButton *displayFilterPushButton;
    QSpacerItem *horizontalSpacer;
    ElidedLabel *pathLabel;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ColoringRulesDialog)
    {
        if (ColoringRulesDialog->objectName().isEmpty())
            ColoringRulesDialog->setObjectName(QStringLiteral("ColoringRulesDialog"));
        ColoringRulesDialog->resize(650, 480);
        verticalLayout = new QVBoxLayout(ColoringRulesDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        coloringRulesTreeView = new TabnavTreeView(ColoringRulesDialog);
        coloringRulesTreeView->setObjectName(QStringLiteral("coloringRulesTreeView"));
        coloringRulesTreeView->setDragEnabled(true);
        coloringRulesTreeView->setDragDropMode(QAbstractItemView::InternalMove);
        coloringRulesTreeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        coloringRulesTreeView->setTextElideMode(Qt::ElideMiddle);
        coloringRulesTreeView->setRootIsDecorated(false);
        coloringRulesTreeView->setUniformRowHeights(true);
        coloringRulesTreeView->setItemsExpandable(false);
        coloringRulesTreeView->setExpandsOnDoubleClick(false);
        coloringRulesTreeView->setProperty("DropIndicatorShown", QVariant(true));

        verticalLayout->addWidget(coloringRulesTreeView);

        hintLabel = new QLabel(ColoringRulesDialog);
        hintLabel->setObjectName(QStringLiteral("hintLabel"));
        hintLabel->setWordWrap(true);

        verticalLayout->addWidget(hintLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        newToolButton = new StockIconToolButton(ColoringRulesDialog);
        newToolButton->setObjectName(QStringLiteral("newToolButton"));

        horizontalLayout->addWidget(newToolButton);

        deleteToolButton = new StockIconToolButton(ColoringRulesDialog);
        deleteToolButton->setObjectName(QStringLiteral("deleteToolButton"));
        deleteToolButton->setEnabled(false);

        horizontalLayout->addWidget(deleteToolButton);

        copyToolButton = new StockIconToolButton(ColoringRulesDialog);
        copyToolButton->setObjectName(QStringLiteral("copyToolButton"));
        copyToolButton->setEnabled(false);

        horizontalLayout->addWidget(copyToolButton);

        clearToolButton = new StockIconToolButton(ColoringRulesDialog);
        clearToolButton->setObjectName(QStringLiteral("clearToolButton"));
        clearToolButton->setEnabled(false);

        horizontalLayout->addWidget(clearToolButton);

        fGPushButton = new QPushButton(ColoringRulesDialog);
        fGPushButton->setObjectName(QStringLiteral("fGPushButton"));
        fGPushButton->setVisible(false);
        fGPushButton->setStyleSheet(QStringLiteral("QPushButton { border: 1px solid palette(Dark); }"));
        fGPushButton->setAutoDefault(false);
        fGPushButton->setFlat(true);

        horizontalLayout->addWidget(fGPushButton);

        bGPushButton = new QPushButton(ColoringRulesDialog);
        bGPushButton->setObjectName(QStringLiteral("bGPushButton"));
        bGPushButton->setVisible(false);
        bGPushButton->setStyleSheet(QStringLiteral("QPushButton { border: 1px solid palette(Dark); }"));
        bGPushButton->setAutoDefault(false);
        bGPushButton->setFlat(true);

        horizontalLayout->addWidget(bGPushButton);

        displayFilterPushButton = new QPushButton(ColoringRulesDialog);
        displayFilterPushButton->setObjectName(QStringLiteral("displayFilterPushButton"));
        displayFilterPushButton->setVisible(false);
        displayFilterPushButton->setAutoDefault(false);

        horizontalLayout->addWidget(displayFilterPushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pathLabel = new ElidedLabel(ColoringRulesDialog);
        pathLabel->setObjectName(QStringLiteral("pathLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pathLabel->sizePolicy().hasHeightForWidth());
        pathLabel->setSizePolicy(sizePolicy);
        pathLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pathLabel->setOpenExternalLinks(true);

        horizontalLayout->addWidget(pathLabel);

        horizontalLayout->setStretch(8, 1);

        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(ColoringRulesDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Help|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ColoringRulesDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ColoringRulesDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ColoringRulesDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ColoringRulesDialog);
    } // setupUi

    void retranslateUi(QDialog *ColoringRulesDialog)
    {
        ColoringRulesDialog->setWindowTitle(QApplication::translate("ColoringRulesDialog", "Dialog", Q_NULLPTR));
        hintLabel->setText(QApplication::translate("ColoringRulesDialog", "<small><i>A hint.</i></small>", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        newToolButton->setToolTip(QApplication::translate("ColoringRulesDialog", "Add a new coloring rule.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        newToolButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        deleteToolButton->setToolTip(QApplication::translate("ColoringRulesDialog", "Delete this coloring rule.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        deleteToolButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        copyToolButton->setToolTip(QApplication::translate("ColoringRulesDialog", "Duplicate this coloring rule.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        clearToolButton->setToolTip(QApplication::translate("ColoringRulesDialog", "Clear all coloring rules.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        fGPushButton->setToolTip(QApplication::translate("ColoringRulesDialog", "Set the foreground color for this rule.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        fGPushButton->setText(QApplication::translate("ColoringRulesDialog", "Foreground", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        bGPushButton->setToolTip(QApplication::translate("ColoringRulesDialog", "Set the background color for this rule.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        bGPushButton->setText(QApplication::translate("ColoringRulesDialog", "Background", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        displayFilterPushButton->setToolTip(QApplication::translate("ColoringRulesDialog", "Set the display filter using this rule.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        displayFilterPushButton->setText(QApplication::translate("ColoringRulesDialog", "Apply as filter", Q_NULLPTR));
        pathLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ColoringRulesDialog: public Ui_ColoringRulesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORING_RULES_DIALOG_H

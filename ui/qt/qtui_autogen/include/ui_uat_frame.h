/********************************************************************************
** Form generated from reading UI file 'uat_frame.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UAT_FRAME_H
#define UI_UAT_FRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include "widgets/copy_from_profile_button.h"
#include "widgets/elided_label.h"
#include "widgets/stock_icon_tool_button.h"
#include "widgets/tabnav_tree_view.h"

QT_BEGIN_NAMESPACE

class Ui_UatFrame
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
    CopyFromProfileButton *copyFromProfileButton;
    ElidedLabel *pathLabel;

    void setupUi(QFrame *UatFrame)
    {
        if (UatFrame->objectName().isEmpty())
            UatFrame->setObjectName(QStringLiteral("UatFrame"));
        UatFrame->resize(513, 397);
        UatFrame->setLineWidth(0);
        verticalLayout = new QVBoxLayout(UatFrame);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        uatTreeView = new TabnavTreeView(UatFrame);
        uatTreeView->setObjectName(QStringLiteral("uatTreeView"));

        verticalLayout->addWidget(uatTreeView);

        hintLabel = new QLabel(UatFrame);
        hintLabel->setObjectName(QStringLiteral("hintLabel"));
        hintLabel->setStyleSheet(QStringLiteral("QLabel { color: red; }"));
        hintLabel->setTextFormat(Qt::RichText);
        hintLabel->setWordWrap(true);

        verticalLayout->addWidget(hintLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        newToolButton = new StockIconToolButton(UatFrame);
        newToolButton->setObjectName(QStringLiteral("newToolButton"));

        horizontalLayout->addWidget(newToolButton);

        deleteToolButton = new StockIconToolButton(UatFrame);
        deleteToolButton->setObjectName(QStringLiteral("deleteToolButton"));
        deleteToolButton->setEnabled(false);

        horizontalLayout->addWidget(deleteToolButton);

        copyToolButton = new StockIconToolButton(UatFrame);
        copyToolButton->setObjectName(QStringLiteral("copyToolButton"));
        copyToolButton->setEnabled(false);

        horizontalLayout->addWidget(copyToolButton);

        moveUpToolButton = new StockIconToolButton(UatFrame);
        moveUpToolButton->setObjectName(QStringLiteral("moveUpToolButton"));

        horizontalLayout->addWidget(moveUpToolButton);

        moveDownToolButton = new StockIconToolButton(UatFrame);
        moveDownToolButton->setObjectName(QStringLiteral("moveDownToolButton"));

        horizontalLayout->addWidget(moveDownToolButton);

        clearToolButton = new StockIconToolButton(UatFrame);
        clearToolButton->setObjectName(QStringLiteral("clearToolButton"));

        horizontalLayout->addWidget(clearToolButton);

        copyFromProfileButton = new CopyFromProfileButton(UatFrame);
        copyFromProfileButton->setObjectName(QStringLiteral("copyFromProfileButton"));

        horizontalLayout->addWidget(copyFromProfileButton);

        pathLabel = new ElidedLabel(UatFrame);
        pathLabel->setObjectName(QStringLiteral("pathLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pathLabel->sizePolicy().hasHeightForWidth());
        pathLabel->setSizePolicy(sizePolicy);
        pathLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pathLabel->setOpenExternalLinks(true);

        horizontalLayout->addWidget(pathLabel);

        horizontalLayout->setStretch(7, 1);

        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(UatFrame);

        QMetaObject::connectSlotsByName(UatFrame);
    } // setupUi

    void retranslateUi(QFrame *UatFrame)
    {
        UatFrame->setWindowTitle(QApplication::translate("UatFrame", "Frame", Q_NULLPTR));
        hintLabel->setText(QString());
#ifndef QT_NO_TOOLTIP
        newToolButton->setToolTip(QApplication::translate("UatFrame", "Create a new entry.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        newToolButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        deleteToolButton->setToolTip(QApplication::translate("UatFrame", "Remove this entry.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        copyToolButton->setToolTip(QApplication::translate("UatFrame", "Copy this entry.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        copyToolButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        moveUpToolButton->setToolTip(QApplication::translate("UatFrame", "Move entry up.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        moveUpToolButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        moveDownToolButton->setToolTip(QApplication::translate("UatFrame", "Move entry down.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        moveDownToolButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        clearToolButton->setToolTip(QApplication::translate("UatFrame", "Clear all entries.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        clearToolButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        copyFromProfileButton->setToolTip(QApplication::translate("UatFrame", "Copy entries from another profile.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        copyFromProfileButton->setText(QApplication::translate("UatFrame", "Copy from", Q_NULLPTR));
        pathLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UatFrame: public Ui_UatFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UAT_FRAME_H

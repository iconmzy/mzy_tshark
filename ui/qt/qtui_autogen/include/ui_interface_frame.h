/********************************************************************************
** Form generated from reading UI file 'interface_frame.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACE_FRAME_H
#define UI_INTERFACE_FRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_InterfaceFrame
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *warningLabel;
    QTreeView *interfaceTree;

    void setupUi(QFrame *InterfaceFrame)
    {
        if (InterfaceFrame->objectName().isEmpty())
            InterfaceFrame->setObjectName(QStringLiteral("InterfaceFrame"));
        InterfaceFrame->resize(256, 209);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(InterfaceFrame->sizePolicy().hasHeightForWidth());
        InterfaceFrame->setSizePolicy(sizePolicy);
        InterfaceFrame->setLineWidth(0);
        verticalLayout = new QVBoxLayout(InterfaceFrame);
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        warningLabel = new QLabel(InterfaceFrame);
        warningLabel->setObjectName(QStringLiteral("warningLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(warningLabel->sizePolicy().hasHeightForWidth());
        warningLabel->setSizePolicy(sizePolicy1);
        warningLabel->setTextFormat(Qt::RichText);
        warningLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        warningLabel->setWordWrap(true);
        warningLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);

        verticalLayout->addWidget(warningLabel);

        interfaceTree = new QTreeView(InterfaceFrame);
        interfaceTree->setObjectName(QStringLiteral("interfaceTree"));
        interfaceTree->setSelectionMode(QAbstractItemView::ExtendedSelection);
        interfaceTree->setRootIsDecorated(false);
        interfaceTree->setHeaderHidden(true);

        verticalLayout->addWidget(interfaceTree);


        retranslateUi(InterfaceFrame);

        QMetaObject::connectSlotsByName(InterfaceFrame);
    } // setupUi

    void retranslateUi(QFrame *InterfaceFrame)
    {
        InterfaceFrame->setWindowTitle(QApplication::translate("InterfaceFrame", "Frame", Q_NULLPTR));
        warningLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class InterfaceFrame: public Ui_InterfaceFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE_FRAME_H

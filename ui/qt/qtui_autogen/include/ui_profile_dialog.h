/********************************************************************************
** Form generated from reading UI file 'profile_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILE_DIALOG_H
#define UI_PROFILE_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "widgets/elided_label.h"
#include "widgets/profile_tree_view.h"
#include "widgets/stock_icon_tool_button.h"

QT_BEGIN_NAMESPACE

class Ui_ProfileDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineProfileFilter;
    QComboBox *cmbProfileTypes;
    ProfileTreeView *profileTreeView;
    QHBoxLayout *horizontalLayout;
    StockIconToolButton *newToolButton;
    StockIconToolButton *deleteToolButton;
    StockIconToolButton *copyToolButton;
    QSpacerItem *horizontalSpacer;
    ElidedLabel *hintLabel;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ProfileDialog)
    {
        if (ProfileDialog->objectName().isEmpty())
            ProfileDialog->setObjectName(QStringLiteral("ProfileDialog"));
        ProfileDialog->resize(570, 400);
        verticalLayout = new QVBoxLayout(ProfileDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lineProfileFilter = new QLineEdit(ProfileDialog);
        lineProfileFilter->setObjectName(QStringLiteral("lineProfileFilter"));

        horizontalLayout_2->addWidget(lineProfileFilter);

        cmbProfileTypes = new QComboBox(ProfileDialog);
        cmbProfileTypes->setObjectName(QStringLiteral("cmbProfileTypes"));

        horizontalLayout_2->addWidget(cmbProfileTypes);


        verticalLayout->addLayout(horizontalLayout_2);

        profileTreeView = new ProfileTreeView(ProfileDialog);
        profileTreeView->setObjectName(QStringLiteral("profileTreeView"));
        profileTreeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        profileTreeView->setRootIsDecorated(false);
        profileTreeView->setUniformRowHeights(true);
        profileTreeView->setItemsExpandable(false);
        profileTreeView->setSortingEnabled(false);
        profileTreeView->setHeaderHidden(false);
        profileTreeView->setExpandsOnDoubleClick(false);
        profileTreeView->header()->setVisible(true);

        verticalLayout->addWidget(profileTreeView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        newToolButton = new StockIconToolButton(ProfileDialog);
        newToolButton->setObjectName(QStringLiteral("newToolButton"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/stock/plus-8.png"), QSize(), QIcon::Normal, QIcon::Off);
        newToolButton->setIcon(icon);

        horizontalLayout->addWidget(newToolButton);

        deleteToolButton = new StockIconToolButton(ProfileDialog);
        deleteToolButton->setObjectName(QStringLiteral("deleteToolButton"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/stock/minus-8.png"), QSize(), QIcon::Normal, QIcon::Off);
        deleteToolButton->setIcon(icon1);

        horizontalLayout->addWidget(deleteToolButton);

        copyToolButton = new StockIconToolButton(ProfileDialog);
        copyToolButton->setObjectName(QStringLiteral("copyToolButton"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/stock/copy-8.png"), QSize(), QIcon::Normal, QIcon::Off);
        copyToolButton->setIcon(icon2);

        horizontalLayout->addWidget(copyToolButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        hintLabel = new ElidedLabel(ProfileDialog);
        hintLabel->setObjectName(QStringLiteral("hintLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(hintLabel->sizePolicy().hasHeightForWidth());
        hintLabel->setSizePolicy(sizePolicy);
        hintLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        hintLabel->setOpenExternalLinks(true);

        horizontalLayout->addWidget(hintLabel);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(ProfileDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Help|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ProfileDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ProfileDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ProfileDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ProfileDialog);
    } // setupUi

    void retranslateUi(QDialog *ProfileDialog)
    {
        lineProfileFilter->setPlaceholderText(QApplication::translate("ProfileDialog", "Search for profile \342\200\246", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        newToolButton->setToolTip(QApplication::translate("ProfileDialog", "Create a new profile using default settings.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        newToolButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        deleteToolButton->setToolTip(QApplication::translate("ProfileDialog", "<html><head/><body><p>Remove this profile. System provided profiles cannot be removed. The default profile will be reset upon deletion.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        copyToolButton->setToolTip(QApplication::translate("ProfileDialog", "Copy this profile.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        copyToolButton->setText(QString());
        hintLabel->setText(QString());
        Q_UNUSED(ProfileDialog);
    } // retranslateUi

};

namespace Ui {
    class ProfileDialog: public Ui_ProfileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILE_DIALOG_H

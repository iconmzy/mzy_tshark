/********************************************************************************
** Form generated from reading UI file 'enabled_protocols_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENABLED_PROTOCOLS_DIALOG_H
#define UI_ENABLED_PROTOCOLS_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_EnabledProtocolsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *search_line_edit_;
    QComboBox *cmbSearchType;
    QLabel *label_2;
    QComboBox *cmbProtocolType;
    QTreeView *protocol_tree_;
    QLabel *disable_notice_text_;
    QHBoxLayout *horizontalLayout;
    QPushButton *enable_all_button_;
    QPushButton *disable_all_button_;
    QPushButton *invert_button_;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *EnabledProtocolsDialog)
    {
        if (EnabledProtocolsDialog->objectName().isEmpty())
            EnabledProtocolsDialog->setObjectName(QStringLiteral("EnabledProtocolsDialog"));
        EnabledProtocolsDialog->resize(987, 595);
        verticalLayout = new QVBoxLayout(EnabledProtocolsDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(EnabledProtocolsDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        search_line_edit_ = new QLineEdit(EnabledProtocolsDialog);
        search_line_edit_->setObjectName(QStringLiteral("search_line_edit_"));

        horizontalLayout_2->addWidget(search_line_edit_);

        cmbSearchType = new QComboBox(EnabledProtocolsDialog);
        cmbSearchType->setObjectName(QStringLiteral("cmbSearchType"));

        horizontalLayout_2->addWidget(cmbSearchType);

        label_2 = new QLabel(EnabledProtocolsDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        cmbProtocolType = new QComboBox(EnabledProtocolsDialog);
        cmbProtocolType->setObjectName(QStringLiteral("cmbProtocolType"));

        horizontalLayout_2->addWidget(cmbProtocolType);


        verticalLayout->addLayout(horizontalLayout_2);

        protocol_tree_ = new QTreeView(EnabledProtocolsDialog);
        protocol_tree_->setObjectName(QStringLiteral("protocol_tree_"));
        protocol_tree_->setSortingEnabled(true);

        verticalLayout->addWidget(protocol_tree_);

        disable_notice_text_ = new QLabel(EnabledProtocolsDialog);
        disable_notice_text_->setObjectName(QStringLiteral("disable_notice_text_"));
        disable_notice_text_->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(disable_notice_text_);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        enable_all_button_ = new QPushButton(EnabledProtocolsDialog);
        enable_all_button_->setObjectName(QStringLiteral("enable_all_button_"));

        horizontalLayout->addWidget(enable_all_button_);

        disable_all_button_ = new QPushButton(EnabledProtocolsDialog);
        disable_all_button_->setObjectName(QStringLiteral("disable_all_button_"));

        horizontalLayout->addWidget(disable_all_button_);

        invert_button_ = new QPushButton(EnabledProtocolsDialog);
        invert_button_->setObjectName(QStringLiteral("invert_button_"));

        horizontalLayout->addWidget(invert_button_);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(EnabledProtocolsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Help|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(EnabledProtocolsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), EnabledProtocolsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), EnabledProtocolsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(EnabledProtocolsDialog);
    } // setupUi

    void retranslateUi(QDialog *EnabledProtocolsDialog)
    {
        EnabledProtocolsDialog->setWindowTitle(QApplication::translate("EnabledProtocolsDialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("EnabledProtocolsDialog", "Search:", Q_NULLPTR));
        label_2->setText(QApplication::translate("EnabledProtocolsDialog", "in", Q_NULLPTR));
        disable_notice_text_->setText(QApplication::translate("EnabledProtocolsDialog", "<small><i>Disabling a protocol prevents higher layer protocols from being displayed</i></small>", Q_NULLPTR));
        enable_all_button_->setText(QApplication::translate("EnabledProtocolsDialog", "Enable All", Q_NULLPTR));
        disable_all_button_->setText(QApplication::translate("EnabledProtocolsDialog", "Disable All", Q_NULLPTR));
        invert_button_->setText(QApplication::translate("EnabledProtocolsDialog", "Invert", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class EnabledProtocolsDialog: public Ui_EnabledProtocolsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENABLED_PROTOCOLS_DIALOG_H

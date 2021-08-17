/********************************************************************************
** Form generated from reading UI file 'resolved_addresses_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESOLVED_ADDRESSES_DIALOG_H
#define UI_RESOLVED_ADDRESSES_DIALOG_H

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
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ResolvedAddressesDialog
{
public:
    QAction *actionComment;
    QAction *actionIPv4HashTable;
    QAction *actionIPv6HashTable;
    QAction *actionShowAll;
    QAction *actionHideAll;
    QAction *actionAddressesHosts;
    QAction *actionPortNames;
    QAction *actionEthernetAddresses;
    QAction *actionEthernetWKA;
    QAction *actionEthernetManufacturers;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *txtSearchFilter;
    QComboBox *cmbDataType;
    QTableView *tblAddresses;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *txtPortFilter;
    QComboBox *cmbPortFilterType;
    QTableView *tblPorts;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_4;
    QPlainTextEdit *plainTextEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ResolvedAddressesDialog)
    {
        if (ResolvedAddressesDialog->objectName().isEmpty())
            ResolvedAddressesDialog->setObjectName(QStringLiteral("ResolvedAddressesDialog"));
        ResolvedAddressesDialog->resize(620, 450);
        actionComment = new QAction(ResolvedAddressesDialog);
        actionComment->setObjectName(QStringLiteral("actionComment"));
        actionComment->setCheckable(true);
        actionComment->setChecked(true);
        actionIPv4HashTable = new QAction(ResolvedAddressesDialog);
        actionIPv4HashTable->setObjectName(QStringLiteral("actionIPv4HashTable"));
        actionIPv4HashTable->setCheckable(true);
        actionIPv6HashTable = new QAction(ResolvedAddressesDialog);
        actionIPv6HashTable->setObjectName(QStringLiteral("actionIPv6HashTable"));
        actionIPv6HashTable->setCheckable(true);
        actionShowAll = new QAction(ResolvedAddressesDialog);
        actionShowAll->setObjectName(QStringLiteral("actionShowAll"));
        actionHideAll = new QAction(ResolvedAddressesDialog);
        actionHideAll->setObjectName(QStringLiteral("actionHideAll"));
        actionAddressesHosts = new QAction(ResolvedAddressesDialog);
        actionAddressesHosts->setObjectName(QStringLiteral("actionAddressesHosts"));
        actionAddressesHosts->setCheckable(true);
        actionAddressesHosts->setChecked(true);
        actionPortNames = new QAction(ResolvedAddressesDialog);
        actionPortNames->setObjectName(QStringLiteral("actionPortNames"));
        actionPortNames->setCheckable(true);
        actionPortNames->setChecked(true);
        actionEthernetAddresses = new QAction(ResolvedAddressesDialog);
        actionEthernetAddresses->setObjectName(QStringLiteral("actionEthernetAddresses"));
        actionEthernetAddresses->setCheckable(true);
        actionEthernetAddresses->setChecked(true);
        actionEthernetWKA = new QAction(ResolvedAddressesDialog);
        actionEthernetWKA->setObjectName(QStringLiteral("actionEthernetWKA"));
        actionEthernetWKA->setCheckable(true);
        actionEthernetWKA->setChecked(true);
        actionEthernetManufacturers = new QAction(ResolvedAddressesDialog);
        actionEthernetManufacturers->setObjectName(QStringLiteral("actionEthernetManufacturers"));
        actionEthernetManufacturers->setCheckable(true);
        actionEthernetManufacturers->setChecked(true);
        verticalLayout_2 = new QVBoxLayout(ResolvedAddressesDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tabWidget = new QTabWidget(ResolvedAddressesDialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        txtSearchFilter = new QLineEdit(tab);
        txtSearchFilter->setObjectName(QStringLiteral("txtSearchFilter"));

        horizontalLayout->addWidget(txtSearchFilter);

        cmbDataType = new QComboBox(tab);
        cmbDataType->setObjectName(QStringLiteral("cmbDataType"));

        horizontalLayout->addWidget(cmbDataType);


        verticalLayout->addLayout(horizontalLayout);

        tblAddresses = new QTableView(tab);
        tblAddresses->setObjectName(QStringLiteral("tblAddresses"));
        tblAddresses->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tblAddresses->setAlternatingRowColors(true);
        tblAddresses->setSortingEnabled(true);
        tblAddresses->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tblAddresses->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(tblAddresses);

        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        verticalLayout_3 = new QVBoxLayout(tab_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        txtPortFilter = new QLineEdit(tab_3);
        txtPortFilter->setObjectName(QStringLiteral("txtPortFilter"));

        horizontalLayout_2->addWidget(txtPortFilter);

        cmbPortFilterType = new QComboBox(tab_3);
        cmbPortFilterType->setObjectName(QStringLiteral("cmbPortFilterType"));

        horizontalLayout_2->addWidget(cmbPortFilterType);


        verticalLayout_3->addLayout(horizontalLayout_2);

        tblPorts = new QTableView(tab_3);
        tblPorts->setObjectName(QStringLiteral("tblPorts"));
        tblPorts->setSortingEnabled(true);
        tblPorts->verticalHeader()->setVisible(false);

        verticalLayout_3->addWidget(tblPorts);

        tabWidget->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_4 = new QVBoxLayout(tab_2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        plainTextEdit = new QPlainTextEdit(tab_2);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        verticalLayout_4->addWidget(plainTextEdit);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_2->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(ResolvedAddressesDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(ResolvedAddressesDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ResolvedAddressesDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ResolvedAddressesDialog, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ResolvedAddressesDialog);
    } // setupUi

    void retranslateUi(QDialog *ResolvedAddressesDialog)
    {
        ResolvedAddressesDialog->setWindowTitle(QApplication::translate("ResolvedAddressesDialog", "Dialog", Q_NULLPTR));
        actionComment->setText(QApplication::translate("ResolvedAddressesDialog", "Comment", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionComment->setToolTip(QApplication::translate("ResolvedAddressesDialog", "Show the comment.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionIPv4HashTable->setText(QApplication::translate("ResolvedAddressesDialog", "IPv4 Hash Table", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionIPv4HashTable->setToolTip(QApplication::translate("ResolvedAddressesDialog", "Show the IPv4 hash table entries.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionIPv6HashTable->setText(QApplication::translate("ResolvedAddressesDialog", "IPv6 Hash Table", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionIPv6HashTable->setToolTip(QApplication::translate("ResolvedAddressesDialog", "Show the IPv6 hash table entries.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionShowAll->setText(QApplication::translate("ResolvedAddressesDialog", "Show All", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionShowAll->setToolTip(QApplication::translate("ResolvedAddressesDialog", "Show all address types.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionHideAll->setText(QApplication::translate("ResolvedAddressesDialog", "Hide All", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionHideAll->setToolTip(QApplication::translate("ResolvedAddressesDialog", "Hide all address types.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionAddressesHosts->setText(QApplication::translate("ResolvedAddressesDialog", "IPv4 and IPv6 Addresses (hosts)", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionAddressesHosts->setToolTip(QApplication::translate("ResolvedAddressesDialog", "Show resolved IPv4 and IPv6 host names in \"hosts\" format.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionPortNames->setText(QApplication::translate("ResolvedAddressesDialog", "Port names (services)", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionPortNames->setToolTip(QApplication::translate("ResolvedAddressesDialog", "Show resolved port names in \"services\" format.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionEthernetAddresses->setText(QApplication::translate("ResolvedAddressesDialog", "Ethernet Addresses", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionEthernetAddresses->setToolTip(QApplication::translate("ResolvedAddressesDialog", "Show resolved Ethernet addresses in \"ethers\" format.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionEthernetWKA->setText(QApplication::translate("ResolvedAddressesDialog", "Ethernet Well-Known Addresses", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionEthernetWKA->setToolTip(QApplication::translate("ResolvedAddressesDialog", "Show well-known Ethernet addresses in \"ethers\" format.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionEthernetManufacturers->setText(QApplication::translate("ResolvedAddressesDialog", "Ethernet Manufacturers", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionEthernetManufacturers->setToolTip(QApplication::translate("ResolvedAddressesDialog", "Show Ethernet manufacturers in \"ethers\" format.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        txtSearchFilter->setPlaceholderText(QApplication::translate("ResolvedAddressesDialog", "Search for entry (min 3 characters)", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("ResolvedAddressesDialog", "Hosts", Q_NULLPTR));
        txtPortFilter->setPlaceholderText(QApplication::translate("ResolvedAddressesDialog", "Search for port or name", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("ResolvedAddressesDialog", "Ports", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("ResolvedAddressesDialog", "Capture File Comments", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ResolvedAddressesDialog: public Ui_ResolvedAddressesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESOLVED_ADDRESSES_DIALOG_H

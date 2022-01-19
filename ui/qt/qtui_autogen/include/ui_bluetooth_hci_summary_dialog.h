/********************************************************************************
** Form generated from reading UI file 'bluetooth_hci_summary_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLUETOOTH_HCI_SUMMARY_DIALOG_H
#define UI_BLUETOOTH_HCI_SUMMARY_DIALOG_H

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
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include "widgets/display_filter_edit.h"

QT_BEGIN_NAMESPACE

class Ui_BluetoothHciSummaryDialog
{
public:
    QAction *actionCopy_Cell;
    QAction *actionCopy_Rows;
    QAction *actionCopy_All;
    QAction *actionSave_as_image;
    QAction *actionMark_Unmark_Row;
    QAction *actionMark_Unmark_Cell;
    QVBoxLayout *verticalLayout;
    QTreeWidget *tableTreeWidget;
    QHBoxLayout *resultsFilterHorizontalLayout;
    QLabel *resultsFilterLabel;
    QLineEdit *resultsFilterLineEdit;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    DisplayFilterEdit *displayFilterLineEdit;
    QComboBox *interfaceComboBox;
    QComboBox *adapterComboBox;
    QLabel *hintLabel;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *BluetoothHciSummaryDialog)
    {
        if (BluetoothHciSummaryDialog->objectName().isEmpty())
            BluetoothHciSummaryDialog->setObjectName(QStringLiteral("BluetoothHciSummaryDialog"));
        BluetoothHciSummaryDialog->resize(880, 477);
        BluetoothHciSummaryDialog->setBaseSize(QSize(0, 0));
        actionCopy_Cell = new QAction(BluetoothHciSummaryDialog);
        actionCopy_Cell->setObjectName(QStringLiteral("actionCopy_Cell"));
        actionCopy_Rows = new QAction(BluetoothHciSummaryDialog);
        actionCopy_Rows->setObjectName(QStringLiteral("actionCopy_Rows"));
        actionCopy_All = new QAction(BluetoothHciSummaryDialog);
        actionCopy_All->setObjectName(QStringLiteral("actionCopy_All"));
        actionSave_as_image = new QAction(BluetoothHciSummaryDialog);
        actionSave_as_image->setObjectName(QStringLiteral("actionSave_as_image"));
        actionMark_Unmark_Row = new QAction(BluetoothHciSummaryDialog);
        actionMark_Unmark_Row->setObjectName(QStringLiteral("actionMark_Unmark_Row"));
        actionMark_Unmark_Cell = new QAction(BluetoothHciSummaryDialog);
        actionMark_Unmark_Cell->setObjectName(QStringLiteral("actionMark_Unmark_Cell"));
        verticalLayout = new QVBoxLayout(BluetoothHciSummaryDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableTreeWidget = new QTreeWidget(BluetoothHciSummaryDialog);
        new QTreeWidgetItem(tableTreeWidget);
        new QTreeWidgetItem(tableTreeWidget);
        new QTreeWidgetItem(tableTreeWidget);
        new QTreeWidgetItem(tableTreeWidget);
        new QTreeWidgetItem(tableTreeWidget);
        new QTreeWidgetItem(tableTreeWidget);
        new QTreeWidgetItem(tableTreeWidget);
        new QTreeWidgetItem(tableTreeWidget);
        new QTreeWidgetItem(tableTreeWidget);
        new QTreeWidgetItem(tableTreeWidget);
        new QTreeWidgetItem(tableTreeWidget);
        new QTreeWidgetItem(tableTreeWidget);
        new QTreeWidgetItem(tableTreeWidget);
        new QTreeWidgetItem(tableTreeWidget);
        tableTreeWidget->setObjectName(QStringLiteral("tableTreeWidget"));
        tableTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        tableTreeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableTreeWidget->setProperty("showDropIndicator", QVariant(false));
        tableTreeWidget->setAlternatingRowColors(true);
        tableTreeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableTreeWidget->setTextElideMode(Qt::ElideMiddle);
        tableTreeWidget->setIndentation(30);
        tableTreeWidget->setRootIsDecorated(true);
        tableTreeWidget->setUniformRowHeights(false);
        tableTreeWidget->setItemsExpandable(true);
        tableTreeWidget->setSortingEnabled(false);
        tableTreeWidget->setAnimated(false);
        tableTreeWidget->setAllColumnsShowFocus(false);
        tableTreeWidget->setHeaderHidden(false);
        tableTreeWidget->header()->setCascadingSectionResizes(false);
        tableTreeWidget->header()->setDefaultSectionSize(100);
        tableTreeWidget->header()->setHighlightSections(false);
        tableTreeWidget->header()->setMinimumSectionSize(100);
        tableTreeWidget->header()->setProperty("showSortIndicator", QVariant(false));
        tableTreeWidget->header()->setStretchLastSection(true);

        verticalLayout->addWidget(tableTreeWidget);

        resultsFilterHorizontalLayout = new QHBoxLayout();
        resultsFilterHorizontalLayout->setObjectName(QStringLiteral("resultsFilterHorizontalLayout"));
        resultsFilterHorizontalLayout->setContentsMargins(-1, 0, -1, -1);
        resultsFilterLabel = new QLabel(BluetoothHciSummaryDialog);
        resultsFilterLabel->setObjectName(QStringLiteral("resultsFilterLabel"));

        resultsFilterHorizontalLayout->addWidget(resultsFilterLabel);

        resultsFilterLineEdit = new QLineEdit(BluetoothHciSummaryDialog);
        resultsFilterLineEdit->setObjectName(QStringLiteral("resultsFilterLineEdit"));

        resultsFilterHorizontalLayout->addWidget(resultsFilterLineEdit);


        verticalLayout->addLayout(resultsFilterHorizontalLayout);

        horizontalLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        horizontalLayout->setSpacing(-1);
#endif
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(-1, -1, -1, 0);
        label = new QLabel(BluetoothHciSummaryDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        displayFilterLineEdit = new DisplayFilterEdit(BluetoothHciSummaryDialog);
        displayFilterLineEdit->setObjectName(QStringLiteral("displayFilterLineEdit"));

        horizontalLayout->addWidget(displayFilterLineEdit);

        interfaceComboBox = new QComboBox(BluetoothHciSummaryDialog);
        interfaceComboBox->setObjectName(QStringLiteral("interfaceComboBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(interfaceComboBox->sizePolicy().hasHeightForWidth());
        interfaceComboBox->setSizePolicy(sizePolicy);
        interfaceComboBox->setMinimumSize(QSize(350, 0));

        horizontalLayout->addWidget(interfaceComboBox);

        adapterComboBox = new QComboBox(BluetoothHciSummaryDialog);
        adapterComboBox->setObjectName(QStringLiteral("adapterComboBox"));
        adapterComboBox->setMinimumSize(QSize(320, 0));

        horizontalLayout->addWidget(adapterComboBox);


        verticalLayout->addLayout(horizontalLayout);

        hintLabel = new QLabel(BluetoothHciSummaryDialog);
        hintLabel->setObjectName(QStringLiteral("hintLabel"));

        verticalLayout->addWidget(hintLabel);

        buttonBox = new QDialogButtonBox(BluetoothHciSummaryDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(BluetoothHciSummaryDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), BluetoothHciSummaryDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), BluetoothHciSummaryDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(BluetoothHciSummaryDialog);
    } // setupUi

    void retranslateUi(QDialog *BluetoothHciSummaryDialog)
    {
        BluetoothHciSummaryDialog->setWindowTitle(QApplication::translate("BluetoothHciSummaryDialog", "Bluetooth HCI Summary", Q_NULLPTR));
        actionCopy_Cell->setText(QApplication::translate("BluetoothHciSummaryDialog", "Copy Cell", Q_NULLPTR));
        actionCopy_Rows->setText(QApplication::translate("BluetoothHciSummaryDialog", "Copy Rows", Q_NULLPTR));
        actionCopy_All->setText(QApplication::translate("BluetoothHciSummaryDialog", "Copy All", Q_NULLPTR));
        actionSave_as_image->setText(QApplication::translate("BluetoothHciSummaryDialog", "Save as image", Q_NULLPTR));
        actionMark_Unmark_Row->setText(QApplication::translate("BluetoothHciSummaryDialog", "Mark/Unmark Row", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMark_Unmark_Row->setToolTip(QApplication::translate("BluetoothHciSummaryDialog", "Mark/Unmark Row", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMark_Unmark_Row->setShortcut(QApplication::translate("BluetoothHciSummaryDialog", "Ctrl+M", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMark_Unmark_Cell->setText(QApplication::translate("BluetoothHciSummaryDialog", "Mark/Unmark Cell", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = tableTreeWidget->headerItem();
        ___qtreewidgetitem->setText(9, QApplication::translate("BluetoothHciSummaryDialog", "Occurrence", Q_NULLPTR));
        ___qtreewidgetitem->setText(8, QApplication::translate("BluetoothHciSummaryDialog", "Hardware Error", Q_NULLPTR));
        ___qtreewidgetitem->setText(7, QApplication::translate("BluetoothHciSummaryDialog", "Reason", Q_NULLPTR));
        ___qtreewidgetitem->setText(6, QApplication::translate("BluetoothHciSummaryDialog", "Status", Q_NULLPTR));
        ___qtreewidgetitem->setText(5, QApplication::translate("BluetoothHciSummaryDialog", "Subevent", Q_NULLPTR));
        ___qtreewidgetitem->setText(4, QApplication::translate("BluetoothHciSummaryDialog", "Event", Q_NULLPTR));
        ___qtreewidgetitem->setText(3, QApplication::translate("BluetoothHciSummaryDialog", "Opcode", Q_NULLPTR));
        ___qtreewidgetitem->setText(2, QApplication::translate("BluetoothHciSummaryDialog", "OCF", Q_NULLPTR));
        ___qtreewidgetitem->setText(1, QApplication::translate("BluetoothHciSummaryDialog", "OGF", Q_NULLPTR));
        ___qtreewidgetitem->setText(0, QApplication::translate("BluetoothHciSummaryDialog", "Name", Q_NULLPTR));

        const bool __sortingEnabled = tableTreeWidget->isSortingEnabled();
        tableTreeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = tableTreeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(9, QApplication::translate("BluetoothHciSummaryDialog", "0", Q_NULLPTR));
        ___qtreewidgetitem1->setText(1, QApplication::translate("BluetoothHciSummaryDialog", "0x01", Q_NULLPTR));
        ___qtreewidgetitem1->setText(0, QApplication::translate("BluetoothHciSummaryDialog", "Link Control Commands", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem2 = tableTreeWidget->topLevelItem(1);
        ___qtreewidgetitem2->setText(9, QApplication::translate("BluetoothHciSummaryDialog", "0", Q_NULLPTR));
        ___qtreewidgetitem2->setText(1, QApplication::translate("BluetoothHciSummaryDialog", "0x02", Q_NULLPTR));
        ___qtreewidgetitem2->setText(0, QApplication::translate("BluetoothHciSummaryDialog", "Link Policy Commands", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem3 = tableTreeWidget->topLevelItem(2);
        ___qtreewidgetitem3->setText(9, QApplication::translate("BluetoothHciSummaryDialog", "0", Q_NULLPTR));
        ___qtreewidgetitem3->setText(1, QApplication::translate("BluetoothHciSummaryDialog", "0x03", Q_NULLPTR));
        ___qtreewidgetitem3->setText(0, QApplication::translate("BluetoothHciSummaryDialog", "Controller & Baseband Commands", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem4 = tableTreeWidget->topLevelItem(3);
        ___qtreewidgetitem4->setText(9, QApplication::translate("BluetoothHciSummaryDialog", "0", Q_NULLPTR));
        ___qtreewidgetitem4->setText(1, QApplication::translate("BluetoothHciSummaryDialog", "0x04", Q_NULLPTR));
        ___qtreewidgetitem4->setText(0, QApplication::translate("BluetoothHciSummaryDialog", "Informational Parameters", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem5 = tableTreeWidget->topLevelItem(4);
        ___qtreewidgetitem5->setText(9, QApplication::translate("BluetoothHciSummaryDialog", "0", Q_NULLPTR));
        ___qtreewidgetitem5->setText(1, QApplication::translate("BluetoothHciSummaryDialog", "0x05", Q_NULLPTR));
        ___qtreewidgetitem5->setText(0, QApplication::translate("BluetoothHciSummaryDialog", "Status Parameters", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem6 = tableTreeWidget->topLevelItem(5);
        ___qtreewidgetitem6->setText(9, QApplication::translate("BluetoothHciSummaryDialog", "0", Q_NULLPTR));
        ___qtreewidgetitem6->setText(1, QApplication::translate("BluetoothHciSummaryDialog", "0x06", Q_NULLPTR));
        ___qtreewidgetitem6->setText(0, QApplication::translate("BluetoothHciSummaryDialog", "Testing Commands", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem7 = tableTreeWidget->topLevelItem(6);
        ___qtreewidgetitem7->setText(9, QApplication::translate("BluetoothHciSummaryDialog", "0", Q_NULLPTR));
        ___qtreewidgetitem7->setText(1, QApplication::translate("BluetoothHciSummaryDialog", "0x08", Q_NULLPTR));
        ___qtreewidgetitem7->setText(0, QApplication::translate("BluetoothHciSummaryDialog", "LE Controller Commands", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem8 = tableTreeWidget->topLevelItem(7);
        ___qtreewidgetitem8->setText(9, QApplication::translate("BluetoothHciSummaryDialog", "0", Q_NULLPTR));
        ___qtreewidgetitem8->setText(1, QApplication::translate("BluetoothHciSummaryDialog", "0x3E", Q_NULLPTR));
        ___qtreewidgetitem8->setText(0, QApplication::translate("BluetoothHciSummaryDialog", "Bluetooth Logo Testing Commands", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem9 = tableTreeWidget->topLevelItem(8);
        ___qtreewidgetitem9->setText(9, QApplication::translate("BluetoothHciSummaryDialog", "0", Q_NULLPTR));
        ___qtreewidgetitem9->setText(1, QApplication::translate("BluetoothHciSummaryDialog", "0x3F", Q_NULLPTR));
        ___qtreewidgetitem9->setText(0, QApplication::translate("BluetoothHciSummaryDialog", "Vendor-Specific Commands", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem10 = tableTreeWidget->topLevelItem(9);
        ___qtreewidgetitem10->setText(9, QApplication::translate("BluetoothHciSummaryDialog", "0", Q_NULLPTR));
        ___qtreewidgetitem10->setText(0, QApplication::translate("BluetoothHciSummaryDialog", "Unknown OGF", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem11 = tableTreeWidget->topLevelItem(10);
        ___qtreewidgetitem11->setText(9, QApplication::translate("BluetoothHciSummaryDialog", "0", Q_NULLPTR));
        ___qtreewidgetitem11->setText(0, QApplication::translate("BluetoothHciSummaryDialog", "Events", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem12 = tableTreeWidget->topLevelItem(11);
        ___qtreewidgetitem12->setText(9, QApplication::translate("BluetoothHciSummaryDialog", "0", Q_NULLPTR));
        ___qtreewidgetitem12->setText(0, QApplication::translate("BluetoothHciSummaryDialog", "Status", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem13 = tableTreeWidget->topLevelItem(12);
        ___qtreewidgetitem13->setText(9, QApplication::translate("BluetoothHciSummaryDialog", "0", Q_NULLPTR));
        ___qtreewidgetitem13->setText(0, QApplication::translate("BluetoothHciSummaryDialog", "Reason", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem14 = tableTreeWidget->topLevelItem(13);
        ___qtreewidgetitem14->setText(9, QApplication::translate("BluetoothHciSummaryDialog", "0", Q_NULLPTR));
        ___qtreewidgetitem14->setText(0, QApplication::translate("BluetoothHciSummaryDialog", "Hardware Errors", Q_NULLPTR));
        tableTreeWidget->setSortingEnabled(__sortingEnabled);

        resultsFilterLabel->setText(QApplication::translate("BluetoothHciSummaryDialog", "Results filter:", Q_NULLPTR));
        label->setText(QApplication::translate("BluetoothHciSummaryDialog", "Display filter:", Q_NULLPTR));
        interfaceComboBox->clear();
        interfaceComboBox->insertItems(0, QStringList()
         << QApplication::translate("BluetoothHciSummaryDialog", "All Interfaces", Q_NULLPTR)
        );
        adapterComboBox->clear();
        adapterComboBox->insertItems(0, QStringList()
         << QApplication::translate("BluetoothHciSummaryDialog", "All Adapters", Q_NULLPTR)
        );
        hintLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BluetoothHciSummaryDialog: public Ui_BluetoothHciSummaryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLUETOOTH_HCI_SUMMARY_DIALOG_H

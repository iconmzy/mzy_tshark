/********************************************************************************
** Form generated from reading UI file 'bluetooth_devices_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLUETOOTH_DEVICES_DIALOG_H
#define UI_BLUETOOTH_DEVICES_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_BluetoothDevicesDialog
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
    QHBoxLayout *horizontalLayout;
    QComboBox *interfaceComboBox;
    QCheckBox *showInformationStepsCheckBox;
    QLabel *hintLabel;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *BluetoothDevicesDialog)
    {
        if (BluetoothDevicesDialog->objectName().isEmpty())
            BluetoothDevicesDialog->setObjectName(QStringLiteral("BluetoothDevicesDialog"));
        BluetoothDevicesDialog->resize(880, 477);
        BluetoothDevicesDialog->setBaseSize(QSize(0, 0));
        actionCopy_Cell = new QAction(BluetoothDevicesDialog);
        actionCopy_Cell->setObjectName(QStringLiteral("actionCopy_Cell"));
        actionCopy_Rows = new QAction(BluetoothDevicesDialog);
        actionCopy_Rows->setObjectName(QStringLiteral("actionCopy_Rows"));
        actionCopy_All = new QAction(BluetoothDevicesDialog);
        actionCopy_All->setObjectName(QStringLiteral("actionCopy_All"));
        actionSave_as_image = new QAction(BluetoothDevicesDialog);
        actionSave_as_image->setObjectName(QStringLiteral("actionSave_as_image"));
        actionMark_Unmark_Row = new QAction(BluetoothDevicesDialog);
        actionMark_Unmark_Row->setObjectName(QStringLiteral("actionMark_Unmark_Row"));
        actionMark_Unmark_Cell = new QAction(BluetoothDevicesDialog);
        actionMark_Unmark_Cell->setObjectName(QStringLiteral("actionMark_Unmark_Cell"));
        verticalLayout = new QVBoxLayout(BluetoothDevicesDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableTreeWidget = new QTreeWidget(BluetoothDevicesDialog);
        tableTreeWidget->setObjectName(QStringLiteral("tableTreeWidget"));
        tableTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        tableTreeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableTreeWidget->setTextElideMode(Qt::ElideMiddle);
        tableTreeWidget->setRootIsDecorated(false);
        tableTreeWidget->setItemsExpandable(false);
        tableTreeWidget->setSortingEnabled(true);
        tableTreeWidget->header()->setCascadingSectionResizes(false);
        tableTreeWidget->header()->setHighlightSections(false);
        tableTreeWidget->header()->setProperty("showSortIndicator", QVariant(true));

        verticalLayout->addWidget(tableTreeWidget);

        horizontalLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        horizontalLayout->setSpacing(-1);
#endif
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(-1, -1, -1, 0);
        interfaceComboBox = new QComboBox(BluetoothDevicesDialog);
        interfaceComboBox->setObjectName(QStringLiteral("interfaceComboBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(interfaceComboBox->sizePolicy().hasHeightForWidth());
        interfaceComboBox->setSizePolicy(sizePolicy);
        interfaceComboBox->setMinimumSize(QSize(350, 0));

        horizontalLayout->addWidget(interfaceComboBox);

        showInformationStepsCheckBox = new QCheckBox(BluetoothDevicesDialog);
        showInformationStepsCheckBox->setObjectName(QStringLiteral("showInformationStepsCheckBox"));
        showInformationStepsCheckBox->setChecked(false);

        horizontalLayout->addWidget(showInformationStepsCheckBox);


        verticalLayout->addLayout(horizontalLayout);

        hintLabel = new QLabel(BluetoothDevicesDialog);
        hintLabel->setObjectName(QStringLiteral("hintLabel"));

        verticalLayout->addWidget(hintLabel);

        buttonBox = new QDialogButtonBox(BluetoothDevicesDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(BluetoothDevicesDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), BluetoothDevicesDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), BluetoothDevicesDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(BluetoothDevicesDialog);
    } // setupUi

    void retranslateUi(QDialog *BluetoothDevicesDialog)
    {
        BluetoothDevicesDialog->setWindowTitle(QApplication::translate("BluetoothDevicesDialog", "Bluetooth Devices", Q_NULLPTR));
        actionCopy_Cell->setText(QApplication::translate("BluetoothDevicesDialog", "Copy Cell", Q_NULLPTR));
        actionCopy_Rows->setText(QApplication::translate("BluetoothDevicesDialog", "Copy Rows", Q_NULLPTR));
        actionCopy_All->setText(QApplication::translate("BluetoothDevicesDialog", "Copy All", Q_NULLPTR));
        actionSave_as_image->setText(QApplication::translate("BluetoothDevicesDialog", "Save as image", Q_NULLPTR));
        actionMark_Unmark_Row->setText(QApplication::translate("BluetoothDevicesDialog", "Mark/Unmark Row", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMark_Unmark_Row->setToolTip(QApplication::translate("BluetoothDevicesDialog", "Mark/Unmark Row", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMark_Unmark_Row->setShortcut(QApplication::translate("BluetoothDevicesDialog", "Ctrl-M", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMark_Unmark_Cell->setText(QApplication::translate("BluetoothDevicesDialog", "Mark/Unmark Cell", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = tableTreeWidget->headerItem();
        ___qtreewidgetitem->setText(8, QApplication::translate("BluetoothDevicesDialog", "Is Local Adapter", Q_NULLPTR));
        ___qtreewidgetitem->setText(7, QApplication::translate("BluetoothDevicesDialog", "HCI Revision", Q_NULLPTR));
        ___qtreewidgetitem->setText(6, QApplication::translate("BluetoothDevicesDialog", "HCI Version", Q_NULLPTR));
        ___qtreewidgetitem->setText(5, QApplication::translate("BluetoothDevicesDialog", "Manufacturer", Q_NULLPTR));
        ___qtreewidgetitem->setText(4, QApplication::translate("BluetoothDevicesDialog", "LMP Subversion", Q_NULLPTR));
        ___qtreewidgetitem->setText(3, QApplication::translate("BluetoothDevicesDialog", "LMP Version", Q_NULLPTR));
        ___qtreewidgetitem->setText(2, QApplication::translate("BluetoothDevicesDialog", "Name", Q_NULLPTR));
        ___qtreewidgetitem->setText(1, QApplication::translate("BluetoothDevicesDialog", "OUI", Q_NULLPTR));
        ___qtreewidgetitem->setText(0, QApplication::translate("BluetoothDevicesDialog", "BD_ADDR", Q_NULLPTR));
        interfaceComboBox->clear();
        interfaceComboBox->insertItems(0, QStringList()
         << QApplication::translate("BluetoothDevicesDialog", "All Interfaces", Q_NULLPTR)
        );
        showInformationStepsCheckBox->setText(QApplication::translate("BluetoothDevicesDialog", "Show information steps", Q_NULLPTR));
        hintLabel->setText(QApplication::translate("BluetoothDevicesDialog", "%1 items; Right click for more option; Double click for device details", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BluetoothDevicesDialog: public Ui_BluetoothDevicesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLUETOOTH_DEVICES_DIALOG_H

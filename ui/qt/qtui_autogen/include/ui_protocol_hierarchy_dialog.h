/********************************************************************************
** Form generated from reading UI file 'protocol_hierarchy_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROTOCOL_HIERARCHY_DIALOG_H
#define UI_PROTOCOL_HIERARCHY_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ProtocolHierarchyDialog
{
public:
    QAction *actionCopyAsCsv;
    QAction *actionCopyAsYaml;
    QVBoxLayout *verticalLayout;
    QTreeWidget *hierStatsTreeWidget;
    QLabel *hintLabel;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ProtocolHierarchyDialog)
    {
        if (ProtocolHierarchyDialog->objectName().isEmpty())
            ProtocolHierarchyDialog->setObjectName(QStringLiteral("ProtocolHierarchyDialog"));
        ProtocolHierarchyDialog->resize(620, 480);
        actionCopyAsCsv = new QAction(ProtocolHierarchyDialog);
        actionCopyAsCsv->setObjectName(QStringLiteral("actionCopyAsCsv"));
        actionCopyAsYaml = new QAction(ProtocolHierarchyDialog);
        actionCopyAsYaml->setObjectName(QStringLiteral("actionCopyAsYaml"));
        verticalLayout = new QVBoxLayout(ProtocolHierarchyDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        hierStatsTreeWidget = new QTreeWidget(ProtocolHierarchyDialog);
        hierStatsTreeWidget->setObjectName(QStringLiteral("hierStatsTreeWidget"));
        hierStatsTreeWidget->setUniformRowHeights(true);
        hierStatsTreeWidget->header()->setDefaultSectionSize(50);
        hierStatsTreeWidget->header()->setProperty("showSortIndicator", QVariant(false));

        verticalLayout->addWidget(hierStatsTreeWidget);

        hintLabel = new QLabel(ProtocolHierarchyDialog);
        hintLabel->setObjectName(QStringLiteral("hintLabel"));
        hintLabel->setWordWrap(true);

        verticalLayout->addWidget(hintLabel);

        buttonBox = new QDialogButtonBox(ProtocolHierarchyDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Help);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ProtocolHierarchyDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ProtocolHierarchyDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ProtocolHierarchyDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ProtocolHierarchyDialog);
    } // setupUi

    void retranslateUi(QDialog *ProtocolHierarchyDialog)
    {
        ProtocolHierarchyDialog->setWindowTitle(QApplication::translate("ProtocolHierarchyDialog", "Dialog", Q_NULLPTR));
        actionCopyAsCsv->setText(QApplication::translate("ProtocolHierarchyDialog", "Copy as CSV", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionCopyAsCsv->setToolTip(QApplication::translate("ProtocolHierarchyDialog", "Copy stream list as CSV.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionCopyAsYaml->setText(QApplication::translate("ProtocolHierarchyDialog", "Copy as YAML", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionCopyAsYaml->setToolTip(QApplication::translate("ProtocolHierarchyDialog", "Copy stream list as YAML.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        QTreeWidgetItem *___qtreewidgetitem = hierStatsTreeWidget->headerItem();
        ___qtreewidgetitem->setText(8, QApplication::translate("ProtocolHierarchyDialog", "End Bits/s", Q_NULLPTR));
        ___qtreewidgetitem->setText(7, QApplication::translate("ProtocolHierarchyDialog", "End Bytes", Q_NULLPTR));
        ___qtreewidgetitem->setText(6, QApplication::translate("ProtocolHierarchyDialog", "End Packets", Q_NULLPTR));
        ___qtreewidgetitem->setText(5, QApplication::translate("ProtocolHierarchyDialog", "Bits/s", Q_NULLPTR));
        ___qtreewidgetitem->setText(4, QApplication::translate("ProtocolHierarchyDialog", "Bytes", Q_NULLPTR));
        ___qtreewidgetitem->setText(3, QApplication::translate("ProtocolHierarchyDialog", "Percent Bytes", Q_NULLPTR));
        ___qtreewidgetitem->setText(2, QApplication::translate("ProtocolHierarchyDialog", "Packets", Q_NULLPTR));
        ___qtreewidgetitem->setText(1, QApplication::translate("ProtocolHierarchyDialog", "Percent Packets", Q_NULLPTR));
        ___qtreewidgetitem->setText(0, QApplication::translate("ProtocolHierarchyDialog", "Protocol", Q_NULLPTR));
        hintLabel->setText(QApplication::translate("ProtocolHierarchyDialog", "<small><i>A hint.</i></small>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ProtocolHierarchyDialog: public Ui_ProtocolHierarchyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROTOCOL_HIERARCHY_DIALOG_H

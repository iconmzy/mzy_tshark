/********************************************************************************
** Form generated from reading UI file 'sctp_all_assocs_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCTP_ALL_ASSOCS_DIALOG_H
#define UI_SCTP_ALL_ASSOCS_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SCTPAllAssocsDialog
{
public:
    QAction *actionReset;
    QAction *actionZoomIn;
    QAction *actionZoomOut;
    QAction *actionMoveUp10;
    QAction *actionMoveLeft10;
    QAction *actionMoveRight10;
    QAction *actionMoveDown10;
    QAction *actionMoveUp1;
    QAction *actionMoveLeft1;
    QAction *actionMoveRight1;
    QAction *actionMoveDown1;
    QAction *actionNextStream;
    QAction *actionPreviousStream;
    QAction *actionSwitchDirection;
    QAction *actionGoToPacket;
    QAction *actionDragZoom;
    QAction *actionToggleSequenceNumbers;
    QAction *actionToggleTimeOrigin;
    QAction *actionCrosshairs;
    QAction *actionRoundTripTime;
    QAction *actionThroughput;
    QAction *actionStevens;
    QAction *actionWindowScaling;
    QAction *actionTcptrace;
    QVBoxLayout *verticalLayout;
    QTableWidget *assocList;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *setFilterButton;
    QPushButton *analyseButton;
    QSpacerItem *horizontalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SCTPAllAssocsDialog)
    {
        if (SCTPAllAssocsDialog->objectName().isEmpty())
            SCTPAllAssocsDialog->setObjectName(QStringLiteral("SCTPAllAssocsDialog"));
        SCTPAllAssocsDialog->resize(685, 300);
        actionReset = new QAction(SCTPAllAssocsDialog);
        actionReset->setObjectName(QStringLiteral("actionReset"));
        actionZoomIn = new QAction(SCTPAllAssocsDialog);
        actionZoomIn->setObjectName(QStringLiteral("actionZoomIn"));
        actionZoomOut = new QAction(SCTPAllAssocsDialog);
        actionZoomOut->setObjectName(QStringLiteral("actionZoomOut"));
        actionMoveUp10 = new QAction(SCTPAllAssocsDialog);
        actionMoveUp10->setObjectName(QStringLiteral("actionMoveUp10"));
        actionMoveLeft10 = new QAction(SCTPAllAssocsDialog);
        actionMoveLeft10->setObjectName(QStringLiteral("actionMoveLeft10"));
        actionMoveRight10 = new QAction(SCTPAllAssocsDialog);
        actionMoveRight10->setObjectName(QStringLiteral("actionMoveRight10"));
        actionMoveDown10 = new QAction(SCTPAllAssocsDialog);
        actionMoveDown10->setObjectName(QStringLiteral("actionMoveDown10"));
        actionMoveUp1 = new QAction(SCTPAllAssocsDialog);
        actionMoveUp1->setObjectName(QStringLiteral("actionMoveUp1"));
        actionMoveLeft1 = new QAction(SCTPAllAssocsDialog);
        actionMoveLeft1->setObjectName(QStringLiteral("actionMoveLeft1"));
        actionMoveRight1 = new QAction(SCTPAllAssocsDialog);
        actionMoveRight1->setObjectName(QStringLiteral("actionMoveRight1"));
        actionMoveDown1 = new QAction(SCTPAllAssocsDialog);
        actionMoveDown1->setObjectName(QStringLiteral("actionMoveDown1"));
        actionNextStream = new QAction(SCTPAllAssocsDialog);
        actionNextStream->setObjectName(QStringLiteral("actionNextStream"));
        actionPreviousStream = new QAction(SCTPAllAssocsDialog);
        actionPreviousStream->setObjectName(QStringLiteral("actionPreviousStream"));
        actionSwitchDirection = new QAction(SCTPAllAssocsDialog);
        actionSwitchDirection->setObjectName(QStringLiteral("actionSwitchDirection"));
        actionGoToPacket = new QAction(SCTPAllAssocsDialog);
        actionGoToPacket->setObjectName(QStringLiteral("actionGoToPacket"));
        actionDragZoom = new QAction(SCTPAllAssocsDialog);
        actionDragZoom->setObjectName(QStringLiteral("actionDragZoom"));
        actionToggleSequenceNumbers = new QAction(SCTPAllAssocsDialog);
        actionToggleSequenceNumbers->setObjectName(QStringLiteral("actionToggleSequenceNumbers"));
        actionToggleTimeOrigin = new QAction(SCTPAllAssocsDialog);
        actionToggleTimeOrigin->setObjectName(QStringLiteral("actionToggleTimeOrigin"));
        actionCrosshairs = new QAction(SCTPAllAssocsDialog);
        actionCrosshairs->setObjectName(QStringLiteral("actionCrosshairs"));
        actionRoundTripTime = new QAction(SCTPAllAssocsDialog);
        actionRoundTripTime->setObjectName(QStringLiteral("actionRoundTripTime"));
        actionThroughput = new QAction(SCTPAllAssocsDialog);
        actionThroughput->setObjectName(QStringLiteral("actionThroughput"));
        actionStevens = new QAction(SCTPAllAssocsDialog);
        actionStevens->setObjectName(QStringLiteral("actionStevens"));
        actionWindowScaling = new QAction(SCTPAllAssocsDialog);
        actionWindowScaling->setObjectName(QStringLiteral("actionWindowScaling"));
        actionTcptrace = new QAction(SCTPAllAssocsDialog);
        actionTcptrace->setObjectName(QStringLiteral("actionTcptrace"));
        verticalLayout = new QVBoxLayout(SCTPAllAssocsDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        assocList = new QTableWidget(SCTPAllAssocsDialog);
        if (assocList->columnCount() < 6)
            assocList->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        assocList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        assocList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        assocList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        assocList->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        assocList->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        assocList->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (assocList->rowCount() < 2)
            assocList->setRowCount(2);
        assocList->setObjectName(QStringLiteral("assocList"));
        assocList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        assocList->setProperty("showDropIndicator", QVariant(false));
        assocList->setDragDropOverwriteMode(false);
        assocList->setAlternatingRowColors(true);
        assocList->setSelectionMode(QAbstractItemView::SingleSelection);
        assocList->setSelectionBehavior(QAbstractItemView::SelectRows);
        assocList->setSortingEnabled(true);
        assocList->setWordWrap(false);
        assocList->setRowCount(2);
        assocList->setColumnCount(6);
        assocList->horizontalHeader()->setDefaultSectionSize(120);
        assocList->horizontalHeader()->setMinimumSectionSize(50);
        assocList->horizontalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(assocList);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        setFilterButton = new QPushButton(SCTPAllAssocsDialog);
        setFilterButton->setObjectName(QStringLiteral("setFilterButton"));
        setFilterButton->setEnabled(false);
        setFilterButton->setFocusPolicy(Qt::ClickFocus);

        horizontalLayout_2->addWidget(setFilterButton);

        analyseButton = new QPushButton(SCTPAllAssocsDialog);
        analyseButton->setObjectName(QStringLiteral("analyseButton"));
        analyseButton->setEnabled(false);
        analyseButton->setFocusPolicy(Qt::ClickFocus);

        horizontalLayout_2->addWidget(analyseButton);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        buttonBox = new QDialogButtonBox(SCTPAllAssocsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        horizontalLayout_2->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(SCTPAllAssocsDialog);
        QObject::connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), SCTPAllAssocsDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(SCTPAllAssocsDialog);
    } // setupUi

    void retranslateUi(QDialog *SCTPAllAssocsDialog)
    {
        SCTPAllAssocsDialog->setWindowTitle(QApplication::translate("SCTPAllAssocsDialog", "Wireshark - SCTP Associations", Q_NULLPTR));
        actionReset->setText(QApplication::translate("SCTPAllAssocsDialog", "Reset Graph", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionReset->setToolTip(QApplication::translate("SCTPAllAssocsDialog", "Reset the graph to its initial state.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionReset->setShortcut(QApplication::translate("SCTPAllAssocsDialog", "0", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionZoomIn->setText(QApplication::translate("SCTPAllAssocsDialog", "Zoom In", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionZoomIn->setToolTip(QApplication::translate("SCTPAllAssocsDialog", "Zoom In", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionZoomIn->setShortcut(QApplication::translate("SCTPAllAssocsDialog", "+", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionZoomOut->setText(QApplication::translate("SCTPAllAssocsDialog", "Zoom Out", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionZoomOut->setToolTip(QApplication::translate("SCTPAllAssocsDialog", "Zoom Out", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionZoomOut->setShortcut(QApplication::translate("SCTPAllAssocsDialog", "-", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveUp10->setText(QApplication::translate("SCTPAllAssocsDialog", "Move Up 10 Pixels", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveUp10->setToolTip(QApplication::translate("SCTPAllAssocsDialog", "Move Up 10 Pixels", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveUp10->setShortcut(QApplication::translate("SCTPAllAssocsDialog", "Up", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveLeft10->setText(QApplication::translate("SCTPAllAssocsDialog", "Move Left 10 Pixels", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveLeft10->setToolTip(QApplication::translate("SCTPAllAssocsDialog", "Move Left 10 Pixels", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveLeft10->setShortcut(QApplication::translate("SCTPAllAssocsDialog", "Left", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveRight10->setText(QApplication::translate("SCTPAllAssocsDialog", "Move Right 10 Pixels", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveRight10->setToolTip(QApplication::translate("SCTPAllAssocsDialog", "Move Right 10 Pixels", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveRight10->setShortcut(QApplication::translate("SCTPAllAssocsDialog", "Right", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveDown10->setText(QApplication::translate("SCTPAllAssocsDialog", "Move Down 10 Pixels", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveDown10->setToolTip(QApplication::translate("SCTPAllAssocsDialog", "Move Down 10 Pixels", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveDown10->setShortcut(QApplication::translate("SCTPAllAssocsDialog", "Down", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveUp1->setText(QApplication::translate("SCTPAllAssocsDialog", "Move Up 1 Pixel", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveUp1->setToolTip(QApplication::translate("SCTPAllAssocsDialog", "Move Up 1 Pixel", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveUp1->setShortcut(QApplication::translate("SCTPAllAssocsDialog", "Shift+Up", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveLeft1->setText(QApplication::translate("SCTPAllAssocsDialog", "Move Left 1 Pixel", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveLeft1->setToolTip(QApplication::translate("SCTPAllAssocsDialog", "Move Left 1 Pixel", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveLeft1->setShortcut(QApplication::translate("SCTPAllAssocsDialog", "Shift+Left", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveRight1->setText(QApplication::translate("SCTPAllAssocsDialog", "Move Right 1 Pixel", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveRight1->setToolTip(QApplication::translate("SCTPAllAssocsDialog", "Move Right 1 Pixel", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveRight1->setShortcut(QApplication::translate("SCTPAllAssocsDialog", "Shift+Right", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveDown1->setText(QApplication::translate("SCTPAllAssocsDialog", "Move Down 1 Pixel", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveDown1->setToolTip(QApplication::translate("SCTPAllAssocsDialog", "Move Down 1 Pixel", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveDown1->setShortcut(QApplication::translate("SCTPAllAssocsDialog", "Shift+Down", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionNextStream->setText(QApplication::translate("SCTPAllAssocsDialog", "Next Stream", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionNextStream->setToolTip(QApplication::translate("SCTPAllAssocsDialog", "Go to the next stream in the capture", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionNextStream->setShortcut(QApplication::translate("SCTPAllAssocsDialog", "PgUp", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionPreviousStream->setText(QApplication::translate("SCTPAllAssocsDialog", "Previous Stream", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionPreviousStream->setToolTip(QApplication::translate("SCTPAllAssocsDialog", "Go to the previous stream in the capture", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionPreviousStream->setShortcut(QApplication::translate("SCTPAllAssocsDialog", "PgDown", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionSwitchDirection->setText(QApplication::translate("SCTPAllAssocsDialog", "Switch Direction", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSwitchDirection->setToolTip(QApplication::translate("SCTPAllAssocsDialog", "Switch direction (swap TCP endpoints)", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionSwitchDirection->setShortcut(QApplication::translate("SCTPAllAssocsDialog", "D", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionGoToPacket->setText(QApplication::translate("SCTPAllAssocsDialog", "Go To Packet Under Cursor", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionGoToPacket->setToolTip(QApplication::translate("SCTPAllAssocsDialog", "Go to packet currently under the cursor", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionGoToPacket->setShortcut(QApplication::translate("SCTPAllAssocsDialog", "G", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionDragZoom->setText(QApplication::translate("SCTPAllAssocsDialog", "Drag / Zoom", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionDragZoom->setToolTip(QApplication::translate("SCTPAllAssocsDialog", "Toggle mouse drag / zoom behavior", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionDragZoom->setShortcut(QApplication::translate("SCTPAllAssocsDialog", "Z", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionToggleSequenceNumbers->setText(QApplication::translate("SCTPAllAssocsDialog", "Relative / Absolute Sequence Numbers", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionToggleSequenceNumbers->setToolTip(QApplication::translate("SCTPAllAssocsDialog", "Toggle relative / absolute sequence numbers", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionToggleSequenceNumbers->setShortcut(QApplication::translate("SCTPAllAssocsDialog", "S", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionToggleTimeOrigin->setText(QApplication::translate("SCTPAllAssocsDialog", "Capture / Session Time Origin", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionToggleTimeOrigin->setToolTip(QApplication::translate("SCTPAllAssocsDialog", "Toggle capture / session time origin", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionToggleTimeOrigin->setShortcut(QApplication::translate("SCTPAllAssocsDialog", "T", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionCrosshairs->setText(QApplication::translate("SCTPAllAssocsDialog", "Crosshairs", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionCrosshairs->setToolTip(QApplication::translate("SCTPAllAssocsDialog", "Toggle crosshairs", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionCrosshairs->setShortcut(QApplication::translate("SCTPAllAssocsDialog", "Space", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionRoundTripTime->setText(QApplication::translate("SCTPAllAssocsDialog", "Round Trip Time", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionRoundTripTime->setToolTip(QApplication::translate("SCTPAllAssocsDialog", "Switch to the Round Trip Time graph", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionRoundTripTime->setShortcut(QApplication::translate("SCTPAllAssocsDialog", "1", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionThroughput->setText(QApplication::translate("SCTPAllAssocsDialog", "Throughput", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionThroughput->setToolTip(QApplication::translate("SCTPAllAssocsDialog", "Switch to the Throughput graph", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionThroughput->setShortcut(QApplication::translate("SCTPAllAssocsDialog", "2", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionStevens->setText(QApplication::translate("SCTPAllAssocsDialog", "Time / Sequence (Stevens)", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionStevens->setToolTip(QApplication::translate("SCTPAllAssocsDialog", "Switch to the Stevens-style Time / Sequence graph", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionStevens->setShortcut(QApplication::translate("SCTPAllAssocsDialog", "3", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionWindowScaling->setText(QApplication::translate("SCTPAllAssocsDialog", "Window Scaling", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionWindowScaling->setToolTip(QApplication::translate("SCTPAllAssocsDialog", "Switch to the Window Scaling graph", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionWindowScaling->setShortcut(QApplication::translate("SCTPAllAssocsDialog", "5", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionTcptrace->setText(QApplication::translate("SCTPAllAssocsDialog", "Time / Sequence (tcptrace)", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionTcptrace->setToolTip(QApplication::translate("SCTPAllAssocsDialog", "Switch to the tcptrace-style Time / Sequence graph", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionTcptrace->setShortcut(QApplication::translate("SCTPAllAssocsDialog", "4", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        QTableWidgetItem *___qtablewidgetitem = assocList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("SCTPAllAssocsDialog", "ID", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = assocList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("SCTPAllAssocsDialog", "Port 1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = assocList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("SCTPAllAssocsDialog", "Port 2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = assocList->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("SCTPAllAssocsDialog", "Number of Packets", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = assocList->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("SCTPAllAssocsDialog", "Number of DATA Chunks", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = assocList->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("SCTPAllAssocsDialog", "Number of Bytes", Q_NULLPTR));
        setFilterButton->setText(QApplication::translate("SCTPAllAssocsDialog", "Filter Selected Association", Q_NULLPTR));
        analyseButton->setText(QApplication::translate("SCTPAllAssocsDialog", "Analyze", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SCTPAllAssocsDialog: public Ui_SCTPAllAssocsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCTP_ALL_ASSOCS_DIALOG_H

/********************************************************************************
** Form generated from reading UI file 'lte_rlc_graph_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LTE_RLC_GRAPH_DIALOG_H
#define UI_LTE_RLC_GRAPH_DIALOG_H

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
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "widgets/qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_LteRlcGraphDialog
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
    QAction *actionDragZoom;
    QAction *actionCrosshairs;
    QAction *actionMoveUp100;
    QAction *actionMoveDown100;
    QAction *actionGoToPacket;
    QAction *actionZoomInX;
    QAction *actionZoomOutY;
    QAction *actionZoomInY;
    QAction *actionZoomOutX;
    QAction *actionSwitchDirection;
    QVBoxLayout *verticalLayout;
    QCustomPlot *rlcPlot;
    QLabel *hintLabel;
    QHBoxLayout *horizontalLayout_2;
    QLabel *mouseLabel;
    QRadioButton *dragRadioButton;
    QRadioButton *zoomRadioButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *resetButton;
    QPushButton *otherDirectionButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *LteRlcGraphDialog)
    {
        if (LteRlcGraphDialog->objectName().isEmpty())
            LteRlcGraphDialog->setObjectName(QStringLiteral("LteRlcGraphDialog"));
        LteRlcGraphDialog->resize(660, 447);
        actionReset = new QAction(LteRlcGraphDialog);
        actionReset->setObjectName(QStringLiteral("actionReset"));
        actionZoomIn = new QAction(LteRlcGraphDialog);
        actionZoomIn->setObjectName(QStringLiteral("actionZoomIn"));
        actionZoomOut = new QAction(LteRlcGraphDialog);
        actionZoomOut->setObjectName(QStringLiteral("actionZoomOut"));
        actionMoveUp10 = new QAction(LteRlcGraphDialog);
        actionMoveUp10->setObjectName(QStringLiteral("actionMoveUp10"));
        actionMoveLeft10 = new QAction(LteRlcGraphDialog);
        actionMoveLeft10->setObjectName(QStringLiteral("actionMoveLeft10"));
        actionMoveRight10 = new QAction(LteRlcGraphDialog);
        actionMoveRight10->setObjectName(QStringLiteral("actionMoveRight10"));
        actionMoveDown10 = new QAction(LteRlcGraphDialog);
        actionMoveDown10->setObjectName(QStringLiteral("actionMoveDown10"));
        actionMoveUp1 = new QAction(LteRlcGraphDialog);
        actionMoveUp1->setObjectName(QStringLiteral("actionMoveUp1"));
        actionMoveLeft1 = new QAction(LteRlcGraphDialog);
        actionMoveLeft1->setObjectName(QStringLiteral("actionMoveLeft1"));
        actionMoveRight1 = new QAction(LteRlcGraphDialog);
        actionMoveRight1->setObjectName(QStringLiteral("actionMoveRight1"));
        actionMoveDown1 = new QAction(LteRlcGraphDialog);
        actionMoveDown1->setObjectName(QStringLiteral("actionMoveDown1"));
        actionDragZoom = new QAction(LteRlcGraphDialog);
        actionDragZoom->setObjectName(QStringLiteral("actionDragZoom"));
        actionCrosshairs = new QAction(LteRlcGraphDialog);
        actionCrosshairs->setObjectName(QStringLiteral("actionCrosshairs"));
        actionMoveUp100 = new QAction(LteRlcGraphDialog);
        actionMoveUp100->setObjectName(QStringLiteral("actionMoveUp100"));
        actionMoveDown100 = new QAction(LteRlcGraphDialog);
        actionMoveDown100->setObjectName(QStringLiteral("actionMoveDown100"));
        actionGoToPacket = new QAction(LteRlcGraphDialog);
        actionGoToPacket->setObjectName(QStringLiteral("actionGoToPacket"));
        actionZoomInX = new QAction(LteRlcGraphDialog);
        actionZoomInX->setObjectName(QStringLiteral("actionZoomInX"));
        actionZoomOutY = new QAction(LteRlcGraphDialog);
        actionZoomOutY->setObjectName(QStringLiteral("actionZoomOutY"));
        actionZoomInY = new QAction(LteRlcGraphDialog);
        actionZoomInY->setObjectName(QStringLiteral("actionZoomInY"));
        actionZoomOutX = new QAction(LteRlcGraphDialog);
        actionZoomOutX->setObjectName(QStringLiteral("actionZoomOutX"));
        actionSwitchDirection = new QAction(LteRlcGraphDialog);
        actionSwitchDirection->setObjectName(QStringLiteral("actionSwitchDirection"));
        verticalLayout = new QVBoxLayout(LteRlcGraphDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        rlcPlot = new QCustomPlot(LteRlcGraphDialog);
        rlcPlot->setObjectName(QStringLiteral("rlcPlot"));

        verticalLayout->addWidget(rlcPlot);

        hintLabel = new QLabel(LteRlcGraphDialog);
        hintLabel->setObjectName(QStringLiteral("hintLabel"));
        hintLabel->setWordWrap(true);

        verticalLayout->addWidget(hintLabel);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        mouseLabel = new QLabel(LteRlcGraphDialog);
        mouseLabel->setObjectName(QStringLiteral("mouseLabel"));

        horizontalLayout_2->addWidget(mouseLabel);

        dragRadioButton = new QRadioButton(LteRlcGraphDialog);
        dragRadioButton->setObjectName(QStringLiteral("dragRadioButton"));
        dragRadioButton->setCheckable(true);

        horizontalLayout_2->addWidget(dragRadioButton);

        zoomRadioButton = new QRadioButton(LteRlcGraphDialog);
        zoomRadioButton->setObjectName(QStringLiteral("zoomRadioButton"));
        zoomRadioButton->setCheckable(true);

        horizontalLayout_2->addWidget(zoomRadioButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        resetButton = new QPushButton(LteRlcGraphDialog);
        resetButton->setObjectName(QStringLiteral("resetButton"));

        horizontalLayout_2->addWidget(resetButton);

        otherDirectionButton = new QPushButton(LteRlcGraphDialog);
        otherDirectionButton->setObjectName(QStringLiteral("otherDirectionButton"));

        horizontalLayout_2->addWidget(otherDirectionButton);


        verticalLayout->addLayout(horizontalLayout_2);

        buttonBox = new QDialogButtonBox(LteRlcGraphDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Help|QDialogButtonBox::Save);

        verticalLayout->addWidget(buttonBox);

        verticalLayout->setStretch(0, 1);

        retranslateUi(LteRlcGraphDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), LteRlcGraphDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), LteRlcGraphDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(LteRlcGraphDialog);
    } // setupUi

    void retranslateUi(QDialog *LteRlcGraphDialog)
    {
        LteRlcGraphDialog->setWindowTitle(QApplication::translate("LteRlcGraphDialog", "Dialog", Q_NULLPTR));
        actionReset->setText(QApplication::translate("LteRlcGraphDialog", "Reset Graph", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionReset->setToolTip(QApplication::translate("LteRlcGraphDialog", "Reset the graph to its initial state.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionReset->setShortcut(QApplication::translate("LteRlcGraphDialog", "0", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionZoomIn->setText(QApplication::translate("LteRlcGraphDialog", "Zoom In", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionZoomIn->setToolTip(QApplication::translate("LteRlcGraphDialog", "Zoom In", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionZoomIn->setShortcut(QApplication::translate("LteRlcGraphDialog", "+", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionZoomOut->setText(QApplication::translate("LteRlcGraphDialog", "Zoom Out", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionZoomOut->setToolTip(QApplication::translate("LteRlcGraphDialog", "Zoom Out", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionZoomOut->setShortcut(QApplication::translate("LteRlcGraphDialog", "-", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveUp10->setText(QApplication::translate("LteRlcGraphDialog", "Move Up 10 Pixels", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveUp10->setToolTip(QApplication::translate("LteRlcGraphDialog", "Move Up 10 Pixels", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveUp10->setShortcut(QApplication::translate("LteRlcGraphDialog", "Up", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveLeft10->setText(QApplication::translate("LteRlcGraphDialog", "Move Left 10 Pixels", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveLeft10->setToolTip(QApplication::translate("LteRlcGraphDialog", "Move Left 10 Pixels", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveLeft10->setShortcut(QApplication::translate("LteRlcGraphDialog", "Left", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveRight10->setText(QApplication::translate("LteRlcGraphDialog", "Move Right 10 Pixels", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveRight10->setToolTip(QApplication::translate("LteRlcGraphDialog", "Move Right 10 Pixels", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveRight10->setShortcut(QApplication::translate("LteRlcGraphDialog", "Right", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveDown10->setText(QApplication::translate("LteRlcGraphDialog", "Move Down 10 Pixels", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveDown10->setToolTip(QApplication::translate("LteRlcGraphDialog", "Move Down 10 Pixels", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveDown10->setShortcut(QApplication::translate("LteRlcGraphDialog", "Down", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveUp1->setText(QApplication::translate("LteRlcGraphDialog", "Move Up 1 Pixel", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveUp1->setToolTip(QApplication::translate("LteRlcGraphDialog", "Move Up 1 Pixel", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveUp1->setShortcut(QApplication::translate("LteRlcGraphDialog", "Shift+Up", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveLeft1->setText(QApplication::translate("LteRlcGraphDialog", "Move Left 1 Pixel", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveLeft1->setToolTip(QApplication::translate("LteRlcGraphDialog", "Move Left 1 Pixel", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveLeft1->setShortcut(QApplication::translate("LteRlcGraphDialog", "Shift+Left", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveRight1->setText(QApplication::translate("LteRlcGraphDialog", "Move Right 1 Pixel", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveRight1->setToolTip(QApplication::translate("LteRlcGraphDialog", "Move Right 1 Pixel", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveRight1->setShortcut(QApplication::translate("LteRlcGraphDialog", "Shift+Right", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveDown1->setText(QApplication::translate("LteRlcGraphDialog", "Move Down 1 Pixel", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveDown1->setToolTip(QApplication::translate("LteRlcGraphDialog", "Move down 1 Pixel", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveDown1->setShortcut(QApplication::translate("LteRlcGraphDialog", "Shift+Down", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionDragZoom->setText(QApplication::translate("LteRlcGraphDialog", "Drag / Zoom", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionDragZoom->setToolTip(QApplication::translate("LteRlcGraphDialog", "Toggle mouse drag / zoom behavior", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionDragZoom->setShortcut(QApplication::translate("LteRlcGraphDialog", "Z", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionCrosshairs->setText(QApplication::translate("LteRlcGraphDialog", "Crosshairs", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionCrosshairs->setToolTip(QApplication::translate("LteRlcGraphDialog", "Toggle crosshairs", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionCrosshairs->setShortcut(QApplication::translate("LteRlcGraphDialog", "Space", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveUp100->setText(QApplication::translate("LteRlcGraphDialog", "Move Up 100 Pixels", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveUp100->setToolTip(QApplication::translate("LteRlcGraphDialog", "Move Up 100 Pixels", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveUp100->setShortcut(QApplication::translate("LteRlcGraphDialog", "PgUp", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveDown100->setText(QApplication::translate("LteRlcGraphDialog", "Move Up 100 Pixels", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveDown100->setToolTip(QApplication::translate("LteRlcGraphDialog", "Move Up 100 Pixels", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveDown100->setShortcut(QApplication::translate("LteRlcGraphDialog", "PgDown", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionGoToPacket->setText(QApplication::translate("LteRlcGraphDialog", "Go To Packet Under Cursor", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionGoToPacket->setToolTip(QApplication::translate("LteRlcGraphDialog", "Go to packet currently under the cursor", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionGoToPacket->setShortcut(QApplication::translate("LteRlcGraphDialog", "G", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionZoomInX->setText(QApplication::translate("LteRlcGraphDialog", "Zoom In X Axis", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionZoomInX->setToolTip(QApplication::translate("LteRlcGraphDialog", "Zoom In X Axis", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionZoomInX->setShortcut(QApplication::translate("LteRlcGraphDialog", "X", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionZoomOutY->setText(QApplication::translate("LteRlcGraphDialog", "Zoom Out Y Axis", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionZoomOutY->setToolTip(QApplication::translate("LteRlcGraphDialog", "Zoom Out Y Axis", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionZoomOutY->setShortcut(QApplication::translate("LteRlcGraphDialog", "Shift+Y", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionZoomInY->setText(QApplication::translate("LteRlcGraphDialog", "Zoom In Y Axis", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionZoomInY->setToolTip(QApplication::translate("LteRlcGraphDialog", "Zoom In Y Axis", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionZoomInY->setShortcut(QApplication::translate("LteRlcGraphDialog", "Y", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionZoomOutX->setText(QApplication::translate("LteRlcGraphDialog", "Zoom Out X Axis", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionZoomOutX->setToolTip(QApplication::translate("LteRlcGraphDialog", "Zoom Out X Axis", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionZoomOutX->setShortcut(QApplication::translate("LteRlcGraphDialog", "Shift+X", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionSwitchDirection->setText(QApplication::translate("LteRlcGraphDialog", "Switch Direction", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSwitchDirection->setToolTip(QApplication::translate("LteRlcGraphDialog", "Switch direction (swap between UL and DL)", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionSwitchDirection->setShortcut(QApplication::translate("LteRlcGraphDialog", "D", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        hintLabel->setToolTip(QApplication::translate("LteRlcGraphDialog", "<html><head/><body>\n"
"\n"
"<h3>Valuable and amazing time-saving keyboard shortcuts</h3>\n"
"<table><tbody>\n"
"\n"
"<tr><th>+</th><td>Zoom in</td></th>\n"
"<tr><th>-</th><td>Zoom out</td></th>\n"
"<tr><th>0</th><td>Reset graph to its initial state</td></th>\n"
"\n"
"<tr><th>\342\206\222</th><td>Move right 10 pixels</td></th>\n"
"<tr><th>\342\206\220</th><td>Move left 10 pixels</td></th>\n"
"<tr><th>\342\206\221</th><td>Move up 10 pixels</td></th>\n"
"<tr><th>\342\206\223</th><td>Move down 10 pixels</td></th>\n"
"<tr><th><i>Shift+</i>\342\206\222</th><td>Move right 1 pixel</td></th>\n"
"<tr><th><i>Shift+</i>\342\206\220</th><td>Move left 1 pixel</td></th>\n"
"<tr><th><i>Shift+</i>\342\206\221</th><td>Move up 1 pixel</td></th>\n"
"<tr><th><i>Shift+</i>\342\206\223</th><td>Move down 1 pixel</td></th>\n"
"\n"
"<tr><th>g</th><td>Go to packet under cursor</td></th>\n"
"\n"
"<tr><th>z</th><td>Toggle mouse drag / zoom</td></th>\n"
"<tr><th>t</th><td>Toggle capture / session time origin</td></th>\n"
"<tr><th>Space</t"
                        "h><td>Toggle crosshairs</td></th>\n"
"\n"
"</tbody></table>\n"
"</body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        hintLabel->setText(QString());
        mouseLabel->setText(QApplication::translate("LteRlcGraphDialog", "Mouse", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        dragRadioButton->setToolTip(QApplication::translate("LteRlcGraphDialog", "Drag using the mouse button.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        dragRadioButton->setText(QApplication::translate("LteRlcGraphDialog", "drags", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        zoomRadioButton->setToolTip(QApplication::translate("LteRlcGraphDialog", "Select using the mouse button.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        zoomRadioButton->setText(QApplication::translate("LteRlcGraphDialog", "zooms", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        resetButton->setToolTip(QApplication::translate("LteRlcGraphDialog", "<html><head/><body><p>Reset the graph to its initial state.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        resetButton->setText(QApplication::translate("LteRlcGraphDialog", "Reset", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        otherDirectionButton->setToolTip(QApplication::translate("LteRlcGraphDialog", "<html><head/><body><p>Switch the direction of the connection (view the opposite flow).</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        otherDirectionButton->setText(QApplication::translate("LteRlcGraphDialog", "Switch Direction", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LteRlcGraphDialog: public Ui_LteRlcGraphDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LTE_RLC_GRAPH_DIALOG_H

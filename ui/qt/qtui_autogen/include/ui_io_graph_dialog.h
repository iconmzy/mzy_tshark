/********************************************************************************
** Form generated from reading UI file 'io_graph_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IO_GRAPH_DIALOG_H
#define UI_IO_GRAPH_DIALOG_H

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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "widgets/elided_label.h"
#include "widgets/qcustomplot.h"
#include "widgets/stock_icon_tool_button.h"
#include "widgets/tabnav_tree_view.h"

QT_BEGIN_NAMESPACE

class Ui_IOGraphDialog
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
    QAction *actionGoToPacket;
    QAction *actionDragZoom;
    QAction *actionToggleTimeOrigin;
    QAction *actionCrosshairs;
    QAction *actionZoomInX;
    QAction *actionZoomOutX;
    QAction *actionZoomInY;
    QAction *actionZoomOutY;
    QVBoxLayout *verticalLayout_2;
    QSplitter *splitter;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QCustomPlot *ioPlot;
    ElidedLabel *hintLabel;
    TabnavTreeView *graphUat;
    QHBoxLayout *horizontalLayout;
    StockIconToolButton *newToolButton;
    StockIconToolButton *deleteToolButton;
    StockIconToolButton *copyToolButton;
    StockIconToolButton *clearToolButton;
    QSpacerItem *horizontalSpacer_4;
    QLabel *mouseLabel;
    QRadioButton *dragRadioButton;
    QRadioButton *zoomRadioButton;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QComboBox *intervalComboBox;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *todCheckBox;
    QSpacerItem *horizontalSpacer_5;
    QCheckBox *logCheckBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *resetButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *IOGraphDialog)
    {
        if (IOGraphDialog->objectName().isEmpty())
            IOGraphDialog->setObjectName(QStringLiteral("IOGraphDialog"));
        IOGraphDialog->resize(850, 640);
        actionReset = new QAction(IOGraphDialog);
        actionReset->setObjectName(QStringLiteral("actionReset"));
        actionZoomIn = new QAction(IOGraphDialog);
        actionZoomIn->setObjectName(QStringLiteral("actionZoomIn"));
        actionZoomOut = new QAction(IOGraphDialog);
        actionZoomOut->setObjectName(QStringLiteral("actionZoomOut"));
        actionMoveUp10 = new QAction(IOGraphDialog);
        actionMoveUp10->setObjectName(QStringLiteral("actionMoveUp10"));
        actionMoveLeft10 = new QAction(IOGraphDialog);
        actionMoveLeft10->setObjectName(QStringLiteral("actionMoveLeft10"));
        actionMoveRight10 = new QAction(IOGraphDialog);
        actionMoveRight10->setObjectName(QStringLiteral("actionMoveRight10"));
        actionMoveDown10 = new QAction(IOGraphDialog);
        actionMoveDown10->setObjectName(QStringLiteral("actionMoveDown10"));
        actionMoveUp1 = new QAction(IOGraphDialog);
        actionMoveUp1->setObjectName(QStringLiteral("actionMoveUp1"));
        actionMoveLeft1 = new QAction(IOGraphDialog);
        actionMoveLeft1->setObjectName(QStringLiteral("actionMoveLeft1"));
        actionMoveRight1 = new QAction(IOGraphDialog);
        actionMoveRight1->setObjectName(QStringLiteral("actionMoveRight1"));
        actionMoveDown1 = new QAction(IOGraphDialog);
        actionMoveDown1->setObjectName(QStringLiteral("actionMoveDown1"));
        actionGoToPacket = new QAction(IOGraphDialog);
        actionGoToPacket->setObjectName(QStringLiteral("actionGoToPacket"));
        actionDragZoom = new QAction(IOGraphDialog);
        actionDragZoom->setObjectName(QStringLiteral("actionDragZoom"));
        actionToggleTimeOrigin = new QAction(IOGraphDialog);
        actionToggleTimeOrigin->setObjectName(QStringLiteral("actionToggleTimeOrigin"));
        actionCrosshairs = new QAction(IOGraphDialog);
        actionCrosshairs->setObjectName(QStringLiteral("actionCrosshairs"));
        actionZoomInX = new QAction(IOGraphDialog);
        actionZoomInX->setObjectName(QStringLiteral("actionZoomInX"));
        actionZoomOutX = new QAction(IOGraphDialog);
        actionZoomOutX->setObjectName(QStringLiteral("actionZoomOutX"));
        actionZoomInY = new QAction(IOGraphDialog);
        actionZoomInY->setObjectName(QStringLiteral("actionZoomInY"));
        actionZoomOutY = new QAction(IOGraphDialog);
        actionZoomOutY->setObjectName(QStringLiteral("actionZoomOutY"));
        verticalLayout_2 = new QVBoxLayout(IOGraphDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        splitter = new QSplitter(IOGraphDialog);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        widget = new QWidget(splitter);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        ioPlot = new QCustomPlot(widget);
        ioPlot->setObjectName(QStringLiteral("ioPlot"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(90);
        sizePolicy.setHeightForWidth(ioPlot->sizePolicy().hasHeightForWidth());
        ioPlot->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(ioPlot);

        hintLabel = new ElidedLabel(widget);
        hintLabel->setObjectName(QStringLiteral("hintLabel"));

        verticalLayout->addWidget(hintLabel);

        splitter->addWidget(widget);
        graphUat = new TabnavTreeView(splitter);
        graphUat->setObjectName(QStringLiteral("graphUat"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graphUat->sizePolicy().hasHeightForWidth());
        graphUat->setSizePolicy(sizePolicy1);
        splitter->addWidget(graphUat);

        verticalLayout_2->addWidget(splitter);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        newToolButton = new StockIconToolButton(IOGraphDialog);
        newToolButton->setObjectName(QStringLiteral("newToolButton"));

        horizontalLayout->addWidget(newToolButton);

        deleteToolButton = new StockIconToolButton(IOGraphDialog);
        deleteToolButton->setObjectName(QStringLiteral("deleteToolButton"));

        horizontalLayout->addWidget(deleteToolButton);

        copyToolButton = new StockIconToolButton(IOGraphDialog);
        copyToolButton->setObjectName(QStringLiteral("copyToolButton"));

        horizontalLayout->addWidget(copyToolButton);

        clearToolButton = new StockIconToolButton(IOGraphDialog);
        clearToolButton->setObjectName(QStringLiteral("clearToolButton"));
        clearToolButton->setEnabled(false);

        horizontalLayout->addWidget(clearToolButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        mouseLabel = new QLabel(IOGraphDialog);
        mouseLabel->setObjectName(QStringLiteral("mouseLabel"));

        horizontalLayout->addWidget(mouseLabel);

        dragRadioButton = new QRadioButton(IOGraphDialog);
        dragRadioButton->setObjectName(QStringLiteral("dragRadioButton"));
        dragRadioButton->setCheckable(true);

        horizontalLayout->addWidget(dragRadioButton);

        zoomRadioButton = new QRadioButton(IOGraphDialog);
        zoomRadioButton->setObjectName(QStringLiteral("zoomRadioButton"));
        zoomRadioButton->setCheckable(true);

        horizontalLayout->addWidget(zoomRadioButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        label_2 = new QLabel(IOGraphDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        intervalComboBox = new QComboBox(IOGraphDialog);
        intervalComboBox->setObjectName(QStringLiteral("intervalComboBox"));

        horizontalLayout->addWidget(intervalComboBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        todCheckBox = new QCheckBox(IOGraphDialog);
        todCheckBox->setObjectName(QStringLiteral("todCheckBox"));

        horizontalLayout->addWidget(todCheckBox);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        logCheckBox = new QCheckBox(IOGraphDialog);
        logCheckBox->setObjectName(QStringLiteral("logCheckBox"));

        horizontalLayout->addWidget(logCheckBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        resetButton = new QPushButton(IOGraphDialog);
        resetButton->setObjectName(QStringLiteral("resetButton"));

        horizontalLayout->addWidget(resetButton);


        verticalLayout_2->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(IOGraphDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Help|QDialogButtonBox::Save);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(IOGraphDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), IOGraphDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), IOGraphDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(IOGraphDialog);
    } // setupUi

    void retranslateUi(QDialog *IOGraphDialog)
    {
        IOGraphDialog->setWindowTitle(QApplication::translate("IOGraphDialog", "Dialog", Q_NULLPTR));
        actionReset->setText(QApplication::translate("IOGraphDialog", "Reset Graph", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionReset->setToolTip(QApplication::translate("IOGraphDialog", "Reset the graph to its initial state.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionReset->setShortcut(QApplication::translate("IOGraphDialog", "0", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionZoomIn->setText(QApplication::translate("IOGraphDialog", "Zoom In", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionZoomIn->setToolTip(QApplication::translate("IOGraphDialog", "Zoom In", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionZoomIn->setShortcut(QApplication::translate("IOGraphDialog", "+", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionZoomOut->setText(QApplication::translate("IOGraphDialog", "Zoom Out", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionZoomOut->setToolTip(QApplication::translate("IOGraphDialog", "Zoom Out", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionZoomOut->setShortcut(QApplication::translate("IOGraphDialog", "-", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveUp10->setText(QApplication::translate("IOGraphDialog", "Move Up 10 Pixels", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveUp10->setToolTip(QApplication::translate("IOGraphDialog", "Move Up 10 Pixels", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveUp10->setShortcut(QApplication::translate("IOGraphDialog", "Up", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveLeft10->setText(QApplication::translate("IOGraphDialog", "Move Left 10 Pixels", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveLeft10->setToolTip(QApplication::translate("IOGraphDialog", "Move Left 10 Pixels", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveLeft10->setShortcut(QApplication::translate("IOGraphDialog", "Left", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveRight10->setText(QApplication::translate("IOGraphDialog", "Move Right 10 Pixels", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveRight10->setToolTip(QApplication::translate("IOGraphDialog", "Move Right 10 Pixels", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveRight10->setShortcut(QApplication::translate("IOGraphDialog", "Right", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveDown10->setText(QApplication::translate("IOGraphDialog", "Move Down 10 Pixels", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveDown10->setToolTip(QApplication::translate("IOGraphDialog", "Move Down 10 Pixels", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveDown10->setShortcut(QApplication::translate("IOGraphDialog", "Down", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveUp1->setText(QApplication::translate("IOGraphDialog", "Move Up 1 Pixel", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveUp1->setToolTip(QApplication::translate("IOGraphDialog", "Move Up 1 Pixel", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveUp1->setShortcut(QApplication::translate("IOGraphDialog", "Shift+Up", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveLeft1->setText(QApplication::translate("IOGraphDialog", "Move Left 1 Pixel", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveLeft1->setToolTip(QApplication::translate("IOGraphDialog", "Move Left 1 Pixel", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveLeft1->setShortcut(QApplication::translate("IOGraphDialog", "Shift+Left", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveRight1->setText(QApplication::translate("IOGraphDialog", "Move Right 1 Pixel", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveRight1->setToolTip(QApplication::translate("IOGraphDialog", "Move Right 1 Pixel", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveRight1->setShortcut(QApplication::translate("IOGraphDialog", "Shift+Right", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionMoveDown1->setText(QApplication::translate("IOGraphDialog", "Move Down 1 Pixel", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionMoveDown1->setToolTip(QApplication::translate("IOGraphDialog", "Move down 1 Pixel", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionMoveDown1->setShortcut(QApplication::translate("IOGraphDialog", "Shift+Down", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionGoToPacket->setText(QApplication::translate("IOGraphDialog", "Go To Packet Under Cursor", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionGoToPacket->setToolTip(QApplication::translate("IOGraphDialog", "Go to packet currently under the cursor", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionGoToPacket->setShortcut(QApplication::translate("IOGraphDialog", "G", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionDragZoom->setText(QApplication::translate("IOGraphDialog", "Drag / Zoom", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionDragZoom->setToolTip(QApplication::translate("IOGraphDialog", "Toggle mouse drag / zoom behavior", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionDragZoom->setShortcut(QApplication::translate("IOGraphDialog", "Z", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionToggleTimeOrigin->setText(QApplication::translate("IOGraphDialog", "Capture / Session Time Origin", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionToggleTimeOrigin->setToolTip(QApplication::translate("IOGraphDialog", "Toggle capture / session time origin", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionToggleTimeOrigin->setShortcut(QApplication::translate("IOGraphDialog", "T", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionCrosshairs->setText(QApplication::translate("IOGraphDialog", "Crosshairs", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionCrosshairs->setToolTip(QApplication::translate("IOGraphDialog", "Toggle crosshairs", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionCrosshairs->setShortcut(QApplication::translate("IOGraphDialog", "Space", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionZoomInX->setText(QApplication::translate("IOGraphDialog", "Zoom In X Axis", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionZoomInX->setToolTip(QApplication::translate("IOGraphDialog", "Zoom In X Axis", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionZoomInX->setShortcut(QApplication::translate("IOGraphDialog", "X", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionZoomOutX->setText(QApplication::translate("IOGraphDialog", "Zoom Out X Axis", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionZoomOutX->setToolTip(QApplication::translate("IOGraphDialog", "Zoom Out X Axis", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionZoomOutX->setShortcut(QApplication::translate("IOGraphDialog", "Shift+X", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionZoomInY->setText(QApplication::translate("IOGraphDialog", "Zoom In Y Axis", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionZoomInY->setToolTip(QApplication::translate("IOGraphDialog", "Zoom In Y Axis", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionZoomInY->setShortcut(QApplication::translate("IOGraphDialog", "Y", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionZoomOutY->setText(QApplication::translate("IOGraphDialog", "Zoom Out Y Axis", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionZoomOutY->setToolTip(QApplication::translate("IOGraphDialog", "Zoom Out Y Axis", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionZoomOutY->setShortcut(QApplication::translate("IOGraphDialog", "Shift+Y", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        hintLabel->setToolTip(QApplication::translate("IOGraphDialog", "<html><head/><body>\n"
"\n"
"<h3>Valuable and amazing time-saving keyboard shortcuts</h3>\n"
"<table><tbody>\n"
"\n"
"<tr><th>+</th><td>Zoom in</td></th>\n"
"<tr><th>-</th><td>Zoom out</td></th>\n"
"<tr><th>x</th><td>Zoom in X axis</td></th>\n"
"<tr><th>X</th><td>Zoom out X axis</td></th>\n"
"<tr><th>y</th><td>Zoom in Y axis</td></th>\n"
"<tr><th>Y</th><td>Zoom out Y axis</td></th>\n"
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
"<tr><th>g</th><"
                        "td>Go to packet under cursor</td></th>\n"
"\n"
"<tr><th>z</th><td>Toggle mouse drag / zoom</td></th>\n"
"<tr><th>t</th><td>Toggle capture / session time origin</td></th>\n"
"<tr><th>Space</th><td>Toggle crosshairs</td></th>\n"
"\n"
"</tbody></table>\n"
"</body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        hintLabel->setText(QString());
#ifndef QT_NO_TOOLTIP
        newToolButton->setToolTip(QApplication::translate("IOGraphDialog", "Add a new graph.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        newToolButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        deleteToolButton->setToolTip(QApplication::translate("IOGraphDialog", "Remove this graph.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        copyToolButton->setToolTip(QApplication::translate("IOGraphDialog", "Duplicate this graph.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        copyToolButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        clearToolButton->setToolTip(QApplication::translate("IOGraphDialog", "Clear all graphs.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        mouseLabel->setText(QApplication::translate("IOGraphDialog", "Mouse", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        dragRadioButton->setToolTip(QApplication::translate("IOGraphDialog", "Drag using the mouse button.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        dragRadioButton->setText(QApplication::translate("IOGraphDialog", "drags", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        zoomRadioButton->setToolTip(QApplication::translate("IOGraphDialog", "Select using the mouse button.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        zoomRadioButton->setText(QApplication::translate("IOGraphDialog", "zooms", Q_NULLPTR));
        label_2->setText(QApplication::translate("IOGraphDialog", "Interval", Q_NULLPTR));
        todCheckBox->setText(QApplication::translate("IOGraphDialog", "Time of day", Q_NULLPTR));
        logCheckBox->setText(QApplication::translate("IOGraphDialog", "Log scale", Q_NULLPTR));
        resetButton->setText(QApplication::translate("IOGraphDialog", "Reset", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class IOGraphDialog: public Ui_IOGraphDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IO_GRAPH_DIALOG_H

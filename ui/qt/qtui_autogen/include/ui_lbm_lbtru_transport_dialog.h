/********************************************************************************
** Form generated from reading UI file 'lbm_lbtru_transport_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LBM_LBTRU_TRANSPORT_DIALOG_H
#define UI_LBM_LBTRU_TRANSPORT_DIALOG_H

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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "widgets/display_filter_edit.h"

QT_BEGIN_NAMESPACE

class Ui_LBMLBTRUTransportDialog
{
public:
    QAction *actionCopyAsCSV;
    QAction *actionCopyAsYAML;
    QAction *action_SourceDataFrames;
    QAction *action_SourceDataBytes;
    QAction *action_SourceDataFramesBytes;
    QAction *action_SourceDataRate;
    QAction *action_SourceRXDataFrames;
    QAction *action_SourceRXDataBytes;
    QAction *action_SourceRXDataFramesBytes;
    QAction *action_SourceRXDataRate;
    QAction *action_SourceNCFFrames;
    QAction *action_SourceNCFCount;
    QAction *action_SourceNCFBytes;
    QAction *action_SourceNCFFramesBytes;
    QAction *action_SourceNCFCountBytes;
    QAction *action_SourceNCFFramesCount;
    QAction *action_SourceNCFFramesCountBytes;
    QAction *action_SourceSMFrames;
    QAction *action_SourceSMBytes;
    QAction *action_SourceSMFramesBytes;
    QAction *action_SourceSMRate;
    QAction *action_SourceRSTFrames;
    QAction *action_SourceRSTBytes;
    QAction *action_SourceRSTFramesBytes;
    QAction *action_SourceRSTRate;
    QAction *action_ReceiverNAKFrames;
    QAction *action_ReceiverNAKCount;
    QAction *action_ReceiverNAKBytes;
    QAction *action_ReceiverNAKFramesCount;
    QAction *action_ReceiverNAKCountBytes;
    QAction *action_ReceiverNAKFramesBytes;
    QAction *action_ReceiverNAKFramesCountBytes;
    QAction *action_ReceiverNAKRate;
    QAction *action_ReceiverACKFrames;
    QAction *action_ReceiverACKBytes;
    QAction *action_ReceiverACKFramesBytes;
    QAction *action_ReceiverACKRate;
    QAction *action_ReceiverCREQFrames;
    QAction *action_ReceiverCREQBytes;
    QAction *action_ReceiverCREQFramesBytes;
    QAction *action_ReceiverCREQRate;
    QAction *action_SourceAutoResizeColumns;
    QAction *action_ReceiverAutoResizeColumns;
    QAction *action_SourceNCFRate;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *sourcesTab;
    QHBoxLayout *horizontalLayout_5;
    QSplitter *splitter;
    QTreeWidget *sources_TreeWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *sources_detail_ComboBox;
    QLabel *label_3;
    QLabel *sources_detail_transport_Label;
    QSpacerItem *horizontalSpacer;
    QStackedWidget *sources_stackedWidget;
    QWidget *sources_detail_sqn_page;
    QHBoxLayout *horizontalLayout_4;
    QTreeWidget *sources_detail_sqn_TreeWidget;
    QWidget *sources_detail_rst_page;
    QVBoxLayout *verticalLayout_4;
    QTreeWidget *sources_detail_rst_TreeWidget;
    QWidget *sources_detail_ncf_sqn_page;
    QHBoxLayout *horizontalLayout_6;
    QTreeWidget *sources_detail_ncf_sqn_TreeWidget;
    QWidget *receiversTab;
    QHBoxLayout *horizontalLayout_9;
    QSplitter *splitter_2;
    QTreeWidget *receivers_TreeWidget;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QComboBox *receivers_detail_ComboBox;
    QLabel *label_5;
    QLabel *receivers_detail_transport_Label;
    QSpacerItem *horizontalSpacer_2;
    QStackedWidget *receivers_stackedWidget;
    QWidget *receivers_detail_sqn_page;
    QHBoxLayout *horizontalLayout_7;
    QTreeWidget *receivers_detail_sqn_TreeWidget;
    QWidget *receivers_detail_reason_page;
    QHBoxLayout *horizontalLayout_8;
    QTreeWidget *receivers_detail_reason_TreeWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    DisplayFilterEdit *displayFilterLineEdit;
    QPushButton *applyFilterButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *LBMLBTRUTransportDialog)
    {
        if (LBMLBTRUTransportDialog->objectName().isEmpty())
            LBMLBTRUTransportDialog->setObjectName(QStringLiteral("LBMLBTRUTransportDialog"));
        LBMLBTRUTransportDialog->resize(872, 667);
        LBMLBTRUTransportDialog->setSizeGripEnabled(true);
        actionCopyAsCSV = new QAction(LBMLBTRUTransportDialog);
        actionCopyAsCSV->setObjectName(QStringLiteral("actionCopyAsCSV"));
#ifndef QT_NO_SHORTCUT
        actionCopyAsCSV->setShortcut(QStringLiteral("Ctrl+C"));
#endif // QT_NO_SHORTCUT
        actionCopyAsYAML = new QAction(LBMLBTRUTransportDialog);
        actionCopyAsYAML->setObjectName(QStringLiteral("actionCopyAsYAML"));
#ifndef QT_NO_SHORTCUT
        actionCopyAsYAML->setShortcut(QStringLiteral("Ctrl+Y"));
#endif // QT_NO_SHORTCUT
        action_SourceDataFrames = new QAction(LBMLBTRUTransportDialog);
        action_SourceDataFrames->setObjectName(QStringLiteral("action_SourceDataFrames"));
        action_SourceDataFrames->setCheckable(true);
        action_SourceDataBytes = new QAction(LBMLBTRUTransportDialog);
        action_SourceDataBytes->setObjectName(QStringLiteral("action_SourceDataBytes"));
        action_SourceDataBytes->setCheckable(true);
        action_SourceDataFramesBytes = new QAction(LBMLBTRUTransportDialog);
        action_SourceDataFramesBytes->setObjectName(QStringLiteral("action_SourceDataFramesBytes"));
        action_SourceDataFramesBytes->setCheckable(true);
        action_SourceDataRate = new QAction(LBMLBTRUTransportDialog);
        action_SourceDataRate->setObjectName(QStringLiteral("action_SourceDataRate"));
        action_SourceDataRate->setCheckable(true);
        action_SourceRXDataFrames = new QAction(LBMLBTRUTransportDialog);
        action_SourceRXDataFrames->setObjectName(QStringLiteral("action_SourceRXDataFrames"));
        action_SourceRXDataFrames->setCheckable(true);
        action_SourceRXDataBytes = new QAction(LBMLBTRUTransportDialog);
        action_SourceRXDataBytes->setObjectName(QStringLiteral("action_SourceRXDataBytes"));
        action_SourceRXDataBytes->setCheckable(true);
        action_SourceRXDataFramesBytes = new QAction(LBMLBTRUTransportDialog);
        action_SourceRXDataFramesBytes->setObjectName(QStringLiteral("action_SourceRXDataFramesBytes"));
        action_SourceRXDataFramesBytes->setCheckable(true);
        action_SourceRXDataRate = new QAction(LBMLBTRUTransportDialog);
        action_SourceRXDataRate->setObjectName(QStringLiteral("action_SourceRXDataRate"));
        action_SourceRXDataRate->setCheckable(true);
        action_SourceNCFFrames = new QAction(LBMLBTRUTransportDialog);
        action_SourceNCFFrames->setObjectName(QStringLiteral("action_SourceNCFFrames"));
        action_SourceNCFFrames->setCheckable(true);
        action_SourceNCFCount = new QAction(LBMLBTRUTransportDialog);
        action_SourceNCFCount->setObjectName(QStringLiteral("action_SourceNCFCount"));
        action_SourceNCFCount->setCheckable(true);
        action_SourceNCFBytes = new QAction(LBMLBTRUTransportDialog);
        action_SourceNCFBytes->setObjectName(QStringLiteral("action_SourceNCFBytes"));
        action_SourceNCFBytes->setCheckable(true);
        action_SourceNCFFramesBytes = new QAction(LBMLBTRUTransportDialog);
        action_SourceNCFFramesBytes->setObjectName(QStringLiteral("action_SourceNCFFramesBytes"));
        action_SourceNCFFramesBytes->setCheckable(true);
        action_SourceNCFCountBytes = new QAction(LBMLBTRUTransportDialog);
        action_SourceNCFCountBytes->setObjectName(QStringLiteral("action_SourceNCFCountBytes"));
        action_SourceNCFCountBytes->setCheckable(true);
        action_SourceNCFFramesCount = new QAction(LBMLBTRUTransportDialog);
        action_SourceNCFFramesCount->setObjectName(QStringLiteral("action_SourceNCFFramesCount"));
        action_SourceNCFFramesCount->setCheckable(true);
        action_SourceNCFFramesCountBytes = new QAction(LBMLBTRUTransportDialog);
        action_SourceNCFFramesCountBytes->setObjectName(QStringLiteral("action_SourceNCFFramesCountBytes"));
        action_SourceNCFFramesCountBytes->setCheckable(true);
        action_SourceSMFrames = new QAction(LBMLBTRUTransportDialog);
        action_SourceSMFrames->setObjectName(QStringLiteral("action_SourceSMFrames"));
        action_SourceSMFrames->setCheckable(true);
        action_SourceSMBytes = new QAction(LBMLBTRUTransportDialog);
        action_SourceSMBytes->setObjectName(QStringLiteral("action_SourceSMBytes"));
        action_SourceSMBytes->setCheckable(true);
        action_SourceSMFramesBytes = new QAction(LBMLBTRUTransportDialog);
        action_SourceSMFramesBytes->setObjectName(QStringLiteral("action_SourceSMFramesBytes"));
        action_SourceSMFramesBytes->setCheckable(true);
        action_SourceSMRate = new QAction(LBMLBTRUTransportDialog);
        action_SourceSMRate->setObjectName(QStringLiteral("action_SourceSMRate"));
        action_SourceSMRate->setCheckable(true);
        action_SourceRSTFrames = new QAction(LBMLBTRUTransportDialog);
        action_SourceRSTFrames->setObjectName(QStringLiteral("action_SourceRSTFrames"));
        action_SourceRSTFrames->setCheckable(true);
        action_SourceRSTBytes = new QAction(LBMLBTRUTransportDialog);
        action_SourceRSTBytes->setObjectName(QStringLiteral("action_SourceRSTBytes"));
        action_SourceRSTBytes->setCheckable(true);
        action_SourceRSTFramesBytes = new QAction(LBMLBTRUTransportDialog);
        action_SourceRSTFramesBytes->setObjectName(QStringLiteral("action_SourceRSTFramesBytes"));
        action_SourceRSTFramesBytes->setCheckable(true);
        action_SourceRSTRate = new QAction(LBMLBTRUTransportDialog);
        action_SourceRSTRate->setObjectName(QStringLiteral("action_SourceRSTRate"));
        action_SourceRSTRate->setCheckable(true);
        action_ReceiverNAKFrames = new QAction(LBMLBTRUTransportDialog);
        action_ReceiverNAKFrames->setObjectName(QStringLiteral("action_ReceiverNAKFrames"));
        action_ReceiverNAKFrames->setCheckable(true);
        action_ReceiverNAKCount = new QAction(LBMLBTRUTransportDialog);
        action_ReceiverNAKCount->setObjectName(QStringLiteral("action_ReceiverNAKCount"));
        action_ReceiverNAKCount->setCheckable(true);
        action_ReceiverNAKBytes = new QAction(LBMLBTRUTransportDialog);
        action_ReceiverNAKBytes->setObjectName(QStringLiteral("action_ReceiverNAKBytes"));
        action_ReceiverNAKBytes->setCheckable(true);
        action_ReceiverNAKFramesCount = new QAction(LBMLBTRUTransportDialog);
        action_ReceiverNAKFramesCount->setObjectName(QStringLiteral("action_ReceiverNAKFramesCount"));
        action_ReceiverNAKFramesCount->setCheckable(true);
        action_ReceiverNAKCountBytes = new QAction(LBMLBTRUTransportDialog);
        action_ReceiverNAKCountBytes->setObjectName(QStringLiteral("action_ReceiverNAKCountBytes"));
        action_ReceiverNAKCountBytes->setCheckable(true);
        action_ReceiverNAKFramesBytes = new QAction(LBMLBTRUTransportDialog);
        action_ReceiverNAKFramesBytes->setObjectName(QStringLiteral("action_ReceiverNAKFramesBytes"));
        action_ReceiverNAKFramesBytes->setCheckable(true);
        action_ReceiverNAKFramesCountBytes = new QAction(LBMLBTRUTransportDialog);
        action_ReceiverNAKFramesCountBytes->setObjectName(QStringLiteral("action_ReceiverNAKFramesCountBytes"));
        action_ReceiverNAKFramesCountBytes->setCheckable(true);
        action_ReceiverNAKRate = new QAction(LBMLBTRUTransportDialog);
        action_ReceiverNAKRate->setObjectName(QStringLiteral("action_ReceiverNAKRate"));
        action_ReceiverNAKRate->setCheckable(true);
        action_ReceiverACKFrames = new QAction(LBMLBTRUTransportDialog);
        action_ReceiverACKFrames->setObjectName(QStringLiteral("action_ReceiverACKFrames"));
        action_ReceiverACKFrames->setCheckable(true);
        action_ReceiverACKBytes = new QAction(LBMLBTRUTransportDialog);
        action_ReceiverACKBytes->setObjectName(QStringLiteral("action_ReceiverACKBytes"));
        action_ReceiverACKBytes->setCheckable(true);
        action_ReceiverACKFramesBytes = new QAction(LBMLBTRUTransportDialog);
        action_ReceiverACKFramesBytes->setObjectName(QStringLiteral("action_ReceiverACKFramesBytes"));
        action_ReceiverACKFramesBytes->setCheckable(true);
        action_ReceiverACKRate = new QAction(LBMLBTRUTransportDialog);
        action_ReceiverACKRate->setObjectName(QStringLiteral("action_ReceiverACKRate"));
        action_ReceiverACKRate->setCheckable(true);
        action_ReceiverCREQFrames = new QAction(LBMLBTRUTransportDialog);
        action_ReceiverCREQFrames->setObjectName(QStringLiteral("action_ReceiverCREQFrames"));
        action_ReceiverCREQFrames->setCheckable(true);
        action_ReceiverCREQBytes = new QAction(LBMLBTRUTransportDialog);
        action_ReceiverCREQBytes->setObjectName(QStringLiteral("action_ReceiverCREQBytes"));
        action_ReceiverCREQBytes->setCheckable(true);
        action_ReceiverCREQFramesBytes = new QAction(LBMLBTRUTransportDialog);
        action_ReceiverCREQFramesBytes->setObjectName(QStringLiteral("action_ReceiverCREQFramesBytes"));
        action_ReceiverCREQFramesBytes->setCheckable(true);
        action_ReceiverCREQRate = new QAction(LBMLBTRUTransportDialog);
        action_ReceiverCREQRate->setObjectName(QStringLiteral("action_ReceiverCREQRate"));
        action_ReceiverCREQRate->setCheckable(true);
        action_SourceAutoResizeColumns = new QAction(LBMLBTRUTransportDialog);
        action_SourceAutoResizeColumns->setObjectName(QStringLiteral("action_SourceAutoResizeColumns"));
        action_ReceiverAutoResizeColumns = new QAction(LBMLBTRUTransportDialog);
        action_ReceiverAutoResizeColumns->setObjectName(QStringLiteral("action_ReceiverAutoResizeColumns"));
        action_SourceNCFRate = new QAction(LBMLBTRUTransportDialog);
        action_SourceNCFRate->setObjectName(QStringLiteral("action_SourceNCFRate"));
        action_SourceNCFRate->setCheckable(true);
        verticalLayout = new QVBoxLayout(LBMLBTRUTransportDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(LBMLBTRUTransportDialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        sourcesTab = new QWidget();
        sourcesTab->setObjectName(QStringLiteral("sourcesTab"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sourcesTab->sizePolicy().hasHeightForWidth());
        sourcesTab->setSizePolicy(sizePolicy);
        horizontalLayout_5 = new QHBoxLayout(sourcesTab);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        splitter = new QSplitter(sourcesTab);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        splitter->setHandleWidth(10);
        sources_TreeWidget = new QTreeWidget(splitter);
        sources_TreeWidget->setObjectName(QStringLiteral("sources_TreeWidget"));
        sizePolicy.setHeightForWidth(sources_TreeWidget->sizePolicy().hasHeightForWidth());
        sources_TreeWidget->setSizePolicy(sizePolicy);
        sources_TreeWidget->setMaximumSize(QSize(16777215, 16777215));
        splitter->addWidget(sources_TreeWidget);
        sources_TreeWidget->header()->setDefaultSectionSize(80);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        sources_detail_ComboBox = new QComboBox(layoutWidget);
        sources_detail_ComboBox->setObjectName(QStringLiteral("sources_detail_ComboBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(sources_detail_ComboBox->sizePolicy().hasHeightForWidth());
        sources_detail_ComboBox->setSizePolicy(sizePolicy1);
        sources_detail_ComboBox->setMinimumSize(QSize(120, 0));

        horizontalLayout_2->addWidget(sources_detail_ComboBox);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        sources_detail_transport_Label = new QLabel(layoutWidget);
        sources_detail_transport_Label->setObjectName(QStringLiteral("sources_detail_transport_Label"));

        horizontalLayout_2->addWidget(sources_detail_transport_Label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_2);

        sources_stackedWidget = new QStackedWidget(layoutWidget);
        sources_stackedWidget->setObjectName(QStringLiteral("sources_stackedWidget"));
        sources_stackedWidget->setEnabled(true);
        sources_stackedWidget->setFrameShape(QFrame::NoFrame);
        sources_stackedWidget->setLineWidth(1);
        sources_detail_sqn_page = new QWidget();
        sources_detail_sqn_page->setObjectName(QStringLiteral("sources_detail_sqn_page"));
        horizontalLayout_4 = new QHBoxLayout(sources_detail_sqn_page);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        sources_detail_sqn_TreeWidget = new QTreeWidget(sources_detail_sqn_page);
        sources_detail_sqn_TreeWidget->setObjectName(QStringLiteral("sources_detail_sqn_TreeWidget"));

        horizontalLayout_4->addWidget(sources_detail_sqn_TreeWidget);

        sources_stackedWidget->addWidget(sources_detail_sqn_page);
        sources_detail_rst_page = new QWidget();
        sources_detail_rst_page->setObjectName(QStringLiteral("sources_detail_rst_page"));
        verticalLayout_4 = new QVBoxLayout(sources_detail_rst_page);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        sources_detail_rst_TreeWidget = new QTreeWidget(sources_detail_rst_page);
        sources_detail_rst_TreeWidget->setObjectName(QStringLiteral("sources_detail_rst_TreeWidget"));

        verticalLayout_4->addWidget(sources_detail_rst_TreeWidget);

        sources_stackedWidget->addWidget(sources_detail_rst_page);
        sources_detail_ncf_sqn_page = new QWidget();
        sources_detail_ncf_sqn_page->setObjectName(QStringLiteral("sources_detail_ncf_sqn_page"));
        horizontalLayout_6 = new QHBoxLayout(sources_detail_ncf_sqn_page);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        sources_detail_ncf_sqn_TreeWidget = new QTreeWidget(sources_detail_ncf_sqn_page);
        sources_detail_ncf_sqn_TreeWidget->setObjectName(QStringLiteral("sources_detail_ncf_sqn_TreeWidget"));

        horizontalLayout_6->addWidget(sources_detail_ncf_sqn_TreeWidget);

        sources_stackedWidget->addWidget(sources_detail_ncf_sqn_page);

        verticalLayout_2->addWidget(sources_stackedWidget);

        splitter->addWidget(layoutWidget);

        horizontalLayout_5->addWidget(splitter);

        tabWidget->addTab(sourcesTab, QString());
        receiversTab = new QWidget();
        receiversTab->setObjectName(QStringLiteral("receiversTab"));
        sizePolicy.setHeightForWidth(receiversTab->sizePolicy().hasHeightForWidth());
        receiversTab->setSizePolicy(sizePolicy);
        horizontalLayout_9 = new QHBoxLayout(receiversTab);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        splitter_2 = new QSplitter(receiversTab);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        splitter_2->setHandleWidth(10);
        receivers_TreeWidget = new QTreeWidget(splitter_2);
        receivers_TreeWidget->setObjectName(QStringLiteral("receivers_TreeWidget"));
        splitter_2->addWidget(receivers_TreeWidget);
        layoutWidget_2 = new QWidget(splitter_2);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        verticalLayout_3 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_4 = new QLabel(layoutWidget_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        receivers_detail_ComboBox = new QComboBox(layoutWidget_2);
        receivers_detail_ComboBox->setObjectName(QStringLiteral("receivers_detail_ComboBox"));
        receivers_detail_ComboBox->setMinimumSize(QSize(130, 0));

        horizontalLayout_3->addWidget(receivers_detail_ComboBox);

        label_5 = new QLabel(layoutWidget_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);

        receivers_detail_transport_Label = new QLabel(layoutWidget_2);
        receivers_detail_transport_Label->setObjectName(QStringLiteral("receivers_detail_transport_Label"));

        horizontalLayout_3->addWidget(receivers_detail_transport_Label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_3);

        receivers_stackedWidget = new QStackedWidget(layoutWidget_2);
        receivers_stackedWidget->setObjectName(QStringLiteral("receivers_stackedWidget"));
        sizePolicy.setHeightForWidth(receivers_stackedWidget->sizePolicy().hasHeightForWidth());
        receivers_stackedWidget->setSizePolicy(sizePolicy);
        receivers_detail_sqn_page = new QWidget();
        receivers_detail_sqn_page->setObjectName(QStringLiteral("receivers_detail_sqn_page"));
        sizePolicy.setHeightForWidth(receivers_detail_sqn_page->sizePolicy().hasHeightForWidth());
        receivers_detail_sqn_page->setSizePolicy(sizePolicy);
        horizontalLayout_7 = new QHBoxLayout(receivers_detail_sqn_page);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        receivers_detail_sqn_TreeWidget = new QTreeWidget(receivers_detail_sqn_page);
        receivers_detail_sqn_TreeWidget->setObjectName(QStringLiteral("receivers_detail_sqn_TreeWidget"));

        horizontalLayout_7->addWidget(receivers_detail_sqn_TreeWidget);

        receivers_stackedWidget->addWidget(receivers_detail_sqn_page);
        receivers_detail_reason_page = new QWidget();
        receivers_detail_reason_page->setObjectName(QStringLiteral("receivers_detail_reason_page"));
        sizePolicy.setHeightForWidth(receivers_detail_reason_page->sizePolicy().hasHeightForWidth());
        receivers_detail_reason_page->setSizePolicy(sizePolicy);
        horizontalLayout_8 = new QHBoxLayout(receivers_detail_reason_page);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        receivers_detail_reason_TreeWidget = new QTreeWidget(receivers_detail_reason_page);
        receivers_detail_reason_TreeWidget->setObjectName(QStringLiteral("receivers_detail_reason_TreeWidget"));

        horizontalLayout_8->addWidget(receivers_detail_reason_TreeWidget);

        receivers_stackedWidget->addWidget(receivers_detail_reason_page);

        verticalLayout_3->addWidget(receivers_stackedWidget);

        splitter_2->addWidget(layoutWidget_2);

        horizontalLayout_9->addWidget(splitter_2);

        tabWidget->addTab(receiversTab, QString());

        verticalLayout->addWidget(tabWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 0, -1, -1);
        label = new QLabel(LBMLBTRUTransportDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        displayFilterLineEdit = new DisplayFilterEdit(LBMLBTRUTransportDialog);
        displayFilterLineEdit->setObjectName(QStringLiteral("displayFilterLineEdit"));

        horizontalLayout->addWidget(displayFilterLineEdit);

        applyFilterButton = new QPushButton(LBMLBTRUTransportDialog);
        applyFilterButton->setObjectName(QStringLiteral("applyFilterButton"));

        horizontalLayout->addWidget(applyFilterButton);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(LBMLBTRUTransportDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Help);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(LBMLBTRUTransportDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), LBMLBTRUTransportDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), LBMLBTRUTransportDialog, SLOT(reject()));
        QObject::connect(sources_detail_ComboBox, SIGNAL(currentIndexChanged(int)), LBMLBTRUTransportDialog, SLOT(sourcesDetailCurrentChanged(int)));
        QObject::connect(sources_TreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), LBMLBTRUTransportDialog, SLOT(sourcesItemClicked(QTreeWidgetItem*,int)));
        QObject::connect(sources_detail_sqn_TreeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), LBMLBTRUTransportDialog, SLOT(sourcesDetailItemDoubleClicked(QTreeWidgetItem*,int)));
        QObject::connect(sources_detail_ncf_sqn_TreeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), LBMLBTRUTransportDialog, SLOT(sourcesDetailItemDoubleClicked(QTreeWidgetItem*,int)));
        QObject::connect(receivers_TreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), LBMLBTRUTransportDialog, SLOT(receiversItemClicked(QTreeWidgetItem*,int)));
        QObject::connect(receivers_detail_ComboBox, SIGNAL(currentIndexChanged(int)), LBMLBTRUTransportDialog, SLOT(receiversDetailCurrentChanged(int)));
        QObject::connect(receivers_detail_sqn_TreeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), LBMLBTRUTransportDialog, SLOT(receiversDetailItemDoubleClicked(QTreeWidgetItem*,int)));
        QObject::connect(receivers_detail_reason_TreeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), LBMLBTRUTransportDialog, SLOT(receiversDetailItemDoubleClicked(QTreeWidgetItem*,int)));

        tabWidget->setCurrentIndex(0);
        sources_stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(LBMLBTRUTransportDialog);
    } // setupUi

    void retranslateUi(QDialog *LBMLBTRUTransportDialog)
    {
        LBMLBTRUTransportDialog->setWindowTitle(QApplication::translate("LBMLBTRUTransportDialog", "LBT-RU Transport Statistics", Q_NULLPTR));
        actionCopyAsCSV->setText(QApplication::translate("LBMLBTRUTransportDialog", "Copy as CSV", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionCopyAsCSV->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Copy the tree as CSV", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionCopyAsYAML->setText(QApplication::translate("LBMLBTRUTransportDialog", "Copy as YAML", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionCopyAsYAML->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Copy the tree as YAML", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceDataFrames->setText(QApplication::translate("LBMLBTRUTransportDialog", "Data frames", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceDataFrames->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the data frames column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceDataBytes->setText(QApplication::translate("LBMLBTRUTransportDialog", "Data bytes", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceDataBytes->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the data bytes column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceDataFramesBytes->setText(QApplication::translate("LBMLBTRUTransportDialog", "Data frames/bytes", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceDataFramesBytes->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the data frames/bytes column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceDataRate->setText(QApplication::translate("LBMLBTRUTransportDialog", "Data rate", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceDataRate->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the data rate column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceRXDataFrames->setText(QApplication::translate("LBMLBTRUTransportDialog", "RX data frames", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceRXDataFrames->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the RX data frames column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceRXDataBytes->setText(QApplication::translate("LBMLBTRUTransportDialog", "RX data bytes", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceRXDataBytes->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the RX data bytes column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceRXDataFramesBytes->setText(QApplication::translate("LBMLBTRUTransportDialog", "RX data frames/bytes", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceRXDataFramesBytes->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the RX data frames/bytes column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceRXDataRate->setText(QApplication::translate("LBMLBTRUTransportDialog", "RX data rate", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceRXDataRate->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the RX data rate column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceNCFFrames->setText(QApplication::translate("LBMLBTRUTransportDialog", "NCF frames", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceNCFFrames->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the NCF frames column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceNCFCount->setText(QApplication::translate("LBMLBTRUTransportDialog", "NCF count", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceNCFCount->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the NCF count column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceNCFBytes->setText(QApplication::translate("LBMLBTRUTransportDialog", "NCF bytes", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceNCFBytes->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the NCF bytes column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceNCFFramesBytes->setText(QApplication::translate("LBMLBTRUTransportDialog", "NCF frames/bytes", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceNCFFramesBytes->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the NCF frames/bytes column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceNCFCountBytes->setText(QApplication::translate("LBMLBTRUTransportDialog", "NCF count/bytes", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceNCFCountBytes->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the NCF count/bytes column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceNCFFramesCount->setText(QApplication::translate("LBMLBTRUTransportDialog", "NCF frames/count", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceNCFFramesCount->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the NCF frames/count column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceNCFFramesCountBytes->setText(QApplication::translate("LBMLBTRUTransportDialog", "NCF frames/count/bytes", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceNCFFramesCountBytes->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the NCF frames/count/bytes column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceSMFrames->setText(QApplication::translate("LBMLBTRUTransportDialog", "SM frames", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceSMFrames->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the SM frames column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceSMBytes->setText(QApplication::translate("LBMLBTRUTransportDialog", "SM bytes", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceSMBytes->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the SM bytes column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceSMFramesBytes->setText(QApplication::translate("LBMLBTRUTransportDialog", "SM frames/bytes", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceSMFramesBytes->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the SM frames/bytes column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceSMRate->setText(QApplication::translate("LBMLBTRUTransportDialog", "SM rate", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceSMRate->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the SM rate column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceRSTFrames->setText(QApplication::translate("LBMLBTRUTransportDialog", "RST frames", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceRSTFrames->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the RST frames column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceRSTBytes->setText(QApplication::translate("LBMLBTRUTransportDialog", "RST bytes", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceRSTBytes->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the RST bytes column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceRSTFramesBytes->setText(QApplication::translate("LBMLBTRUTransportDialog", "RST frames/bytes", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceRSTFramesBytes->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the RST frames/bytes column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceRSTRate->setText(QApplication::translate("LBMLBTRUTransportDialog", "RST rate", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceRSTRate->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the RST rate column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_ReceiverNAKFrames->setText(QApplication::translate("LBMLBTRUTransportDialog", "NAK frames", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_ReceiverNAKFrames->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the NAK frames column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_ReceiverNAKCount->setText(QApplication::translate("LBMLBTRUTransportDialog", "NAK count", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_ReceiverNAKCount->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the NAK count column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_ReceiverNAKBytes->setText(QApplication::translate("LBMLBTRUTransportDialog", "NAK bytes", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_ReceiverNAKBytes->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the NAK bytes column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_ReceiverNAKFramesCount->setText(QApplication::translate("LBMLBTRUTransportDialog", "NAK frames/count", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_ReceiverNAKFramesCount->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the NAK frames/count column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_ReceiverNAKCountBytes->setText(QApplication::translate("LBMLBTRUTransportDialog", "NAK count/bytes", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_ReceiverNAKCountBytes->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the NAK count/bytes column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_ReceiverNAKFramesBytes->setText(QApplication::translate("LBMLBTRUTransportDialog", "NAK frames/bytes", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_ReceiverNAKFramesBytes->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the NAK frames/bytes column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_ReceiverNAKFramesCountBytes->setText(QApplication::translate("LBMLBTRUTransportDialog", "NAK frames/count/bytes", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_ReceiverNAKFramesCountBytes->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the NAK frames/count/bytes column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_ReceiverNAKRate->setText(QApplication::translate("LBMLBTRUTransportDialog", "NAK rate", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_ReceiverNAKRate->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the NAK rate column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_ReceiverACKFrames->setText(QApplication::translate("LBMLBTRUTransportDialog", "ACK frames", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_ReceiverACKFrames->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the ACK frames column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_ReceiverACKBytes->setText(QApplication::translate("LBMLBTRUTransportDialog", "ACK bytes", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_ReceiverACKBytes->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the ACK bytes column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_ReceiverACKFramesBytes->setText(QApplication::translate("LBMLBTRUTransportDialog", "ACK frames/bytes", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_ReceiverACKFramesBytes->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the ACK frames/bytes column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_ReceiverACKRate->setText(QApplication::translate("LBMLBTRUTransportDialog", "ACK rate", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_ReceiverACKRate->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the ACK rate column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_ReceiverCREQFrames->setText(QApplication::translate("LBMLBTRUTransportDialog", "CREQ frames", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_ReceiverCREQFrames->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the CREQ frames column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_ReceiverCREQBytes->setText(QApplication::translate("LBMLBTRUTransportDialog", "CREQ bytes", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_ReceiverCREQBytes->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the CREQ bytes column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_ReceiverCREQFramesBytes->setText(QApplication::translate("LBMLBTRUTransportDialog", "CREQ frames/bytes", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_ReceiverCREQFramesBytes->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the CREQ frames/bytes column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_ReceiverCREQRate->setText(QApplication::translate("LBMLBTRUTransportDialog", "CREQ rate", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_ReceiverCREQRate->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the CREQ rate column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceAutoResizeColumns->setText(QApplication::translate("LBMLBTRUTransportDialog", "Auto-resize columns to content", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceAutoResizeColumns->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Resize columns to content size", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_ReceiverAutoResizeColumns->setText(QApplication::translate("LBMLBTRUTransportDialog", "Auto-resize columns to content", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_ReceiverAutoResizeColumns->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Resize columns to content size", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_SourceNCFRate->setText(QApplication::translate("LBMLBTRUTransportDialog", "NCF rate", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_SourceNCFRate->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Show the NCF rate column", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        QTreeWidgetItem *___qtreewidgetitem = sources_TreeWidget->headerItem();
        ___qtreewidgetitem->setText(24, QApplication::translate("LBMLBTRUTransportDialog", "RST rate", Q_NULLPTR));
        ___qtreewidgetitem->setText(23, QApplication::translate("LBMLBTRUTransportDialog", "RST frames/bytes", Q_NULLPTR));
        ___qtreewidgetitem->setText(22, QApplication::translate("LBMLBTRUTransportDialog", "RST bytes", Q_NULLPTR));
        ___qtreewidgetitem->setText(21, QApplication::translate("LBMLBTRUTransportDialog", "RST frames", Q_NULLPTR));
        ___qtreewidgetitem->setText(20, QApplication::translate("LBMLBTRUTransportDialog", "SM rate", Q_NULLPTR));
        ___qtreewidgetitem->setText(19, QApplication::translate("LBMLBTRUTransportDialog", "SM frames/bytes", Q_NULLPTR));
        ___qtreewidgetitem->setText(18, QApplication::translate("LBMLBTRUTransportDialog", "SM bytes", Q_NULLPTR));
        ___qtreewidgetitem->setText(17, QApplication::translate("LBMLBTRUTransportDialog", "SM frames", Q_NULLPTR));
        ___qtreewidgetitem->setText(16, QApplication::translate("LBMLBTRUTransportDialog", "NCF rate", Q_NULLPTR));
        ___qtreewidgetitem->setText(15, QApplication::translate("LBMLBTRUTransportDialog", "NCF frames/count/bytes", Q_NULLPTR));
        ___qtreewidgetitem->setText(14, QApplication::translate("LBMLBTRUTransportDialog", "NCF count/bytes", Q_NULLPTR));
        ___qtreewidgetitem->setText(13, QApplication::translate("LBMLBTRUTransportDialog", "NCF frames/bytes", Q_NULLPTR));
        ___qtreewidgetitem->setText(12, QApplication::translate("LBMLBTRUTransportDialog", "NCF frames/count", Q_NULLPTR));
        ___qtreewidgetitem->setText(11, QApplication::translate("LBMLBTRUTransportDialog", "NCF bytes", Q_NULLPTR));
        ___qtreewidgetitem->setText(10, QApplication::translate("LBMLBTRUTransportDialog", "NCF count", Q_NULLPTR));
        ___qtreewidgetitem->setText(9, QApplication::translate("LBMLBTRUTransportDialog", "NCF frames", Q_NULLPTR));
        ___qtreewidgetitem->setText(8, QApplication::translate("LBMLBTRUTransportDialog", "RX data rate", Q_NULLPTR));
        ___qtreewidgetitem->setText(7, QApplication::translate("LBMLBTRUTransportDialog", "RX data frames/bytes", Q_NULLPTR));
        ___qtreewidgetitem->setText(6, QApplication::translate("LBMLBTRUTransportDialog", "RX data bytes", Q_NULLPTR));
        ___qtreewidgetitem->setText(5, QApplication::translate("LBMLBTRUTransportDialog", "RX data frames", Q_NULLPTR));
        ___qtreewidgetitem->setText(4, QApplication::translate("LBMLBTRUTransportDialog", "Data rate", Q_NULLPTR));
        ___qtreewidgetitem->setText(3, QApplication::translate("LBMLBTRUTransportDialog", "Data frames/bytes", Q_NULLPTR));
        ___qtreewidgetitem->setText(2, QApplication::translate("LBMLBTRUTransportDialog", "Data bytes", Q_NULLPTR));
        ___qtreewidgetitem->setText(1, QApplication::translate("LBMLBTRUTransportDialog", "Data frames", Q_NULLPTR));
        ___qtreewidgetitem->setText(0, QApplication::translate("LBMLBTRUTransportDialog", "Address/Transport/Client", Q_NULLPTR));
        label_2->setText(QApplication::translate("LBMLBTRUTransportDialog", "Show", Q_NULLPTR));
        sources_detail_ComboBox->clear();
        sources_detail_ComboBox->insertItems(0, QStringList()
         << QApplication::translate("LBMLBTRUTransportDialog", "Data SQN", Q_NULLPTR)
         << QApplication::translate("LBMLBTRUTransportDialog", "RX Data SQN", Q_NULLPTR)
         << QApplication::translate("LBMLBTRUTransportDialog", "NCF SQN", Q_NULLPTR)
         << QApplication::translate("LBMLBTRUTransportDialog", "SM SQN", Q_NULLPTR)
         << QApplication::translate("LBMLBTRUTransportDialog", "RST reason", Q_NULLPTR)
        );
        label_3->setText(QApplication::translate("LBMLBTRUTransportDialog", "details for transport", Q_NULLPTR));
        sources_detail_transport_Label->setText(QApplication::translate("LBMLBTRUTransportDialog", "XXXXX:XXX.XXX.XXX.XXX:XXXXX:XXXXXXXX:XXX.XXX.XXX.XXX:XXXXX", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem1 = sources_detail_sqn_TreeWidget->headerItem();
        ___qtreewidgetitem1->setText(2, QApplication::translate("LBMLBTRUTransportDialog", "Frame", Q_NULLPTR));
        ___qtreewidgetitem1->setText(1, QApplication::translate("LBMLBTRUTransportDialog", "Count", Q_NULLPTR));
        ___qtreewidgetitem1->setText(0, QApplication::translate("LBMLBTRUTransportDialog", "SQN", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem2 = sources_detail_rst_TreeWidget->headerItem();
        ___qtreewidgetitem2->setText(2, QApplication::translate("LBMLBTRUTransportDialog", "Frame", Q_NULLPTR));
        ___qtreewidgetitem2->setText(1, QApplication::translate("LBMLBTRUTransportDialog", "Count", Q_NULLPTR));
        ___qtreewidgetitem2->setText(0, QApplication::translate("LBMLBTRUTransportDialog", "Reason", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem3 = sources_detail_ncf_sqn_TreeWidget->headerItem();
        ___qtreewidgetitem3->setText(2, QApplication::translate("LBMLBTRUTransportDialog", "Frame", Q_NULLPTR));
        ___qtreewidgetitem3->setText(1, QApplication::translate("LBMLBTRUTransportDialog", "Count", Q_NULLPTR));
        ___qtreewidgetitem3->setText(0, QApplication::translate("LBMLBTRUTransportDialog", "SQN/Reason", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(sourcesTab), QApplication::translate("LBMLBTRUTransportDialog", "Sources", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem4 = receivers_TreeWidget->headerItem();
        ___qtreewidgetitem4->setText(16, QApplication::translate("LBMLBTRUTransportDialog", "CREQ rate", Q_NULLPTR));
        ___qtreewidgetitem4->setText(15, QApplication::translate("LBMLBTRUTransportDialog", "CREQ frames/bytes", Q_NULLPTR));
        ___qtreewidgetitem4->setText(14, QApplication::translate("LBMLBTRUTransportDialog", "CREQ bytes", Q_NULLPTR));
        ___qtreewidgetitem4->setText(13, QApplication::translate("LBMLBTRUTransportDialog", "CREQ frames", Q_NULLPTR));
        ___qtreewidgetitem4->setText(12, QApplication::translate("LBMLBTRUTransportDialog", "ACK rate", Q_NULLPTR));
        ___qtreewidgetitem4->setText(11, QApplication::translate("LBMLBTRUTransportDialog", "ACK frames/bytes", Q_NULLPTR));
        ___qtreewidgetitem4->setText(10, QApplication::translate("LBMLBTRUTransportDialog", "ACK bytes", Q_NULLPTR));
        ___qtreewidgetitem4->setText(9, QApplication::translate("LBMLBTRUTransportDialog", "ACK frames", Q_NULLPTR));
        ___qtreewidgetitem4->setText(8, QApplication::translate("LBMLBTRUTransportDialog", "NAK rate", Q_NULLPTR));
        ___qtreewidgetitem4->setText(7, QApplication::translate("LBMLBTRUTransportDialog", "NAK frames/count/bytes", Q_NULLPTR));
        ___qtreewidgetitem4->setText(6, QApplication::translate("LBMLBTRUTransportDialog", "NAK frames/bytes", Q_NULLPTR));
        ___qtreewidgetitem4->setText(5, QApplication::translate("LBMLBTRUTransportDialog", "NAK count/bytes", Q_NULLPTR));
        ___qtreewidgetitem4->setText(4, QApplication::translate("LBMLBTRUTransportDialog", "NAK frames/count", Q_NULLPTR));
        ___qtreewidgetitem4->setText(3, QApplication::translate("LBMLBTRUTransportDialog", "NAK bytes", Q_NULLPTR));
        ___qtreewidgetitem4->setText(2, QApplication::translate("LBMLBTRUTransportDialog", "NAK count", Q_NULLPTR));
        ___qtreewidgetitem4->setText(1, QApplication::translate("LBMLBTRUTransportDialog", "NAK frames", Q_NULLPTR));
        ___qtreewidgetitem4->setText(0, QApplication::translate("LBMLBTRUTransportDialog", "Address/Transport", Q_NULLPTR));
        label_4->setText(QApplication::translate("LBMLBTRUTransportDialog", "Show", Q_NULLPTR));
        receivers_detail_ComboBox->clear();
        receivers_detail_ComboBox->insertItems(0, QStringList()
         << QApplication::translate("LBMLBTRUTransportDialog", "NAK SQN", Q_NULLPTR)
         << QApplication::translate("LBMLBTRUTransportDialog", "ACK SQN", Q_NULLPTR)
         << QApplication::translate("LBMLBTRUTransportDialog", "CREQ request", Q_NULLPTR)
        );
        label_5->setText(QApplication::translate("LBMLBTRUTransportDialog", "details for transport", Q_NULLPTR));
        receivers_detail_transport_Label->setText(QApplication::translate("LBMLBTRUTransportDialog", "XXXXX:XXX.XXX.XXX.XXX:XXXXX:XXXXXXXX:XXX.XXX.XXX.XXX:XXXXX", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem5 = receivers_detail_sqn_TreeWidget->headerItem();
        ___qtreewidgetitem5->setText(2, QApplication::translate("LBMLBTRUTransportDialog", "Frame", Q_NULLPTR));
        ___qtreewidgetitem5->setText(1, QApplication::translate("LBMLBTRUTransportDialog", "Count", Q_NULLPTR));
        ___qtreewidgetitem5->setText(0, QApplication::translate("LBMLBTRUTransportDialog", "SQN", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem6 = receivers_detail_reason_TreeWidget->headerItem();
        ___qtreewidgetitem6->setText(2, QApplication::translate("LBMLBTRUTransportDialog", "Frame", Q_NULLPTR));
        ___qtreewidgetitem6->setText(1, QApplication::translate("LBMLBTRUTransportDialog", "Count", Q_NULLPTR));
        ___qtreewidgetitem6->setText(0, QApplication::translate("LBMLBTRUTransportDialog", "Reason", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(receiversTab), QApplication::translate("LBMLBTRUTransportDialog", "Receivers", Q_NULLPTR));
        label->setText(QApplication::translate("LBMLBTRUTransportDialog", "Display filter:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        applyFilterButton->setToolTip(QApplication::translate("LBMLBTRUTransportDialog", "Regenerate statistics using this display filter", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        applyFilterButton->setText(QApplication::translate("LBMLBTRUTransportDialog", "Apply", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LBMLBTRUTransportDialog: public Ui_LBMLBTRUTransportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LBM_LBTRU_TRANSPORT_DIALOG_H

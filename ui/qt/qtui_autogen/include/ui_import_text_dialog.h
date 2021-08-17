/********************************************************************************
** Form generated from reading UI file 'import_text_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMPORT_TEXT_DIALOG_H
#define UI_IMPORT_TEXT_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include "widgets/syntax_line_edit.h"

QT_BEGIN_NAMESPACE

class Ui_ImportTextDialog
{
public:
    QFormLayout *formLayout_3;
    QGroupBox *groupBox;
    QFormLayout *formLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *textFileLineEdit;
    QPushButton *textFileBrowseButton;
    QGridLayout *gridLayout_2;
    QRadioButton *octalOffsetButton;
    QLabel *label_2;
    QRadioButton *hexOffsetButton;
    QRadioButton *decimalOffsetButton;
    QSpacerItem *horizontalSpacer_2;
    QRadioButton *noOffsetButton;
    QLabel *noOffsetLabel;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *dateTimeLineEdit;
    QLabel *timestampExampleLabel;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_5;
    QLabel *directionIndicationLabel;
    QCheckBox *directionIndicationCheckBox;
    QSpacerItem *horizontalSpacer_5;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QComboBox *encapComboBox;
    QSpacerItem *horizontalSpacer_3;
    QGridLayout *headerGridLayout;
    SyntaxLineEdit *sourcePortLineEdit;
    SyntaxLineEdit *ppiLineEdit;
    SyntaxLineEdit *destinationPortLineEdit;
    QRadioButton *ethernetButton;
    QRadioButton *sctpButton;
    QLabel *ppiLabel;
    QLabel *protocolLabel;
    QRadioButton *noDummyButton;
    QSpacerItem *horizontalSpacer_4;
    QLabel *tagLabel;
    QRadioButton *udpButton;
    QLabel *sourcePortLabel;
    SyntaxLineEdit *ethertypeLineEdit;
    QRadioButton *tcpButton;
    SyntaxLineEdit *tagLineEdit;
    QLabel *destinationPortLabel;
    QLabel *ethertypeLabel;
    SyntaxLineEdit *protocolLineEdit;
    QRadioButton *sctpDataButton;
    QRadioButton *ipv4Button;
    QRadioButton *exportPduButton;
    QLabel *payloadLabel;
    SyntaxLineEdit *payloadLineEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_11;
    SyntaxLineEdit *maxLengthLineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ImportTextDialog)
    {
        if (ImportTextDialog->objectName().isEmpty())
            ImportTextDialog->setObjectName(QStringLiteral("ImportTextDialog"));
        ImportTextDialog->resize(472, 486);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ImportTextDialog->sizePolicy().hasHeightForWidth());
        ImportTextDialog->setSizePolicy(sizePolicy);
        ImportTextDialog->setMaximumSize(QSize(16777215, 486));
        ImportTextDialog->setSizeGripEnabled(true);
        ImportTextDialog->setModal(true);
        formLayout_3 = new QFormLayout(ImportTextDialog);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        formLayout_3->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
        groupBox = new QGroupBox(ImportTextDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setFlat(true);
        formLayout_2 = new QFormLayout(groupBox);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        textFileLineEdit = new QLineEdit(groupBox);
        textFileLineEdit->setObjectName(QStringLiteral("textFileLineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textFileLineEdit->sizePolicy().hasHeightForWidth());
        textFileLineEdit->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(textFileLineEdit);

        textFileBrowseButton = new QPushButton(groupBox);
        textFileBrowseButton->setObjectName(QStringLiteral("textFileBrowseButton"));

        horizontalLayout_2->addWidget(textFileBrowseButton);


        formLayout_2->setLayout(1, QFormLayout::SpanningRole, horizontalLayout_2);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        octalOffsetButton = new QRadioButton(groupBox);
        octalOffsetButton->setObjectName(QStringLiteral("octalOffsetButton"));

        gridLayout_2->addWidget(octalOffsetButton, 2, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        hexOffsetButton = new QRadioButton(groupBox);
        hexOffsetButton->setObjectName(QStringLiteral("hexOffsetButton"));
        hexOffsetButton->setChecked(true);

        gridLayout_2->addWidget(hexOffsetButton, 0, 1, 1, 1);

        decimalOffsetButton = new QRadioButton(groupBox);
        decimalOffsetButton->setObjectName(QStringLiteral("decimalOffsetButton"));

        gridLayout_2->addWidget(decimalOffsetButton, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 2, 3, 1);

        noOffsetButton = new QRadioButton(groupBox);
        noOffsetButton->setObjectName(QStringLiteral("noOffsetButton"));

        gridLayout_2->addWidget(noOffsetButton, 3, 1, 1, 1);

        noOffsetLabel = new QLabel(groupBox);
        noOffsetLabel->setObjectName(QStringLiteral("noOffsetLabel"));
        QFont font;
        font.setItalic(false);
        noOffsetLabel->setFont(font);

        gridLayout_2->addWidget(noOffsetLabel, 3, 2, 1, 1);


        formLayout_2->setLayout(2, QFormLayout::SpanningRole, gridLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        dateTimeLineEdit = new QLineEdit(groupBox);
        dateTimeLineEdit->setObjectName(QStringLiteral("dateTimeLineEdit"));

        horizontalLayout_3->addWidget(dateTimeLineEdit);

        timestampExampleLabel = new QLabel(groupBox);
        timestampExampleLabel->setObjectName(QStringLiteral("timestampExampleLabel"));

        horizontalLayout_3->addWidget(timestampExampleLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        formLayout_2->setLayout(4, QFormLayout::SpanningRole, horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        directionIndicationLabel = new QLabel(groupBox);
        directionIndicationLabel->setObjectName(QStringLiteral("directionIndicationLabel"));

        horizontalLayout_5->addWidget(directionIndicationLabel);

        directionIndicationCheckBox = new QCheckBox(groupBox);
        directionIndicationCheckBox->setObjectName(QStringLiteral("directionIndicationCheckBox"));

        horizontalLayout_5->addWidget(directionIndicationCheckBox);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        formLayout_2->setLayout(5, QFormLayout::SpanningRole, horizontalLayout_5);


        formLayout_3->setWidget(0, QFormLayout::SpanningRole, groupBox);

        groupBox_2 = new QGroupBox(ImportTextDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setFlat(true);
        formLayout = new QFormLayout(groupBox_2);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        encapComboBox = new QComboBox(groupBox_2);
        encapComboBox->setObjectName(QStringLiteral("encapComboBox"));

        horizontalLayout->addWidget(encapComboBox);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        formLayout->setLayout(0, QFormLayout::SpanningRole, horizontalLayout);

        headerGridLayout = new QGridLayout();
        headerGridLayout->setObjectName(QStringLiteral("headerGridLayout"));
        sourcePortLineEdit = new SyntaxLineEdit(groupBox_2);
        sourcePortLineEdit->setObjectName(QStringLiteral("sourcePortLineEdit"));

        headerGridLayout->addWidget(sourcePortLineEdit, 3, 2, 1, 1);

        ppiLineEdit = new SyntaxLineEdit(groupBox_2);
        ppiLineEdit->setObjectName(QStringLiteral("ppiLineEdit"));

        headerGridLayout->addWidget(ppiLineEdit, 6, 2, 1, 1);

        destinationPortLineEdit = new SyntaxLineEdit(groupBox_2);
        destinationPortLineEdit->setObjectName(QStringLiteral("destinationPortLineEdit"));

        headerGridLayout->addWidget(destinationPortLineEdit, 4, 2, 1, 1);

        ethernetButton = new QRadioButton(groupBox_2);
        ethernetButton->setObjectName(QStringLiteral("ethernetButton"));

        headerGridLayout->addWidget(ethernetButton, 1, 0, 1, 1);

        sctpButton = new QRadioButton(groupBox_2);
        sctpButton->setObjectName(QStringLiteral("sctpButton"));

        headerGridLayout->addWidget(sctpButton, 5, 0, 1, 1);

        ppiLabel = new QLabel(groupBox_2);
        ppiLabel->setObjectName(QStringLiteral("ppiLabel"));

        headerGridLayout->addWidget(ppiLabel, 6, 1, 1, 1);

        protocolLabel = new QLabel(groupBox_2);
        protocolLabel->setObjectName(QStringLiteral("protocolLabel"));

        headerGridLayout->addWidget(protocolLabel, 2, 1, 1, 1);

        noDummyButton = new QRadioButton(groupBox_2);
        noDummyButton->setObjectName(QStringLiteral("noDummyButton"));
        noDummyButton->setChecked(true);

        headerGridLayout->addWidget(noDummyButton, 0, 0, 1, 3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        headerGridLayout->addItem(horizontalSpacer_4, 0, 3, 7, 1);

        tagLabel = new QLabel(groupBox_2);
        tagLabel->setObjectName(QStringLiteral("tagLabel"));

        headerGridLayout->addWidget(tagLabel, 5, 1, 1, 1);

        udpButton = new QRadioButton(groupBox_2);
        udpButton->setObjectName(QStringLiteral("udpButton"));

        headerGridLayout->addWidget(udpButton, 3, 0, 1, 1);

        sourcePortLabel = new QLabel(groupBox_2);
        sourcePortLabel->setObjectName(QStringLiteral("sourcePortLabel"));

        headerGridLayout->addWidget(sourcePortLabel, 3, 1, 1, 1);

        ethertypeLineEdit = new SyntaxLineEdit(groupBox_2);
        ethertypeLineEdit->setObjectName(QStringLiteral("ethertypeLineEdit"));
        ethertypeLineEdit->setCursorPosition(0);

        headerGridLayout->addWidget(ethertypeLineEdit, 1, 2, 1, 1);

        tcpButton = new QRadioButton(groupBox_2);
        tcpButton->setObjectName(QStringLiteral("tcpButton"));

        headerGridLayout->addWidget(tcpButton, 4, 0, 1, 1);

        tagLineEdit = new SyntaxLineEdit(groupBox_2);
        tagLineEdit->setObjectName(QStringLiteral("tagLineEdit"));

        headerGridLayout->addWidget(tagLineEdit, 5, 2, 1, 1);

        destinationPortLabel = new QLabel(groupBox_2);
        destinationPortLabel->setObjectName(QStringLiteral("destinationPortLabel"));

        headerGridLayout->addWidget(destinationPortLabel, 4, 1, 1, 1);

        ethertypeLabel = new QLabel(groupBox_2);
        ethertypeLabel->setObjectName(QStringLiteral("ethertypeLabel"));

        headerGridLayout->addWidget(ethertypeLabel, 1, 1, 1, 1);

        protocolLineEdit = new SyntaxLineEdit(groupBox_2);
        protocolLineEdit->setObjectName(QStringLiteral("protocolLineEdit"));

        headerGridLayout->addWidget(protocolLineEdit, 2, 2, 1, 1);

        sctpDataButton = new QRadioButton(groupBox_2);
        sctpDataButton->setObjectName(QStringLiteral("sctpDataButton"));

        headerGridLayout->addWidget(sctpDataButton, 6, 0, 1, 1);

        ipv4Button = new QRadioButton(groupBox_2);
        ipv4Button->setObjectName(QStringLiteral("ipv4Button"));

        headerGridLayout->addWidget(ipv4Button, 2, 0, 1, 1);

        exportPduButton = new QRadioButton(groupBox_2);
        exportPduButton->setObjectName(QStringLiteral("exportPduButton"));

        headerGridLayout->addWidget(exportPduButton, 8, 0, 1, 1);

        payloadLabel = new QLabel(groupBox_2);
        payloadLabel->setObjectName(QStringLiteral("payloadLabel"));

        headerGridLayout->addWidget(payloadLabel, 8, 1, 1, 1);

        payloadLineEdit = new SyntaxLineEdit(groupBox_2);
        payloadLineEdit->setObjectName(QStringLiteral("payloadLineEdit"));

        headerGridLayout->addWidget(payloadLineEdit, 8, 2, 1, 1);


        formLayout->setLayout(1, QFormLayout::SpanningRole, headerGridLayout);


        formLayout_3->setWidget(1, QFormLayout::SpanningRole, groupBox_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_11 = new QLabel(ImportTextDialog);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_4->addWidget(label_11);

        maxLengthLineEdit = new SyntaxLineEdit(ImportTextDialog);
        maxLengthLineEdit->setObjectName(QStringLiteral("maxLengthLineEdit"));

        horizontalLayout_4->addWidget(maxLengthLineEdit);


        formLayout_3->setLayout(2, QFormLayout::FieldRole, horizontalLayout_4);

        buttonBox = new QDialogButtonBox(ImportTextDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Help|QDialogButtonBox::Open);

        formLayout_3->setWidget(3, QFormLayout::SpanningRole, buttonBox);


        retranslateUi(ImportTextDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ImportTextDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ImportTextDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ImportTextDialog);
    } // setupUi

    void retranslateUi(QDialog *ImportTextDialog)
    {
        groupBox->setTitle(QApplication::translate("ImportTextDialog", "Import From", Q_NULLPTR));
        label->setText(QApplication::translate("ImportTextDialog", "File:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        textFileLineEdit->setToolTip(QApplication::translate("ImportTextDialog", "Set name of text file to import", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        textFileBrowseButton->setToolTip(QApplication::translate("ImportTextDialog", "Browse for text file to import", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        textFileBrowseButton->setText(QApplication::translate("ImportTextDialog", "Browse\342\200\246", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        octalOffsetButton->setToolTip(QApplication::translate("ImportTextDialog", "Offsets in the text file are in octal notation", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        octalOffsetButton->setText(QApplication::translate("ImportTextDialog", "Octal", Q_NULLPTR));
        label_2->setText(QApplication::translate("ImportTextDialog", "Offsets:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        hexOffsetButton->setToolTip(QApplication::translate("ImportTextDialog", "Offsets in the text file are in hexadecimal notation", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        hexOffsetButton->setText(QApplication::translate("ImportTextDialog", "Hexadecimal", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        decimalOffsetButton->setToolTip(QApplication::translate("ImportTextDialog", "Offsets in the text file are in decimal notation", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        decimalOffsetButton->setText(QApplication::translate("ImportTextDialog", "Decimal", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        noOffsetButton->setToolTip(QApplication::translate("ImportTextDialog", "The text file has no offset", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        noOffsetButton->setText(QApplication::translate("ImportTextDialog", "None", Q_NULLPTR));
        noOffsetLabel->setText(QString());
#ifndef QT_NO_TOOLTIP
        label_3->setToolTip(QApplication::translate("ImportTextDialog", "The format in which to parse timestamps in the text file (e.g. %H:%M:%S.). Format specifiers are based on strptime(3)", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("ImportTextDialog", "Timestamp format:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        dateTimeLineEdit->setToolTip(QApplication::translate("ImportTextDialog", "The format in which to parse timestamps in the text file (e.g. %H:%M:%S.). Format specifiers are based on strptime(3)", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        timestampExampleLabel->setText(QString());
#ifndef QT_NO_TOOLTIP
        directionIndicationLabel->setToolTip(QApplication::translate("ImportTextDialog", "Whether or not the file contains information indicating the direction (inbound or outbound) of the packet.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        directionIndicationLabel->setText(QApplication::translate("ImportTextDialog", "Direction indication:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        directionIndicationCheckBox->setToolTip(QApplication::translate("ImportTextDialog", "Whether or not the file contains information indicating the direction (inbound or outbound) of the packet.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        groupBox_2->setTitle(QApplication::translate("ImportTextDialog", "Encapsulation", Q_NULLPTR));
        label_4->setText(QApplication::translate("ImportTextDialog", "Encapsulation Type:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        encapComboBox->setToolTip(QApplication::translate("ImportTextDialog", "Encapsulation type of the frames in the import capture file", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        sourcePortLineEdit->setToolTip(QApplication::translate("ImportTextDialog", "The UDP, TCP or SCTP source port for each frame", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        ppiLineEdit->setToolTip(QApplication::translate("ImportTextDialog", "The SCTP DATA payload protocol identifier for each frame", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        destinationPortLineEdit->setToolTip(QApplication::translate("ImportTextDialog", "The UDP, TCP or SCTP destination port for each frame", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        ethernetButton->setToolTip(QApplication::translate("ImportTextDialog", "Prefix each frame with an Ethernet header", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        ethernetButton->setText(QApplication::translate("ImportTextDialog", "Ethernet", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        sctpButton->setToolTip(QApplication::translate("ImportTextDialog", "Prefix each frame with an Ethernet, IPv4 and SCTP header", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        sctpButton->setText(QApplication::translate("ImportTextDialog", "SCTP", Q_NULLPTR));
        ppiLabel->setText(QApplication::translate("ImportTextDialog", "PPI:", Q_NULLPTR));
        protocolLabel->setText(QApplication::translate("ImportTextDialog", "Protocol (dec):", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        noDummyButton->setToolTip(QApplication::translate("ImportTextDialog", "Leave frames unchanged", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        noDummyButton->setText(QApplication::translate("ImportTextDialog", "No dummy header", Q_NULLPTR));
        tagLabel->setText(QApplication::translate("ImportTextDialog", "Tag:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        udpButton->setToolTip(QApplication::translate("ImportTextDialog", "Prefix each frame with an Ethernet, IPv4 and UDP header", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        udpButton->setText(QApplication::translate("ImportTextDialog", "UDP", Q_NULLPTR));
        sourcePortLabel->setText(QApplication::translate("ImportTextDialog", "Source port:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        ethertypeLineEdit->setToolTip(QApplication::translate("ImportTextDialog", "The Ethertype value of each frame", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        tcpButton->setToolTip(QApplication::translate("ImportTextDialog", "Prefix each frame with an Ethernet, IPv4 and TCP header", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        tcpButton->setText(QApplication::translate("ImportTextDialog", "TCP", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        tagLineEdit->setToolTip(QApplication::translate("ImportTextDialog", "The SCTP verification tag for each frame", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        destinationPortLabel->setText(QApplication::translate("ImportTextDialog", "Destination port:", Q_NULLPTR));
        ethertypeLabel->setText(QApplication::translate("ImportTextDialog", "Ethertype (hex):", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        protocolLineEdit->setToolTip(QApplication::translate("ImportTextDialog", "The IPv4 protocol ID for each frame", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        sctpDataButton->setToolTip(QApplication::translate("ImportTextDialog", "Prefix each frame with an Ethernet, IPv4 and SCTP (DATA) header", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        sctpDataButton->setText(QApplication::translate("ImportTextDialog", "SCTP (Data)", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        ipv4Button->setToolTip(QApplication::translate("ImportTextDialog", "Prefix each frame with an Ethernet and IPv4 header", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        ipv4Button->setText(QApplication::translate("ImportTextDialog", "IPv4", Q_NULLPTR));
        exportPduButton->setText(QApplication::translate("ImportTextDialog", "ExportPDU", Q_NULLPTR));
        payloadLabel->setText(QApplication::translate("ImportTextDialog", "Payload", Q_NULLPTR));
        label_11->setText(QApplication::translate("ImportTextDialog", "Maximum frame length:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        maxLengthLineEdit->setToolTip(QApplication::translate("ImportTextDialog", "The maximum size of the frames to write to the import capture file (max 256kiB)", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        Q_UNUSED(ImportTextDialog);
    } // retranslateUi

};

namespace Ui {
    class ImportTextDialog: public Ui_ImportTextDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMPORT_TEXT_DIALOG_H

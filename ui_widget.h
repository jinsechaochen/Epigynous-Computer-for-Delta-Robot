/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QCheckBox *checkBoxRecvHex;
    QCheckBox *checkBoxRecvText;
    QTextEdit *textEditRecv;
    QGroupBox *groupBoxRight;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_11;
    QTextBrowser *textBrowser;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_6;
    QGroupBox *groupBoxInch_2;
    QGridLayout *gridLayout_14;
    QWidget *widget;
    QGridLayout *gridLayout_12;
    QLabel *label_21;
    QPushButton *pushButtonPointAddX;
    QPushButton *pushButtonPointSubX;
    QLabel *label_22;
    QPushButton *pushButtonPointAddY;
    QPushButton *pushButtonPointSubY;
    QLabel *label_20;
    QPushButton *pushButtonPointAddZ;
    QPushButton *pushButtonPointSubZ;
    QGroupBox *groupBoxInch;
    QGridLayout *gridLayout_10;
    QPushButton *PushButtonInchXSub;
    QPushButton *PushButtonInchXAdd;
    QLabel *label_19;
    QLabel *label_17;
    QLabel *label_18;
    QPushButton *PushButtonInchZAdd;
    QPushButton *PushButtonInchYSub;
    QPushButton *PushButtonInchYAdd;
    QPushButton *PushButtonInchZSub;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_15;
    QLabel *label_4;
    QPushButton *pushButtonTrack;
    QComboBox *comboBoxTrack;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QGroupBox *leftTopGroupBox;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QComboBox *comboBoxBaund;
    QPushButton *pushButtonStop;
    QComboBox *comboBoxName;
    QLabel *label_2;
    QPushButton *pushButtonReset;
    QPushButton *pushButtonUpdateCom;
    QPushButton *pushButtonOpen;
    QPushButton *pushButtonClosePump;
    QPushButton *pushButtonOpenPump;
    QLabel *label_6;
    QPushButton *pushButtonSendSend;
    QPushButton *pushButtonSendClear;
    QTextEdit *textEditSend;
    QPushButton *pushButtonClearRecv;
    QCheckBox *checkBoxSendHex;
    QCheckBox *checkBoxSendText;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1091, 559);
        Widget->setStyleSheet(QString::fromUtf8(""));
        gridLayout_2 = new QGridLayout(Widget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        checkBoxRecvHex = new QCheckBox(groupBox);
        checkBoxRecvHex->setObjectName(QString::fromUtf8("checkBoxRecvHex"));
        checkBoxRecvHex->setChecked(true);
        checkBoxRecvHex->setAutoExclusive(true);

        gridLayout_5->addWidget(checkBoxRecvHex, 1, 0, 1, 1);

        checkBoxRecvText = new QCheckBox(groupBox);
        checkBoxRecvText->setObjectName(QString::fromUtf8("checkBoxRecvText"));
        checkBoxRecvText->setChecked(false);
        checkBoxRecvText->setAutoExclusive(true);

        gridLayout_5->addWidget(checkBoxRecvText, 1, 1, 1, 1);

        textEditRecv = new QTextEdit(groupBox);
        textEditRecv->setObjectName(QString::fromUtf8("textEditRecv"));
        textEditRecv->setMinimumSize(QSize(400, 0));
        textEditRecv->setReadOnly(false);

        gridLayout_5->addWidget(textEditRecv, 0, 0, 1, 2);


        gridLayout_2->addWidget(groupBox, 0, 0, 2, 1);

        groupBoxRight = new QGroupBox(Widget);
        groupBoxRight->setObjectName(QString::fromUtf8("groupBoxRight"));
        groupBoxRight->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(groupBoxRight);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_4 = new QGroupBox(groupBoxRight);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_11 = new QGridLayout(groupBox_4);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        textBrowser = new QTextBrowser(groupBox_4);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setMinimumSize(QSize(100, 0));

        gridLayout_11->addWidget(textBrowser, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_4, 0, 0, 1, 1);

        groupBox_3 = new QGroupBox(groupBoxRight);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	width:32px;\n"
"	min-height:20px;\n"
"	background-color: rgb(90, 181, 134);\n"
"	border: 3px solid rgb(70, 161, 104);\n"
"	border-style:outset;\n"
"	font-size:12pt;\n"
"	font:bold;\n"
"}\n"
"QPushButton::pressed\n"
"{\n"
"	border-style:inset;\n"
"}"));
        gridLayout_6 = new QGridLayout(groupBox_3);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        groupBoxInch_2 = new QGroupBox(groupBox_3);
        groupBoxInch_2->setObjectName(QString::fromUtf8("groupBoxInch_2"));
        gridLayout_14 = new QGridLayout(groupBoxInch_2);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        widget = new QWidget(groupBoxInch_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout_12 = new QGridLayout(widget);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        label_21 = new QLabel(widget);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_12->addWidget(label_21, 0, 0, 1, 1);

        pushButtonPointAddX = new QPushButton(widget);
        pushButtonPointAddX->setObjectName(QString::fromUtf8("pushButtonPointAddX"));

        gridLayout_12->addWidget(pushButtonPointAddX, 0, 1, 1, 1);

        pushButtonPointSubX = new QPushButton(widget);
        pushButtonPointSubX->setObjectName(QString::fromUtf8("pushButtonPointSubX"));

        gridLayout_12->addWidget(pushButtonPointSubX, 0, 2, 1, 1);

        label_22 = new QLabel(widget);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout_12->addWidget(label_22, 1, 0, 1, 1);

        pushButtonPointAddY = new QPushButton(widget);
        pushButtonPointAddY->setObjectName(QString::fromUtf8("pushButtonPointAddY"));

        gridLayout_12->addWidget(pushButtonPointAddY, 1, 1, 1, 1);

        pushButtonPointSubY = new QPushButton(widget);
        pushButtonPointSubY->setObjectName(QString::fromUtf8("pushButtonPointSubY"));

        gridLayout_12->addWidget(pushButtonPointSubY, 1, 2, 1, 1);

        label_20 = new QLabel(widget);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_12->addWidget(label_20, 2, 0, 1, 1);

        pushButtonPointAddZ = new QPushButton(widget);
        pushButtonPointAddZ->setObjectName(QString::fromUtf8("pushButtonPointAddZ"));

        gridLayout_12->addWidget(pushButtonPointAddZ, 2, 1, 1, 1);

        pushButtonPointSubZ = new QPushButton(widget);
        pushButtonPointSubZ->setObjectName(QString::fromUtf8("pushButtonPointSubZ"));

        gridLayout_12->addWidget(pushButtonPointSubZ, 2, 2, 1, 1);


        gridLayout_14->addWidget(widget, 0, 0, 1, 1);


        gridLayout_6->addWidget(groupBoxInch_2, 0, 0, 1, 1);

        groupBoxInch = new QGroupBox(groupBox_3);
        groupBoxInch->setObjectName(QString::fromUtf8("groupBoxInch"));
        gridLayout_10 = new QGridLayout(groupBoxInch);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        PushButtonInchXSub = new QPushButton(groupBoxInch);
        PushButtonInchXSub->setObjectName(QString::fromUtf8("PushButtonInchXSub"));

        gridLayout_10->addWidget(PushButtonInchXSub, 0, 2, 1, 1);

        PushButtonInchXAdd = new QPushButton(groupBoxInch);
        PushButtonInchXAdd->setObjectName(QString::fromUtf8("PushButtonInchXAdd"));

        gridLayout_10->addWidget(PushButtonInchXAdd, 0, 1, 1, 1);

        label_19 = new QLabel(groupBoxInch);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_10->addWidget(label_19, 2, 0, 1, 1);

        label_17 = new QLabel(groupBoxInch);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_10->addWidget(label_17, 0, 0, 1, 1);

        label_18 = new QLabel(groupBoxInch);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_10->addWidget(label_18, 1, 0, 1, 1);

        PushButtonInchZAdd = new QPushButton(groupBoxInch);
        PushButtonInchZAdd->setObjectName(QString::fromUtf8("PushButtonInchZAdd"));

        gridLayout_10->addWidget(PushButtonInchZAdd, 2, 1, 1, 1);

        PushButtonInchYSub = new QPushButton(groupBoxInch);
        PushButtonInchYSub->setObjectName(QString::fromUtf8("PushButtonInchYSub"));

        gridLayout_10->addWidget(PushButtonInchYSub, 1, 2, 1, 1);

        PushButtonInchYAdd = new QPushButton(groupBoxInch);
        PushButtonInchYAdd->setObjectName(QString::fromUtf8("PushButtonInchYAdd"));

        gridLayout_10->addWidget(PushButtonInchYAdd, 1, 1, 1, 1);

        PushButtonInchZSub = new QPushButton(groupBoxInch);
        PushButtonInchZSub->setObjectName(QString::fromUtf8("PushButtonInchZSub"));

        gridLayout_10->addWidget(PushButtonInchZSub, 2, 2, 1, 1);


        gridLayout_6->addWidget(groupBoxInch, 0, 1, 1, 1);

        groupBox_5 = new QGroupBox(groupBox_3);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout_15 = new QGridLayout(groupBox_5);
        gridLayout_15->setSpacing(6);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        label_4 = new QLabel(groupBox_5);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_15->addWidget(label_4, 0, 0, 1, 1);

        pushButtonTrack = new QPushButton(groupBox_5);
        pushButtonTrack->setObjectName(QString::fromUtf8("pushButtonTrack"));

        gridLayout_15->addWidget(pushButtonTrack, 3, 0, 1, 1);

        comboBoxTrack = new QComboBox(groupBox_5);
        comboBoxTrack->addItem(QString());
        comboBoxTrack->addItem(QString());
        comboBoxTrack->addItem(QString());
        comboBoxTrack->addItem(QString());
        comboBoxTrack->addItem(QString());
        comboBoxTrack->addItem(QString());
        comboBoxTrack->addItem(QString());
        comboBoxTrack->addItem(QString());
        comboBoxTrack->addItem(QString());
        comboBoxTrack->addItem(QString());
        comboBoxTrack->addItem(QString());
        comboBoxTrack->addItem(QString());
        comboBoxTrack->setObjectName(QString::fromUtf8("comboBoxTrack"));

        gridLayout_15->addWidget(comboBoxTrack, 2, 0, 1, 1);


        gridLayout_6->addWidget(groupBox_5, 0, 2, 1, 1);


        gridLayout->addWidget(groupBox_3, 0, 1, 1, 1);

        gridLayout->setColumnStretch(1, 1);

        gridLayout_2->addWidget(groupBoxRight, 0, 1, 1, 1);

        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        leftTopGroupBox = new QGroupBox(groupBox_2);
        leftTopGroupBox->setObjectName(QString::fromUtf8("leftTopGroupBox"));
        leftTopGroupBox->setMaximumSize(QSize(240, 16777215));
        leftTopGroupBox->setStyleSheet(QString::fromUtf8(""));
        gridLayout_3 = new QGridLayout(leftTopGroupBox);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label = new QLabel(leftTopGroupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        comboBoxBaund = new QComboBox(leftTopGroupBox);
        comboBoxBaund->addItem(QString());
        comboBoxBaund->addItem(QString());
        comboBoxBaund->addItem(QString());
        comboBoxBaund->addItem(QString());
        comboBoxBaund->addItem(QString());
        comboBoxBaund->addItem(QString());
        comboBoxBaund->addItem(QString());
        comboBoxBaund->setObjectName(QString::fromUtf8("comboBoxBaund"));

        gridLayout_3->addWidget(comboBoxBaund, 1, 1, 1, 2);

        pushButtonStop = new QPushButton(leftTopGroupBox);
        pushButtonStop->setObjectName(QString::fromUtf8("pushButtonStop"));
        pushButtonStop->setStyleSheet(QString::fromUtf8("background-color:rgb(255,0,0);"));

        gridLayout_3->addWidget(pushButtonStop, 3, 2, 1, 1);

        comboBoxName = new QComboBox(leftTopGroupBox);
        comboBoxName->setObjectName(QString::fromUtf8("comboBoxName"));

        gridLayout_3->addWidget(comboBoxName, 0, 1, 1, 2);

        label_2 = new QLabel(leftTopGroupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

        pushButtonReset = new QPushButton(leftTopGroupBox);
        pushButtonReset->setObjectName(QString::fromUtf8("pushButtonReset"));
        pushButtonReset->setStyleSheet(QString::fromUtf8("background-color:rgb(255,0,0);"));

        gridLayout_3->addWidget(pushButtonReset, 3, 0, 1, 2);

        pushButtonUpdateCom = new QPushButton(leftTopGroupBox);
        pushButtonUpdateCom->setObjectName(QString::fromUtf8("pushButtonUpdateCom"));
        pushButtonUpdateCom->setStyleSheet(QString::fromUtf8("background-color:rgb(255,0,0);"));

        gridLayout_3->addWidget(pushButtonUpdateCom, 2, 2, 1, 1);

        pushButtonOpen = new QPushButton(leftTopGroupBox);
        pushButtonOpen->setObjectName(QString::fromUtf8("pushButtonOpen"));
        pushButtonOpen->setStyleSheet(QString::fromUtf8("background-color:rgb(255,0,0);"));

        gridLayout_3->addWidget(pushButtonOpen, 2, 0, 1, 2);

        pushButtonClosePump = new QPushButton(leftTopGroupBox);
        pushButtonClosePump->setObjectName(QString::fromUtf8("pushButtonClosePump"));
        pushButtonClosePump->setStyleSheet(QString::fromUtf8("background-color:rgb(255,0,0);"));

        gridLayout_3->addWidget(pushButtonClosePump, 4, 2, 1, 1);

        pushButtonOpenPump = new QPushButton(leftTopGroupBox);
        pushButtonOpenPump->setObjectName(QString::fromUtf8("pushButtonOpenPump"));
        pushButtonOpenPump->setStyleSheet(QString::fromUtf8("background-color:rgb(255,0,0);"));

        gridLayout_3->addWidget(pushButtonOpenPump, 4, 0, 1, 2);


        gridLayout_4->addWidget(leftTopGroupBox, 1, 0, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_4->addWidget(label_6, 0, 3, 1, 1);

        pushButtonSendSend = new QPushButton(groupBox_2);
        pushButtonSendSend->setObjectName(QString::fromUtf8("pushButtonSendSend"));

        gridLayout_4->addWidget(pushButtonSendSend, 2, 3, 1, 1);

        pushButtonSendClear = new QPushButton(groupBox_2);
        pushButtonSendClear->setObjectName(QString::fromUtf8("pushButtonSendClear"));

        gridLayout_4->addWidget(pushButtonSendClear, 2, 1, 1, 1);

        textEditSend = new QTextEdit(groupBox_2);
        textEditSend->setObjectName(QString::fromUtf8("textEditSend"));

        gridLayout_4->addWidget(textEditSend, 1, 1, 1, 5);

        pushButtonClearRecv = new QPushButton(groupBox_2);
        pushButtonClearRecv->setObjectName(QString::fromUtf8("pushButtonClearRecv"));

        gridLayout_4->addWidget(pushButtonClearRecv, 2, 2, 1, 1);

        checkBoxSendHex = new QCheckBox(groupBox_2);
        checkBoxSendHex->setObjectName(QString::fromUtf8("checkBoxSendHex"));
        checkBoxSendHex->setChecked(true);
        checkBoxSendHex->setAutoExclusive(true);

        gridLayout_4->addWidget(checkBoxSendHex, 2, 4, 1, 1);

        checkBoxSendText = new QCheckBox(groupBox_2);
        checkBoxSendText->setObjectName(QString::fromUtf8("checkBoxSendText"));
        checkBoxSendText->setAutoExclusive(true);

        gridLayout_4->addWidget(checkBoxSendText, 2, 5, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 1, 1, 1, 1);

        gridLayout_2->setRowStretch(0, 1);
        gridLayout_2->setRowStretch(1, 1);

        retranslateUi(Widget);

        comboBoxBaund->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "\345\267\245\345\205\267", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Widget", "\346\216\245\346\224\266\344\270\262\345\217\243\346\225\260\346\215\256\344\277\241\346\201\257", nullptr));
        checkBoxRecvHex->setText(QCoreApplication::translate("Widget", "HEX", nullptr));
        checkBoxRecvText->setText(QCoreApplication::translate("Widget", "\346\226\207\346\234\254\346\230\276\347\244\272", nullptr));
        groupBoxRight->setTitle(QCoreApplication::translate("Widget", "\346\225\260\345\200\274\346\230\276\347\244\272", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("Widget", "Delta\346\234\272\345\231\250\344\272\272\346\274\224\347\244\272\344\275\277\347\224\250\347\256\200\346\230\223\350\257\264\346\230\216\357\274\232", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Version: 8.1</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Github:<a href=\"https://github.com/jinsechaochen/Epigynous-Computer/\"><span style=\" text-decoration: underline; color:#007af4;\">jinsechaochen/Epigynous-Computer: A Epigynous Computer for Controlling Delta Robots/\344\270\200\347\247\215\347\224\250"
                        "\344\272\216\346\216\247\345\210\266\344\270\211\350\275\264\345\271\266\350\201\224\346\234\272\345\231\250\344\272\272\347\232\204\344\270\212\344\275\215\346\234\272 (github.com)</span></a></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Author:DuskyBook</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI';\">\346\234\254\347\263\273\347\273\237\345\214\205\345\220\253\347\202\271\345\212\250\343\200\201\345\257\270\345\212\250\343\200\201\350\275\250\350\277\271\350\247\204\345\210\222\344\270\211\351\203\250\345\210\206</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI';\">1\343\200\201\344\275\277\347\224\250\345\211\215\351\234\200\351\200\211\346\213\251\345\245\275\346\263\242\347\211\271\347"
                        "\216\207\343\200\201COM\345\217\243\357\274\214\346\214\211\344\270\213\342\200\234\346\211\223\345\274\200\344\270\262\345\217\243\342\200\235\346\214\211\351\224\256</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI';\">2\343\200\201\345\275\223\345\211\215\345\212\250\345\271\263\345\217\260\345\235\220\346\240\207\345\217\212\347\224\265\346\234\272\350\275\254\345\212\250\346\203\205\345\206\265\345\260\206\345\234\250\345\267\246\344\276\247\346\230\276\347\244\272\345\214\272\345\237\237\346\230\276\347\244\272(\351\234\200\350\246\201\347\273\223\345\220\210\345\257\271\345\272\224\344\270\213\344\275\215\346\234\272)</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Segoe UI';\">\350\275\257\344\273\266\347\211\210\346\234\254 V8.1</span></p></body></html>", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Widget", "\346\216\247\345\210\266", nullptr));
        groupBoxInch_2->setTitle(QCoreApplication::translate("Widget", "\347\202\271\345\212\250", nullptr));
        label_21->setText(QCoreApplication::translate("Widget", "X:", nullptr));
        pushButtonPointAddX->setText(QCoreApplication::translate("Widget", "+", nullptr));
        pushButtonPointSubX->setText(QCoreApplication::translate("Widget", "-", nullptr));
        label_22->setText(QCoreApplication::translate("Widget", "Y:", nullptr));
        pushButtonPointAddY->setText(QCoreApplication::translate("Widget", "+", nullptr));
        pushButtonPointSubY->setText(QCoreApplication::translate("Widget", "-", nullptr));
        label_20->setText(QCoreApplication::translate("Widget", "Z:", nullptr));
        pushButtonPointAddZ->setText(QCoreApplication::translate("Widget", "+", nullptr));
        pushButtonPointSubZ->setText(QCoreApplication::translate("Widget", "-", nullptr));
        groupBoxInch->setTitle(QCoreApplication::translate("Widget", "\345\257\270\345\212\250", nullptr));
        PushButtonInchXSub->setText(QCoreApplication::translate("Widget", "-", nullptr));
        PushButtonInchXAdd->setText(QCoreApplication::translate("Widget", "+", nullptr));
        label_19->setText(QCoreApplication::translate("Widget", "Z:", nullptr));
        label_17->setText(QCoreApplication::translate("Widget", "X:", nullptr));
        label_18->setText(QCoreApplication::translate("Widget", "Y:", nullptr));
        PushButtonInchZAdd->setText(QCoreApplication::translate("Widget", "+", nullptr));
        PushButtonInchYSub->setText(QCoreApplication::translate("Widget", "-", nullptr));
        PushButtonInchYAdd->setText(QCoreApplication::translate("Widget", "+", nullptr));
        PushButtonInchZSub->setText(QCoreApplication::translate("Widget", "-", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("Widget", "\350\275\250\350\277\271\346\216\247\345\210\266", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "\350\275\250\350\277\271\351\200\211\346\213\251\357\274\232", nullptr));
        pushButtonTrack->setText(QCoreApplication::translate("Widget", "\350\275\250\350\277\271\345\217\221\351\200\201", nullptr));
        comboBoxTrack->setItemText(0, QCoreApplication::translate("Widget", "\346\230\237\345\275\242\350\275\250\350\277\271", nullptr));
        comboBoxTrack->setItemText(1, QCoreApplication::translate("Widget", "\345\274\247\345\275\242\350\275\250\350\277\271", nullptr));
        comboBoxTrack->setItemText(2, QCoreApplication::translate("Widget", "\346\242\257\345\275\242\350\275\250\350\277\2711", nullptr));
        comboBoxTrack->setItemText(3, QCoreApplication::translate("Widget", "\346\242\257\345\275\242\350\275\250\350\277\2712", nullptr));
        comboBoxTrack->setItemText(4, QCoreApplication::translate("Widget", "\346\213\211\345\247\206\350\275\250\350\277\2711", nullptr));
        comboBoxTrack->setItemText(5, QCoreApplication::translate("Widget", "\346\213\211\345\247\206\350\275\250\350\277\2712", nullptr));
        comboBoxTrack->setItemText(6, QCoreApplication::translate("Widget", "\346\213\211\345\247\206\350\275\250\350\277\2713", nullptr));
        comboBoxTrack->setItemText(7, QCoreApplication::translate("Widget", "\346\213\211\345\247\206\350\275\250\350\277\2714", nullptr));
        comboBoxTrack->setItemText(8, QCoreApplication::translate("Widget", "\346\213\211\345\247\206\350\275\250\350\277\2715", nullptr));
        comboBoxTrack->setItemText(9, QCoreApplication::translate("Widget", "\346\213\211\345\247\206\350\275\250\350\277\2716", nullptr));
        comboBoxTrack->setItemText(10, QCoreApplication::translate("Widget", "\346\213\211\345\247\206\350\275\250\350\277\2717", nullptr));
        comboBoxTrack->setItemText(11, QCoreApplication::translate("Widget", "\346\213\211\345\247\206\350\275\250\350\277\2718", nullptr));

        groupBox_2->setTitle(QCoreApplication::translate("Widget", "\345\217\221\351\200\201\347\252\227\345\217\243:", nullptr));
        leftTopGroupBox->setTitle(QCoreApplication::translate("Widget", "\344\270\262\345\217\243\350\256\276\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\344\270\262\345\217\243\345\217\267\357\274\232", nullptr));
        comboBoxBaund->setItemText(0, QCoreApplication::translate("Widget", "1200", nullptr));
        comboBoxBaund->setItemText(1, QCoreApplication::translate("Widget", "2400", nullptr));
        comboBoxBaund->setItemText(2, QCoreApplication::translate("Widget", "4800", nullptr));
        comboBoxBaund->setItemText(3, QCoreApplication::translate("Widget", "9600", nullptr));
        comboBoxBaund->setItemText(4, QCoreApplication::translate("Widget", "19200", nullptr));
        comboBoxBaund->setItemText(5, QCoreApplication::translate("Widget", "38400", nullptr));
        comboBoxBaund->setItemText(6, QCoreApplication::translate("Widget", "115200", nullptr));

        pushButtonStop->setText(QCoreApplication::translate("Widget", "\346\200\245\345\201\234", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\346\263\242\347\211\271\347\216\207\357\274\232", nullptr));
        pushButtonReset->setText(QCoreApplication::translate("Widget", "\345\244\215\344\275\215", nullptr));
        pushButtonUpdateCom->setText(QCoreApplication::translate("Widget", "\345\210\267\346\226\260\344\270\262\345\217\243", nullptr));
        pushButtonOpen->setText(QCoreApplication::translate("Widget", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        pushButtonClosePump->setText(QCoreApplication::translate("Widget", "\345\205\263\351\227\255\346\260\224\346\263\265", nullptr));
        pushButtonOpenPump->setText(QCoreApplication::translate("Widget", "\346\211\223\345\274\200\346\260\224\346\263\265", nullptr));
        label_6->setText(QString());
        pushButtonSendSend->setText(QCoreApplication::translate("Widget", "\345\217\221\351\200\201", nullptr));
        pushButtonSendClear->setText(QCoreApplication::translate("Widget", "\346\270\205\351\231\244\345\217\221\351\200\201", nullptr));
        pushButtonClearRecv->setText(QCoreApplication::translate("Widget", "\346\270\205\347\251\272\346\216\245\346\224\266", nullptr));
        checkBoxSendHex->setText(QCoreApplication::translate("Widget", "HEX", nullptr));
        checkBoxSendText->setText(QCoreApplication::translate("Widget", "\346\226\207\346\234\254\346\230\276\347\244\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H

#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QTimer>
#include <QDebug>
#pragma execution_character_set("utf-8")

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //this->showMaximized();
    QStringList listCom = m_pCom->GetComAll();
	for (int i = 0; i < listCom.size(); i++)
	{
		ui->comboBoxName->insertItem(i, listCom.at(i));
	}

    connect(ui->pushButtonOpen, &QPushButton::clicked, [=](){
		OpenPushButton();
    });


    connect(m_pCom, SIGNAL(RecvByteSignal(QByteArray)), this, SLOT(RecvInfoFromSerialSlot(QByteArray)));
    connect(m_pCom, SIGNAL(SendByteSignal(QByteArray)), this, SLOT(SendInfoFromSerialSlot(QByteArray)));

    SetTimer();
    SetInchButton();
    SetPointButton();
    SetComButton();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::RecvInfoFromSerialSlot(QByteArray arr)
{
    qDebug() << ui->checkBoxSendHex->isChecked();
    if(ui->checkBoxRecvHex->isChecked())
    {
        AddText(m_pCom->ByteToHexString(arr), true);
    }
    else
    {
        AddText(QString(arr), true);
    }
}

void Widget::SendInfoFromSerialSlot(QByteArray arr)
{
    qDebug() << ui->checkBoxSendHex->isChecked();
    if(ui->checkBoxSendHex->isChecked())
    {
        AddText(m_pCom->ByteToHexString(arr), false);
    }
    else
    {
        AddText(QString(arr), false);
    }
}

void Widget::OpenPushButton()
{
    if (m_pCom->IsOpenCom())
	{
        m_pCom->CloseComs();
		ui->pushButtonOpen->setStyleSheet("background-color:rgb(255,0,0);");
	}
	else
	{
		QString strPortName = ui->comboBoxName->currentText();
		int iBaund = ui->comboBoxBaund->currentText().toInt();
        int iData = 8;
		int iStop = 1;
		int iParty = 0;

        bool bRet = m_pCom->OpenCom(strPortName, iBaund, iData, iStop, iParty);
		if (bRet)
		{
			ui->pushButtonOpen->setStyleSheet("background-color:rgb(0,255,0);");
		}
		else
		{
			QMessageBox::warning(this, tr("提示"), tr("串口打开失败"), tr("确定"));
		}
	}
}

void Widget::AddText(QString strInfo, bool bRecv)
{
    QDateTime time = QDateTime::currentDateTime();
    QString strTemp;
    if(bRecv)
    {
        strTemp = QString(tr("[%1][接收]%2")).arg(time.toString("hh:mm:ss.zzz")).arg(strInfo);
        ui->textEditRecv->append(strTemp);
		ui->textEditRecv->moveCursor(QTextCursor::End);
    }
    else
    {
        strTemp = QString(tr("[%1][发送]%2")).arg(time.toString("hh:mm:ss.zzz")).arg(strInfo);
        ui->textEditRecv->append(strTemp);
        ui->textEditRecv->moveCursor(QTextCursor::End);
    }
}


void Widget::StopPointRun()
{
	pTimerPoint->stop();
}

unsigned char GetCrcSum(char* pData, int iLen)
{
    unsigned char uAdd = 0x00;
    if(pData == NULL)
    {
        return uAdd;
    }

    unsigned short usData = 0;
    for(int i = 0; i < iLen; i++)
    {
        usData += pData[i];
    }

    uAdd = usData & 0x00ff;

    return uAdd;
}

void Widget::SetTimer()
{
    connect(pTimerPoint, &QTimer::timeout, [=]() {
        if (!m_pCom->IsOpenCom())
        {
            QMessageBox::warning(this, tr("提示"), tr("串口未打开，失败"));
            pTimerPoint->stop();
            return;
        }

        if(m_iCurPointNum >= m_vecPointArrSend.size() || m_iCurPointNum < 0)
        {
            m_iCurPointNum = 0;
            m_vecPointArrSend.clear();
            pTimerPoint->stop();
            return;
        }

        QByteArray arr = m_vecPointArrSend.at(m_iCurPointNum);
        m_pCom->SendInfo(arr);

        m_iCurPointNum++;
    });

    connect(pTimerTrack, &QTimer::timeout, [=]() {
        if (!m_pCom->IsOpenCom())
        {
            QMessageBox::warning(this, tr("提示"), tr("串口未打开失败"));
            pTimerTrack->stop();
            return;
        }
        if(m_iSendCurNum >= m_vecArrSend.size() || m_iSendCurNum < 0)
        {
            m_iSendCurNum = 0;
            m_vecArrSend.clear();;
            pTimerTrack->stop();
            return;
        }

        QByteArray arr = m_vecArrSend.at(m_iSendCurNum);
        m_pCom->SendInfo(arr);

        m_iSendCurNum++;
    });
}

void Widget::SetPointButton()//ABC点动暂时不设置功能
{
    //点动X Y Z
    connect(ui->pushButtonPointAddX, &QPushButton::pressed, [=](){  //X轴正向点动-按下
        //只发送一次：
        //aa 05 01 01 64 55 55 55 55 55 55 4e 20 02 校验 ff 10厘米 2秒
        unsigned char szBuf[] = {0xaa, 0x05, 0x01, 0x01, 0x64, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x4e, 0x20, 0x02, 0x00, 0xff};
        QByteArray arr((char*)szBuf, sizeof(szBuf));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);
        m_iCurPointNum = 0;

        pTimerPoint->start(100);
    });
    connect(ui->pushButtonPointAddX, &QPushButton::released, [=](){  //X轴正向点动-松开
        StopPointRun();
        //只发送一次（发送三条）：
        //aa 01 09 55 55 55 55 55 55 55 55 55 55 01 校验 ff
        //aa 02 09 55 55 55 55 55 55 55 55 55 55 01 校验 ff
        //aa 03 09 55 55 55 55 55 55 55 55 55 55 02 校验 ff
        unsigned char szBuf[] = {0xaa, 0x01, 0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
        QByteArray arr = QByteArray((char*)szBuf, sizeof(szBuf));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);

        unsigned char szBuf1[] = {0xaa, 0x02, 0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
        arr = QByteArray((char*)szBuf1, sizeof(szBuf1));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);

        unsigned char szBuf2[] = {0xaa, 0x03, 0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
        arr = QByteArray((char*)szBuf2, sizeof(szBuf2));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);
        m_iCurPointNum = 0;

        pTimerPoint->start(200);

    });

    connect(ui->pushButtonPointSubX, &QPushButton::pressed, [=](){  //Y轴正向点动-按下
        //只发送一次：
        //aa 05 01 00 64 55 55 55 55 55 55 4e 20 02 校验 ff
        unsigned char szBuf[] = {0xaa, 0x05, 0x01, 0x00, 0x64, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x4e, 0x20, 0x02, 0x00, 0xff};
        QByteArray arr((char*)szBuf, sizeof(szBuf));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);
        m_iCurPointNum = 0;

        pTimerPoint->start(100);
    });
    connect(ui->pushButtonPointSubX, &QPushButton::released, [=](){ //X轴逆向点动-松开
        StopPointRun();
        //只发送一次（发送三条）：
        //aa 01 09 55 55 55 55 55 55 55 55 55 55 01 校验 ff
        //aa 02 09 55 55 55 55 55 55 55 55 55 55 01 校验 ff
        //aa 03 09 55 55 55 55 55 55 55 55 55 55 02 校验 ff
        unsigned char szBuf[] = {0xaa, 0x01, 0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
        QByteArray arr = QByteArray((char*)szBuf, sizeof(szBuf));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);

        unsigned char szBuf1[] = {0xaa, 0x02, 0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
        arr = QByteArray((char*)szBuf1, sizeof(szBuf1));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);

        unsigned char szBuf2[] = {0xaa, 0x03, 0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
        arr = QByteArray((char*)szBuf2, sizeof(szBuf2));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);
        m_iCurPointNum = 0;

        pTimerPoint->start(200);

    });

    connect(ui->pushButtonPointAddY, &QPushButton::pressed, [=](){  //Y轴正向点动-按下
        //只发送一次：
        //aa 05 02 01 64 55 55 55 55 55 55 4e 20 02 校验 ff
        unsigned char szBuf[] = {0xaa, 0x05, 0x02, 0x01, 0x64, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x4e, 0x20, 0x02, 0x00, 0xff};
        QByteArray arr((char*)szBuf, sizeof(szBuf));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);
        m_iCurPointNum = 0;

        pTimerPoint->start(100);
    });
    connect(ui->pushButtonPointAddY, &QPushButton::released, [=](){  //Y轴正向点动-松开
        StopPointRun();
        //只发送一次（发送三条）：
        //aa 01 09 55 55 55 55 55 55 55 55 55 55 01 校验 ff
        //aa 02 09 55 55 55 55 55 55 55 55 55 55 01 校验 ff
        //aa 03 09 55 55 55 55 55 55 55 55 55 55 02 校验 ff
        unsigned char szBuf[] = {0xaa, 0x01, 0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
        QByteArray arr = QByteArray((char*)szBuf, sizeof(szBuf));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);

        unsigned char szBuf1[] = {0xaa, 0x02, 0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
        arr = QByteArray((char*)szBuf1, sizeof(szBuf1));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);

        unsigned char szBuf2[] = {0xaa, 0x03, 0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
        arr = QByteArray((char*)szBuf2, sizeof(szBuf2));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);
        m_iCurPointNum = 0;

        pTimerPoint->start(200);


    });
    connect(ui->pushButtonPointSubY, &QPushButton::pressed, [=](){  //Y轴逆向点动-按下
        //只发送一次：
        //aa 05 02 00 64 55 55 55 55 55 55 4e 20 02 校验 ff
        unsigned char szBuf[] = {0xaa, 0x05, 0x02, 0x00, 0x64, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x4e, 0x20, 0x02, 0x00, 0xff};
        QByteArray arr((char*)szBuf, sizeof(szBuf));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);
        m_iCurPointNum = 0;

        pTimerPoint->start(100);
    });
    connect(ui->pushButtonPointSubY, &QPushButton::released, [=](){  //Y轴逆向点动-松开
        StopPointRun();
        //只发送一次（发送三条）：
        //aa 01 09 55 55 55 55 55 55 55 55 55 55 01 校验 ff
        //aa 02 09 55 55 55 55 55 55 55 55 55 55 01 校验 ff
        //aa 03 09 55 55 55 55 55 55 55 55 55 55 02 校验 ff
        unsigned char szBuf[] = {0xaa, 0x01, 0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
        QByteArray arr = QByteArray((char*)szBuf, sizeof(szBuf));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);

        unsigned char szBuf1[] = {0xaa, 0x02, 0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
        arr = QByteArray((char*)szBuf1, sizeof(szBuf1));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);

        unsigned char szBuf2[] = {0xaa, 0x03, 0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
        arr = QByteArray((char*)szBuf2, sizeof(szBuf2));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);
        m_iCurPointNum = 0;

        pTimerPoint->start(200);

    });

    connect(ui->pushButtonPointAddZ, &QPushButton::pressed, [=](){  //Z轴正向点动-按下
        //只发送一次：
        //aa 05 03 01 32 55 55 55 55 55 55 4e 20 02 校验 ff 5厘米 2秒
        unsigned char szBuf[] = {0xaa, 0x05, 0x03, 0x01, 0x32, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x4e, 0x20, 0x02, 0x00, 0xff};
        QByteArray arr((char*)szBuf, sizeof(szBuf));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);
        m_iCurPointNum = 0;

        pTimerPoint->start(100);
    });
    connect(ui->pushButtonPointAddZ, &QPushButton::released, [=](){  //Z轴正向点动-松开
        StopPointRun();
        //只发送一次（发送三条）：
        //aa 01 09 55 55 55 55 55 55 55 55 55 55 01 校验 ff
        //aa 02 09 55 55 55 55 55 55 55 55 55 55 01 校验 ff
        //aa 03 09 55 55 55 55 55 55 55 55 55 55 02 校验 ff
        unsigned char szBuf[] = {0xaa, 0x01, 0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
        QByteArray arr = QByteArray((char*)szBuf, sizeof(szBuf));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);

        unsigned char szBuf1[] = {0xaa, 0x02, 0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
        arr = QByteArray((char*)szBuf1, sizeof(szBuf1));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);

        unsigned char szBuf2[] = {0xaa, 0x03, 0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
        arr = QByteArray((char*)szBuf2, sizeof(szBuf2));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);
        m_iCurPointNum = 0;

        pTimerPoint->start(200);

    });

    connect(ui->pushButtonPointSubZ, &QPushButton::pressed, [=](){  //Z轴逆向点动-按下
        //只发送一次：
        //aa 05 03 00 32 55 55 55 55 55 55 4e 20 02 校验 ff
        unsigned char szBuf[] = {0xaa, 0x05, 0x03, 0x00, 0x32, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x4e, 0x20, 0x02, 0x00, 0xff};
        QByteArray arr((char*)szBuf, sizeof(szBuf));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);
        m_iCurPointNum = 0;

        pTimerPoint->start(100);

    });
    connect(ui->pushButtonPointSubZ, &QPushButton::released, [=](){  //Z轴逆向点动-松开
        StopPointRun();
        //只发送一次（发送三条）：
        //aa 01 09 55 55 55 55 55 55 55 55 55 55 01 校验 ff
        //aa 02 09 55 55 55 55 55 55 55 55 55 55 01 校验 ff
        //aa 03 09 55 55 55 55 55 55 55 55 55 55 02 校验 ff
        unsigned char szBuf[] = {0xaa, 0x01, 0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
        QByteArray arr = QByteArray((char*)szBuf, sizeof(szBuf));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);

        unsigned char szBuf1[] = {0xaa, 0x02, 0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
        arr = QByteArray((char*)szBuf1, sizeof(szBuf1));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);

        unsigned char szBuf2[] = {0xaa, 0x03, 0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
        arr = QByteArray((char*)szBuf2, sizeof(szBuf2));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);
        m_iCurPointNum = 0;

        pTimerPoint->start(200);

    });
}

void Widget::SetInchButton()  //XYZ轴向寸动
{
    connect(ui->PushButtonInchXAdd, &QPushButton::pressed, [=](){  //X轴正向寸动
        //只发送一次：
        //aa 05 01 01 64 55 55 55 55 55 55 4e 20 02 校验 ff
        unsigned char szBuf[] = {0xaa, 0x05, 0x01, 0x01, 0x64, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x4e, 0x20, 0x02, 0x00, 0xff};
        QByteArray arr((char*)szBuf, sizeof(szBuf));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);
        m_iCurPointNum = 0;

        pTimerPoint->start(100);
    });
    connect(ui->PushButtonInchXSub, &QPushButton::pressed, [=](){  //X轴逆向寸动
        //只发送一次：
        //aa 05 01 00 64 55 55 55 55 55 55 4e 20 02 校验 ff
        unsigned char szBuf[] = {0xaa, 0x05, 0x01, 0x00, 0x64, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x4e, 0x20, 0x02, 0x00, 0xff};
        QByteArray arr((char*)szBuf, sizeof(szBuf));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);
        m_iCurPointNum = 0;

        pTimerPoint->start(100);
    });
    connect(ui->PushButtonInchYAdd, &QPushButton::pressed, [=](){  //Y轴正向寸动
        //只发送一次：
        //aa 05 02 01 64 55 55 55 55 55 55 c3 50 02 校验 ff
        unsigned char szBuf[] = {0xaa, 0x05, 0x02, 0x01, 0x64, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x4e, 0x20, 0x02, 0x00, 0xff};
        QByteArray arr((char*)szBuf, sizeof(szBuf));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);
        m_iCurPointNum = 0;

        pTimerPoint->start(100);
    });
    connect(ui->PushButtonInchYSub, &QPushButton::pressed, [=](){  //Y轴逆向寸动
        //只发送一次：
        //aa 05 02 00 64 55 55 55 55 55 55 c3 50 02 校验 ff
        unsigned char szBuf[] = {0xaa, 0x05, 0x02, 0x00, 0x64, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x4e, 0x20, 0x02, 0x00, 0xff};
        QByteArray arr((char*)szBuf, sizeof(szBuf));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);
        m_iCurPointNum = 0;

        pTimerPoint->start(100);
    });
    connect(ui->PushButtonInchZAdd, &QPushButton::pressed, [=](){  //Z轴正向寸动
        //只发送一次：
        //aa 05 03 01 32 55 55 55 55 55 55 c3 50 02 校验 ff
        unsigned char szBuf[] = {0xaa, 0x05, 0x03, 0x01, 0x32, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x4e, 0x20, 0x02, 0x00, 0xff};
        QByteArray arr((char*)szBuf, sizeof(szBuf));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);
        m_iCurPointNum = 0;

        pTimerPoint->start(100);
    });
    connect(ui->PushButtonInchZSub, &QPushButton::pressed, [=](){  //Z轴逆向寸动
        //只发送一次：
        //aa 05 03 00 32 55 55 55 55 55 55 c3 50 02 校验 ff
        unsigned char szBuf[] = {0xaa, 0x05, 0x03, 0x00, 0x32, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x4e, 0x20, 0x02, 0x00, 0xff};
        QByteArray arr((char*)szBuf, sizeof(szBuf));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);
        m_iCurPointNum = 0;

        pTimerPoint->start(100);
    });
}

/*往下是轨迹选择的内容
轨迹一（“轨迹一”填写到Combobox里，当选择轨迹一时，按下“轨迹发送”键一次发送完毕）：
    //aa 00 01 00 00 01 00 00 02 01 4a 4e 20 02 校验 ff
    //aa 04 01 55 55 55 55 55 55 55 55 55 55 02 校验 ff
轨迹二（“轨迹二”填写到Combobox里，当选择轨迹二时，按下“轨迹发送”键一次发送完毕）：
    //aa 00 01 00 64 01 00 00 02 01 4a 4e 20 02 校验 ff
    //aa 04 02 55 55 55 55 55 55 55 55 55 55 02 校验 ff
轨迹三（“轨迹三”填写到Combobox里，当选择轨迹三时，按下“轨迹发送”键一次发送完毕）：
    //aa 00 01 00 00 01 00 00 02 01 4a 4e 20 02 校验 ff
    //aa 04 03 55 55 55 55 55 55 55 55 55 55 02 校验 ff
轨迹四（“轨迹四”填写到Combobox里，当选择轨迹四时，按下“轨迹发送”键一次发送完毕）：
    //aa 00 01 00 64 01 00 00 02 01 4a 4e 20 02 校验 ff
    //aa 04 04 55 55 55 55 55 55 55 55 55 55 02 校验 ff
轨迹五（“轨迹五”填写到Combobox里，当选择轨迹五时，按下“轨迹发送”键一次发送完毕）：
    //aa 00 01 00 00 01 00 00 02 01 4a 4e 20 02 校验 ff
    //aa 04 05 55 55 55 55 55 55 55 55 55 55 02 校验 ff
轨迹六（“轨迹六”填写到Combobox里，当选择轨迹六时，按下“轨迹发送”键一次发送完毕）：
    //aa 00 01 00 b4 01 00 00 02 01 4a 4e 20 02 校验 ff
    //aa 04 06 55 55 55 55 55 55 55 55 55 55 02 校验 ff
轨迹七（“轨迹七”填写到Combobox里，当选择轨迹七时，按下“轨迹发送”键一次发送完毕）：
    //aa 00 01 00 00 01 00 00 02 01 4a 4e 20 02 校验 ff
    //aa 04 07 55 55 55 55 55 55 55 55 55 55 02 校验 ff
轨迹八（“轨迹八”填写到Combobox里，当选择轨迹八时，按下“轨迹发送”键一次发送完毕）：
    //aa 00 01 00 b4 01 00 00 02 01 4a 4e 20 02 校验 ff
    //aa 04 08 55 55 55 55 55 55 55 55 55 55 02 校验 ff
轨迹九（“星形轨迹”填写到Combobox里，当选择星形轨迹时，按下“轨迹发送”键一次发送完毕）：
    //延时2.15秒
    //aa 00 01 00 00 01 00 00 00 01 4a 4e 20 02 校验 ff
    //延时2.15秒
    //aa 00 01 00 00 01 00 b4 00 01 4a 4e 20 02 校验 ff
    //延时2.15秒
    //aa 00 00 00 6a 00 00 92 00 01 4a 4e 20 02 校验 ff
    //延时2.15秒
    //aa 00 01 00 ab 01 00 38 00 01 4a 4e 20 02 校验 ff
    //延时2.15秒
    //aa 00 00 00 ab 01 00 38 00 01 4a 4e 20 02 校验 ff
    //延时2.15秒
    //aa 00 01 00 6a 00 00 92 00 01 4a 4e 20 02 校验 ff
    //延时2.15秒
    //aa 00 01 00 00 00 00 b4 00 01 4a 4e 20 02 校验 ff
    //延时2.15秒
轨迹十（“梯形轨迹1”填写到Combobox里，当选择梯形轨迹1时，按下“轨迹发送”键一次发送完毕）：
    //aa 00 00 00 50 01 00 00 00 01 4a 4e 20 02 00 ff
    //aa 00 00 00 28 01 00 00 00 01 22 4e 20 02 00 ff
    //aa 00 01 00 28 01 00 00 00 01 22 4e 20 02 00 ff
    //aa 00 01 00 50 01 00 00 00 01 2c 4e 20 02 00 ff
    //aa 00 00 00 50 01 00 00 00 01 4a 4e 20 02 00 ff
轨迹十一（“梯形轨迹2”填写到Combobox里，当选择梯形轨迹2时，按下“轨迹发送”键一次发送完毕）：
    //aa 00 00 00 50 01 00 00 00 01 4a 4e 20 02 00 ff
    //aa 00 00 00 1e 01 00 00 00 01 0e 4e 20 02 00 ff
    //aa 00 01 00 28 01 00 00 00 01 0e 4e 20 02 00 ff
    //aa 00 01 00 50 01 00 00 00 01 4a 4e 20 02 00 ff
    //aa 00 00 00 50 01 00 00 00 01 4a 4e 20 02 00 ff
*/
struct TrackInfo
{
    QString strName;
    unsigned char arr[16];
};

QVector<TrackInfo> g_lstInfo =
{
    {QObject::tr("轨迹一"),{0xaa, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x01, 0x4a, 0x88, 0xb8, 0x02, 0x00, 0xff}},
    {QObject::tr("轨迹二"),{0xaa, 0x00, 0x01, 0x00, 0x64, 0x01, 0x00, 0x00, 0x02, 0x01, 0x4a, 0x88, 0xb8, 0x02, 0x00, 0xff}}
};


void Widget::SetComButton()
{
     connect(ui->pushButtonSendClear, &QPushButton::clicked, [=](){
           ui->textEditSend->setText("");
     });

     connect(ui->pushButtonClearRecv, &QPushButton::clicked, [=](){
           ui->textEditRecv->setText("");
     });

     connect(ui->pushButtonSendSend, &QPushButton::clicked, [=](){
          QString strSend = ui->textEditSend->toPlainText();
          QByteArray arr;
          if (ui->checkBoxSendHex->isChecked())
          {
             arr  = m_pCom->HexStringToByte(strSend);
          }
           else
          {
              arr = strSend.toLocal8Bit();
          }

          m_pCom->SendInfo(arr);
     });

     connect(ui->pushButtonUpdateCom, &QPushButton::clicked, [=](){
        QStringList lstInfo = m_pCom->GetComAll();
        ui->comboBoxName->clear();
        for(int i = 0; i < lstInfo.size(); i++)
        {
            ui->comboBoxName->insertItem(i, lstInfo.at(i));
        }
     });

     connect(ui->pushButtonReset, &QPushButton::pressed, [=](){  //复位
         //只发送一次：
         //aa 01 01 55 55 55 55 55 55 55 55 55 55 02 00 ff
         //aa 02 01 55 55 55 55 55 55 55 55 55 55 02 00 ff
         //aa 03 01 55 55 55 55 55 55 55 55 55 55 02 00 ff
         unsigned char szBuf[] = {0xaa, 0x01, 0x01, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x01, 0x00, 0xff};
         QByteArray arr = QByteArray((char*)szBuf, sizeof(szBuf));
         arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
         m_vecPointArrSend.push_back(arr);

         unsigned char szBuf1[] = {0xaa, 0x02, 0x01, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x01, 0x00, 0xff};
         arr = QByteArray((char*)szBuf1, sizeof(szBuf1));
         arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
         m_vecPointArrSend.push_back(arr);

         unsigned char szBuf2[] = {0xaa, 0x03, 0x01, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
         arr = QByteArray((char*)szBuf2, sizeof(szBuf2));
         arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
         m_vecPointArrSend.push_back(arr);
         m_iCurPointNum = 0;


         pTimerPoint->start(100);

     });

     connect(ui->pushButtonTrack, &QPushButton::clicked, [=](){

         QString strInfo = ui->comboBoxTrack->currentText();
         if(strInfo.compare(tr("拉姆轨迹1")) == 0) //轨迹1
         {
             unsigned char szBuf[] = {0xaa, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x4a, 0x4e, 0x20, 0x02, 0x00, 0xff};
             QByteArray arr = QByteArray((char*)szBuf, sizeof(szBuf));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);

             unsigned char szBuf1[] = {0xaa, 0x04, 0x01, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf1, sizeof(szBuf1));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);

             pTimerTrack->start(2200);
         }

         if(strInfo.compare(tr("拉姆轨迹2")) == 0) //轨迹2
         {
             unsigned char szBuf[] = {0xaa, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x4a, 0x4e, 0x20, 0x02, 0x00, 0xff};
             QByteArray arr = QByteArray((char*)szBuf, sizeof(szBuf));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);

             unsigned char szBuf1[] = {0xaa, 0x04, 0x02, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf1, sizeof(szBuf1));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);

             pTimerTrack->start(2200);
         }

         if(strInfo.compare(tr("拉姆轨迹3")) == 0) //轨迹3
         {
             unsigned char szBuf[] = {0xaa, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x4a, 0x4e, 0x20, 0x02, 0x00, 0xff};
             QByteArray arr = QByteArray((char*)szBuf, sizeof(szBuf));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);

             unsigned char szBuf1[] = {0xaa, 0x04, 0x02, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf1, sizeof(szBuf1));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);

             pTimerTrack->start(2200);
         }

         if(strInfo.compare(tr("拉姆轨迹4")) == 0) //轨迹4
         {
             unsigned char szBuf[] = {0xaa, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x4a, 0x4e, 0x20, 0x02, 0x00, 0xff};
             QByteArray arr = QByteArray((char*)szBuf, sizeof(szBuf));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);

             unsigned char szBuf1[] = {0xaa, 0x04, 0x04, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf1, sizeof(szBuf1));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);

             pTimerTrack->start(2200);
         }


         if(strInfo.compare(tr("拉姆轨迹5")) == 0) //轨迹5
         {
             unsigned char szBuf[] = {0xaa, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x4a, 0x4e, 0x20, 0x02, 0x00, 0xff};
             QByteArray arr = QByteArray((char*)szBuf, sizeof(szBuf));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);

             unsigned char szBuf1[] = {0xaa, 0x04, 0x05, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf1, sizeof(szBuf1));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);

             pTimerTrack->start(2200);
         }


         if(strInfo.compare(tr("拉姆轨迹6")) == 0) //轨迹6
         {
             unsigned char szBuf[] = {0xaa, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x4a, 0x4e, 0x20, 0x02, 0x00, 0xff};
             QByteArray arr = QByteArray((char*)szBuf, sizeof(szBuf));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);

             unsigned char szBuf1[] = {0xaa, 0x04, 0x06, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf1, sizeof(szBuf1));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);

             pTimerTrack->start(2200);
         }


         if(strInfo.compare(tr("拉姆轨迹7")) == 0) //轨迹7
         {
             unsigned char szBuf[] = {0xaa, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x4a, 0x4e, 0x20, 0x02, 0x00, 0xff};
             QByteArray arr = QByteArray((char*)szBuf, sizeof(szBuf));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);

             unsigned char szBuf1[] = {0xaa, 0x04, 0x07, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf1, sizeof(szBuf1));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);

             pTimerTrack->start(2200);
         }


         if(strInfo.compare(tr("拉姆轨迹8")) == 0) //轨迹8
         {
             unsigned char szBuf[] = {0xaa, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x4a, 0x4e, 0x20, 0x02, 0x00, 0xff};
             QByteArray arr = QByteArray((char*)szBuf, sizeof(szBuf));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);

             unsigned char szBuf1[] = {0xaa, 0x04, 0x08, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf1, sizeof(szBuf1));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);

             pTimerTrack->start(2200);
         }

         if(strInfo.compare(tr("星形轨迹")) == 0) //轨迹9
         {
             unsigned char szBuf[] = {0xaa, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x4a, 0x4e, 0x20, 0x02, 0x00, 0xff};
             QByteArray arr = QByteArray((char*)szBuf, sizeof(szBuf));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);

             unsigned char szBuf1[] = {0xaa, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0xb4, 0x00, 0x01, 0x4a, 0x4e, 0x20, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf1, sizeof(szBuf1));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);

             unsigned char szBuf2[] = {0xaa, 0x00, 0x00, 0x00, 0x6a, 0x00, 0x00, 0x92, 0x00, 0x01, 0x4a, 0x4e, 0x20, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf2, sizeof(szBuf2));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);
             m_iSendCurNum = 0;

             unsigned char szBuf3[] = {0xaa, 0x00, 0x01, 0x00, 0xab, 0x01, 0x00, 0x38, 0x00, 0x01, 0x4a, 0x4e, 0x20, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf3, sizeof(szBuf3));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);
             m_iSendCurNum = 0;

             unsigned char szBuf4[] = {0xaa, 0x00, 0x00, 0x00, 0xab, 0x01, 0x00, 0x38, 0x00, 0x01, 0x4a, 0x4e, 0x20, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf4, sizeof(szBuf4));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);
             m_iSendCurNum = 0;

             unsigned char szBuf5[] = {0xaa, 0x00, 0x01, 0x00, 0x6a, 0x00, 0x00, 0x92, 0x00, 0x01, 0x4a, 0x4e, 0x20, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf5, sizeof(szBuf5));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);
             m_iSendCurNum = 0;

             unsigned char szBuf6[] = {0xaa, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0xb4, 0x00, 0x01, 0x4a, 0x4e, 0x20, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf6, sizeof(szBuf6));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);
             m_iSendCurNum = 0;

             pTimerTrack->start(2150);

         }

         if(strInfo.compare(tr("梯形轨迹1")) == 0) //轨迹10
         {
             unsigned char szBuf[] = {0xaa, 0x00, 0x00, 0x00, 0x50, 0x01, 0x00, 0x00, 0x00, 0x01, 0x4a, 0x27, 0x10, 0x02, 0x00, 0xff};
             QByteArray arr = QByteArray((char*)szBuf, sizeof(szBuf));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);

             unsigned char szBuf1[] = {0xaa, 0x00, 0x00, 0x00, 0x28, 0x01, 0x00, 0x00, 0x00, 0x01, 0x22, 0x27, 0x10, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf1, sizeof(szBuf1));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);

             unsigned char szBuf2[] = {0xaa, 0x00, 0x01, 0x00, 0x28, 0x01, 0x00, 0x00, 0x00, 0x01, 0x22, 0x27, 0x10, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf2, sizeof(szBuf2));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);
             m_iSendCurNum = 0;

             unsigned char szBuf3[] = {0xaa, 0x00, 0x01, 0x00, 0x50, 0x01, 0x00, 0x00, 0x00, 0x01, 0x2c, 0x27, 0x10, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf3, sizeof(szBuf3));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);
             m_iSendCurNum = 0;

             pTimerTrack->start(1150);

         }

         if(strInfo.compare(tr("梯形轨迹2")) == 0) //轨迹11
         {
             unsigned char szBuf[] = {0xaa, 0x00, 0x00, 0x00, 0x6e, 0x01, 0x00, 0x00, 0x00, 0x01, 0x4a, 0x27, 0x10, 0x02, 0x00, 0xff};
             QByteArray arr = QByteArray((char*)szBuf, sizeof(szBuf));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);

             unsigned char szBuf1[] = {0xaa, 0x00, 0x00, 0x00, 0x28 , 0x01, 0x00, 0x00, 0x00, 0x01, 0x0e, 0x27, 0x10, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf1, sizeof(szBuf1));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);

             unsigned char szBuf2[] = {0xaa, 0x00, 0x01, 0x00, 0x28, 0x01, 0x00, 0x00, 0x00, 0x01, 0x0e, 0x27, 0x10, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf2, sizeof(szBuf2));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);
             m_iSendCurNum = 0;

             unsigned char szBuf3[] = {0xaa, 0x00, 0x01, 0x00, 0x6e, 0x01, 0x00, 0x00, 0x00, 0x01, 0x4a, 0x27, 0x10, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf3, sizeof(szBuf3));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);
             m_iSendCurNum = 0;

             pTimerTrack->start(1150);

         }

         if(strInfo.compare(tr("弧形轨迹")) == 0) //轨迹12
         {
             unsigned char szBuf[] = {0xaa, 0x00, 0x00, 0x00, 0xa0, 0x01, 0x00, 0x00, 0x00, 0x01, 0x4a, 0x27, 0x10, 0x02, 0x00, 0xff};
             QByteArray arr = QByteArray((char*)szBuf, sizeof(szBuf));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);

             unsigned char szBuf1[] = {0xaa, 0x00, 0x00, 0x00, 0xa0, 0x01, 0x00, 0x00, 0x00, 0x01, 0x04, 0x27, 0x10, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf1, sizeof(szBuf1));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);

             unsigned char szBuf2[] = {0xaa, 0x00, 0x00, 0x00, 0x50, 0x01, 0x00, 0x8b, 0x00, 0x01, 0x04, 0x27, 0x10, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf2, sizeof(szBuf2));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);
             m_iSendCurNum = 0;

             unsigned char szBuf3[] = {0xaa, 0x00, 0x01, 0x00, 0x50, 0x01, 0x00, 0x8b, 0x00, 0x01, 0x04, 0x27, 0x10, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf3, sizeof(szBuf3));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);
             m_iSendCurNum = 0;

             unsigned char szBuf4[] = {0xaa, 0x00, 0x01, 0x00, 0xa0, 0x01, 0x00, 0x00, 0x00, 0x01, 0x04, 0x27, 0x10, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf4, sizeof(szBuf4));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);
             m_iSendCurNum = 0;

             unsigned char szBuf5[] = {0xaa, 0x00, 0x01, 0x00, 0xa0, 0x01, 0x00, 0x00, 0x00, 0x01, 0x4a, 0x27, 0x10, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf5, sizeof(szBuf5));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);
             m_iSendCurNum = 0;

             unsigned char szBuf6[] = {0xaa, 0x00, 0x01, 0x00, 0xa0, 0x01, 0x00, 0x00, 0x00, 0x01, 0x4a, 0x27, 0x10, 0x02, 0x00, 0xff};
             arr = QByteArray((char*)szBuf6, sizeof(szBuf6));
             arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
             m_vecArrSend.push_back(arr);
             m_iSendCurNum = 0;

             pTimerTrack->start(1150);

         }
     });

     connect(ui->pushButtonOpenPump, &QPushButton::clicked, [=](){
        AddText("打开气泵", false);
        unsigned char szBuf[] = {0xaa, 0x07, 0x01, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
        QByteArray arr = QByteArray((char*)szBuf, sizeof(szBuf));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);

     });

     connect(ui->pushButtonClosePump, &QPushButton::clicked, [=](){
        AddText("关闭气泵", false);
        unsigned char szBuf[] = {0xaa, 0x07, 0x00, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
        QByteArray arr = QByteArray((char*)szBuf, sizeof(szBuf));
        arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
        m_vecPointArrSend.push_back(arr);

     });

     connect(ui->pushButtonStop, &QPushButton::clicked, [=](){
         AddText("急停", false);
         //只发送一次（发送三条）：
         //aa 01 09 55 55 55 55 55 55 55 55 55 55 01 校验 ff
         //aa 02 09 55 55 55 55 55 55 55 55 55 55 01 校验 ff
         //aa 03 09 55 55 55 55 55 55 55 55 55 55 02 校验 ff
         unsigned char szBuf[] = {0xaa, 0x01, 0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
         QByteArray arr = QByteArray((char*)szBuf, sizeof(szBuf));
         arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
         m_vecPointArrSend.push_back(arr);

         unsigned char szBuf1[] = {0xaa, 0x02, 0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
         arr = QByteArray((char*)szBuf1, sizeof(szBuf1));
         arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
         m_vecPointArrSend.push_back(arr);

         unsigned char szBuf2[] = {0xaa, 0x03, 0x09, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x02, 0x00, 0xff};
         arr = QByteArray((char*)szBuf2, sizeof(szBuf2));
         arr[arr.size()-2] = (GetCrcSum(arr.data()+1, arr.size()-3));
         m_vecPointArrSend.push_back(arr);
         m_iCurPointNum = 0;

         pTimerPoint->start(200);
     });

//     for(int i = 0; i < g_lstInfo.size(); i++)
//     {
//        ui->comboBoxTrack->insertItem(i, g_lstInfo.at(i).strName);
//     }
}




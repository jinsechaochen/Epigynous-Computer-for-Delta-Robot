#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include "com.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    //串口打开关闭按钮触发的方法
	void OpenPushButton();

	void StopPointRun();

    void SetTimer();

    void SetPointButton();

    void SetInchButton();

    //设置COM相关
    void SetComButton();

    void SetResetButton();

private:
    Ui::Widget *ui;

    //串口管理类
    Com* m_pCom = new Com;
	QTimer* pTimerInch = new QTimer;

    QVector<QByteArray> m_vecPointArrSend;
    int m_iCurPointNum = 0;
	QTimer* pTimerPoint = new QTimer;

    QTimer* pTimerTrack = new QTimer;
    QVector<QByteArray> m_vecArrSend;
    int m_iSendCurNum = 0;

public slots:

    //槽函数
    void RecvInfoFromSerialSlot(QByteArray);
	void SendInfoFromSerialSlot(QByteArray);
	void AddText(QString strInfo, bool bRecv = true);

private:

};

#endif // WIDGET_H

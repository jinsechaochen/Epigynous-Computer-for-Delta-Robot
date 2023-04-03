#ifndef CALCFUNC_H
#define CALCFUNC_H

#include <QObject>

class CalcFunc : public QObject
{
    Q_OBJECT
public:
    explicit CalcFunc(QObject *parent = nullptr);

signals:

public slots:
};

#endif // CALCFUNC_H
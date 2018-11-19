#ifndef CALENDAR_H
#define CALENDAR_H

#include <QObject>
#include <QBasicTimer>

class Calendar : public QObject
{
    Q_OBJECT

public:
    Calendar();

protected:
    void timerEvent(QTimerEvent *e) override;

private:
    QBasicTimer timer;

signals:
    void changeSeason(bool t);
};

#endif // CALENDAR_H

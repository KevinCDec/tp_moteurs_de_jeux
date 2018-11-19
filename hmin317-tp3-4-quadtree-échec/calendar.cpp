#include "calendar.h"




Calendar::Calendar()
{
    timer.start(2500,this);

}


void Calendar::timerEvent(QTimerEvent *e){
    emit(changeSeason(true));
}

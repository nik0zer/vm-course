#include "method.h"
#ifndef INSTRACTION_H
#define INSTRACTION_H


//Подумай сегодня-завтра как хорошо сделать инструкции 
// чтоб их можно было нормально исполнять через диспатч таблицу

namespace Frame
{

class Method;

}

namespace Instraction
{



class Instr
{
public:
    Frame::RegType rd, rs1, rs2;

};


}

#endif
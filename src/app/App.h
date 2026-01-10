//-----------------| App.h
//
//
//--------------------------------------------------

#ifndef T_APP
#define T_APP

#include <Arduino.h>

class App{
    private:
    public:
        virtual String getMain() = 0;
        virtual String getOption() = 0;
};

#endif
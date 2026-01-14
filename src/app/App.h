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
        virtual String getMain() = 0;       // Get the main title for display
        virtual String getOption() = 0;     // Get the second line for display
        virtual bool handleEvent(char input) = 0;
        virtual App *nextApp() = 0;
};

#endif
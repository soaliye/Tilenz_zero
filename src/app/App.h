//-----------------| App.h
//
//
//--------------------------------------------------

#ifndef T_APP
#define T_APP

#include <Arduino/h>

class App{
    private:
        String name;
    public:
        App(String appName);
        uint8_t eventHandler(char event);
        ~App();
};


#endif
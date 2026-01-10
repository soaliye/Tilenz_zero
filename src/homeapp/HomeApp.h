//-----------------| HomeApp.h
//
//
//--------------------------------------------------

#ifndef T_HOMEAPP
#define T_HOMEAPP

#include <Arduino.h>
#include <RtcDS1302.h>
#include <ThreeWire.h>
#include "../app/App.h"

class HomeApp: public App{
    private:
        RtcDS1302<ThreeWire> &clock;
        String &username;

        String main;
        String option;
        RtcDateTime now;
    public:
        HomeApp(RtcDS1302<ThreeWire> &clk, String &usrname): App(), clock(clk), username(usrname){}
        String getMain();
        String getOption();
};

#endif
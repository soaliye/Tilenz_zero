//-----------------| HomeApp.cpp
//
//
//--------------------------------------------------

#include "HomeApp.h"

String HomeApp::getMain(){
    main = username;
    return main;
}

String HomeApp::getOption(){
    now = clock.GetDateTime();
    
    char dateTimeBuffer[17];
    snprintf(dateTimeBuffer, sizeof(dateTimeBuffer), "%02u/%02u/%04u %02u:%02u", 
            now.Day(), now.Month(), now.Year(), now.Hour(), now.Minute());

    //option = now.Day() +"/"+ now.Month() +"/"+ now.Year() +" "+ now.Hour() +":"+ now.Minute();
    //return option;
    return dateTimeBuffer;
}
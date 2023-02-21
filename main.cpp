#include <iostream>
#include <thread>
#include "logger.h"

int main()
{
    Logger log("log_file");
    std::thread t1([&](){
        log.Log(Logger::info,"this is info");
    });
    std::thread t2([&](){
        log.Log(Logger::warning,"this is warning");
    });
    std::thread t3([&](){
       log.Log(Logger::error,"this is error");
    });
    
    //log<<"Info message";

    //Logger log2("LogFile",Logger::error);
    //log2<<"Error message";

    t1.join();
    t2.join();
    t3.join();
    return 0;
}
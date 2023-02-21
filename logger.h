#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <mutex>
    
class Logger
{

    std::mutex mtx;
    public:
    enum level{
        info,
        warning,
        error
    };

    Logger(level lev=info):l_level(lev){};

    Logger(const std::string& filename,level lev=info)
    :l_filename(filename),l_level(lev)
    {
        l_file.open(l_filename);
    }

    ~Logger()
    {
        if(l_file.is_open())
            l_file.close();
    }

    void Log(level lev,std::string message)
    {
        auto t=std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(t);
        std::lock_guard<std::mutex> g(mtx);
        switch (lev)
        {
        case info:
            std::cout<<"\033[0;32m[INFO]"<<"    ";
            std::cout<<"["<<std::put_time(std::localtime(&time),"%Y-%m-%d %X")<<"]"<<" ";
            std::cout<<__func__<<" ";
            std::cout<<message<<"\033[0m"<<std::endl;
            if(l_file.is_open())
            {
                l_file<<"[INFO]"<<"    ";
                l_file<<"["<<std::put_time(std::localtime(&time),"%Y-%m-%d %X")<<"]"<<" ";
                l_file<<message<<std::endl;
            }
            break;
        case warning:
            std::cout<<"\033[0;33m[WARNING]"<<" ";
            std::cout<<"["<<std::put_time(std::localtime(&time),"%Y-%m-%d %X")<<"]"<<" ";
            std::cout<<message<<"\033[0m"<<std::endl;
            if(l_file.is_open())
            {
                l_file<<"[WARNING]"<<" ";
                l_file<<"["<<std::put_time(std::localtime(&time),"%Y-%m-%d %X")<<"]"<<" ";
                l_file<<message<<std::endl;
            }
            break;
        case error:
            std::cout<<"\033[0;31m[ERROR]"<<"   ";
            std::cout<<"["<<std::put_time(std::localtime(&time),"%Y-%m-%d %X")<<"]"<<" ";
            std::cout<<message<<"\033[0m"<<std::endl;
            if(l_file.is_open())
            {
                l_file<<"[ERROR]"<<"   ";
                l_file<<"["<<std::put_time(std::localtime(&time),"%Y-%m-%d %X")<<"]"<<" ";
                l_file<<message<<std::endl;
            }
            break;    
        default:
            break;
        }
    }

    Logger& operator<<(const std::string& mes)
    {
        Log(l_level,mes);
        return *this;
    }

    private:
    std::string l_filename;
    std::ofstream l_file;
    level l_level;
};
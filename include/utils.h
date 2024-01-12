#pragma once
#include<iostream>
#include<string>
namespace dy{
    enum ErrorType{
        OPTION_ERROR,
        FATAL_ERROR,
        SYNTAX_ERROR,
        RUNTIME_ERROR
    };
    void dy_error(ErrorType error_type,const std::string &msg);
}
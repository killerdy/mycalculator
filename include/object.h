#pragma once
#include <variant>
#include <cinttypes>
#include <exception>
#include <iostream>
#include <string>
#include <utils.h>
class Object
{
public:
    enum TypeID
    {
        NullTy,
        IntTy,
        FloatTy
    };
    Object() : obj(std::monostate{}) {}
    Object(int64_t val) : obj(val) {}
    Object(int val) : obj(val) {}
    Object(double val) : obj(val) {}
    Object operator+(const Object &rhs) const
    {
        int ty_flag = 0;
        ty_flag |= (rhs.obj.index() - 1) << 0;
        ty_flag |= (obj.index() - 1) << 1;
        switch (ty_flag)
        {
        case 0:
            return rhs.int_val() + int_val();
        case 1:
            return rhs.double_val() + (double)int_val();
        case 2:
            return (double)rhs.int_val() + double_val();
        case 3:
            return rhs.double_val() + double_val();
        default:
            return 0;
            // dy::dy_error(dy::ErrorType::FATAL_ERROR,"wrong");
        }
    }
    Object operator-(const Object &rhs) const
    {
        int ty_flag = 0;
        ty_flag |= (rhs.obj.index() - 1) << 1;
        ty_flag |= (obj.index() - 1) << 2;
        switch (ty_flag)
        {
        case 0:
            return rhs.int_val() - int_val();
        case 1:
            return rhs.double_val() - (double)int_val();
        case 2:
            return (double)rhs.int_val() - double_val();
        case 3:
            return rhs.double_val() - double_val();
        default:
            return 0;
        }
    }
    Object operator*(const Object &rhs) const
    {
        int ty_flag = 0;
        ty_flag |= (rhs.obj.index() - 1) << 1;
        ty_flag |= (obj.index() - 1) << 2;
        switch (ty_flag)
        {
        case 0:
            return rhs.int_val() * int_val();
        case 1:
            return rhs.double_val() * (double)int_val();
        case 2:
            return (double)rhs.int_val() * double_val();
        case 3:
            return rhs.double_val() * double_val();
        default:
            return 0;
        }
    }
    Object operator/(const Object &rhs) const
    {
        int ty_flag = 0;
        ty_flag |= (rhs.obj.index() - 1) << 1;
        ty_flag |= (obj.index() - 1) << 2;
        switch (ty_flag)
        {
        case 0:
            return rhs.int_val() / int_val();
        case 1:
            return rhs.double_val() / (double)int_val();
        case 2:
            return (double)rhs.int_val() / double_val();
        case 3:
            return rhs.double_val() / double_val();
        default:
            return 0;
        }
    }
    int64_t int_val() const
    {
        return std::get<int64_t>(obj);
    }
    double double_val() const
    {
        if (get_typeid() == IntTy)
            return (double)int_val();
        return std::get<double>(obj);
    }
    TypeID get_typeid() const
    {
        return (TypeID)obj.index();
    }
    std::string to_string();

private:
    std::variant<std::monostate, int64_t, double> obj;
};
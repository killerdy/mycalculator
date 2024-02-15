#include <object.h>
#include <string>
std::string Object::to_string()
{
    if (get_typeid() == IntTy)
        {
            return std::to_string(int_val());
        }
    else if(get_typeid()==FloatTy)
    return std::to_string(double_val());
    else return "";
}

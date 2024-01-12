#include <utils.h>
namespace dy
{
    void dy_error(ErrorType error_type, const std::string &msg)
    {
        switch (error_type)
        {
        case FATAL_ERROR:
            std::cout << "\033[31m error \033[0m" + msg << std::endl;
            exit(1);
        case SYNTAX_ERROR:
        case OPTION_ERROR:
            std::cout << "\033[31m  error \033[0m" << msg << std::endl;
            exit(1);
        default:
            std::cout << "\033[31m  error \033[0m:"
                      << "unknown error" << std::endl;
            exit(1);
        }
    }
}
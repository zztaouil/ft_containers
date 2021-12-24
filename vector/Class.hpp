#ifndef CLASS_HPP
# define CLASS_HPP

# include <stdexcept>
# include <iostream>

static int brr = 0;
static int destructed = 0;

class Class{
    public:
    class errror : public std::exception{
        public:
            virtual const char *what(void) const throw(){
                return "errroor";
            }
    };
        Class(void) : _g(69){
            std::cout << "Default Constructor" << std::endl;
            if (brr == 5)
                throw std::out_of_range("sadasd");
            // brr++;
        }
        Class(const Class &rhs){
            std::cout << "Copy Constructor" << std::endl;
            (void)rhs; 
            if (brr == 5)
                throw std::out_of_range("asdasda ");
            brr++;
        }
        ~Class(void){
            destructed++;
        }

    int _g;

};

std::ostream&    operator<<(std::ostream& os, const Class& clss)
{
    os << clss._g;
    return os;
}

#endif
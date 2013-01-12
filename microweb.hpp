#include <string>
#include <iostream>
#include <sstream>
#include <iterator>
#include <stdlib.h>

//using namespace std;
using std::ostream;
using std::ostringstream;
using std::cout;
using std::dec;
using std::hex;
using std::endl;

#if 1
class string: public std::string
{
public:
    string(const char *s) : std::string(s) {};
    string(const std::string& s) : std::string(s) {};

    operator int() { return atoi(c_str()); }
};
#endif

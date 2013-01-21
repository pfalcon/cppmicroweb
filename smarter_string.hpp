#ifndef _SMARTER_STRING_HPP
#define _SMARTER_STRING_HPP
#include <string>
#include <boost/algorithm/string.hpp>

class String: public std::string
{
public:
    String() : std::string() {};
    String(char *s) : std::string(s) {};
    String(const char *s) : std::string(s) {};
    String(const std::string& s) : std::string(s) {};
    String(const String& s) : std::string(s) {};
    template<class InputIterator> String(InputIterator begin, InputIterator end) : std::string(begin, end) {}

    operator int() { return atoi(c_str()); }
    String strip() { return boost::trim_copy(*this); }
    String substr(int beg, int end = 0)
    {
        if (end <= 0)
            end = this->length() + end - 1;
        return this->std::string::substr(beg, end);
    }
//    vector<string> split() { return boost::trim_copy(*this); }
};

#endif //_SMARTER_STRING_HPP

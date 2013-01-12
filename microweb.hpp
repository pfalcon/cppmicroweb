#include <string>
#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <stdlib.h>
#include "pcre++.h"

//using namespace std;
using std::ostream;
using std::ostringstream;
using std::cout;
using std::dec;
using std::hex;
using std::endl;

using pcrepp::Pcre;

#if 1
class string: public std::string
{
public:
    string() : std::string() {};
    string(const char *s) : std::string(s) {};
    string(const std::string& s) : std::string(s) {};

    operator int() { return atoi(c_str()); }
};
#endif

template <typename T>
class vector : public std::vector<T>
{
public:
        vector& append(T item) { this->push_back(item); return *this; }
//        vector& append(const T&)
};

void route(ostream& out, const string& path);

template<typename T>
static inline std::ostream& operator<<(std::ostream& out, std::vector<T> const& v)
{
    out << '[';
    if (!v.empty()) {
        typedef std::ostream_iterator<T> out_iter;
        copy(v.begin(), v.end() - 1, out_iter(out, ", "));
        out << v.back();
    }
    out << ']';
    return out;
}

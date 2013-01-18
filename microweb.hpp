#ifndef _MICROWEB_HPP
#define _MICROWEB_HPP
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <stdlib.h>
#include <ostream_container.hpp>
#include <anyvalue.hpp>
#include "pcre++.h"

//using namespace std;
using std::ostream;
using std::ostringstream;
using std::cout;
using std::dec;
using std::hex;
using std::endl;

using pcrepp::Pcre;

#if 0
template <typename T>
class vector : public std::vector<T>
{
public:
        vector& append(T item) { this->push_back(item); return *this; }
//        vector& append(const T&)
};
#else
using std::vector;
#endif

void route(ostream& out, const String& path);

#endif //_MICROWEB_HPP

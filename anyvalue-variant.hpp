#include <vector>
#include <list>
#include <map>
#define BOOST_VARIANT_NO_FULL_RECURSIVE_VARIANT_SUPPORT
#include <boost/variant.hpp>
#include "smarter_string.hpp"
#include <iostream>
#include "ostream_container.hpp"

typedef boost::make_recursive_variant<
    int,
    double,
//    std::string,
    String,
    std::vector< boost::recursive_variant_ >,
    std::list< boost::recursive_variant_ >,
    std::map< boost::recursive_variant_, boost::recursive_variant_ >
>::type Val_;

class Val;
typedef std::vector<Val> Vector;
typedef std::list<Val> List;
typedef std::map<Val, Val> Map;

class Val
{
public:
    Val_ _v;
    Val() : _v() {}
//    Val2(Val2& v) : Val((Val)v) {}
    Val(int v) : _v(v) {}
    Val(const char *v) : _v(v) {}
    Val(String v) : _v(v) {}
//    Val(Val& v) : _v(v) {}
    Val(const Map& v) : _v(v) {}
//    Val2(Map v) : _v(v) {}

    Val& operator [](String s) {
        Map m = boost::get<Map>(_v);

//        return Val2(m[s]);
    }
};

bool operator<(const Val& x, const Val& y)
{
    switch (x._v.which()) {
    case 2:
        return boost::get<String>(x._v) < boost::get<String>(y._v);
    }

    return true;
}

std::ostream& operator <<(std::ostream& out, const Val& val)
{
    out << val._v;
    return out;
}

#include <vector>
#include <list>
#include <map>
#define BOOST_VARIANT_NO_FULL_RECURSIVE_VARIANT_SUPPORT
#include <boost/variant.hpp>
#include "smarter_string.hpp"
//#include "ostream_container.hpp"

typedef boost::make_recursive_variant<
    int,
    double,
//    std::string,
    String,
    std::vector< boost::recursive_variant_ >,
    std::list< boost::recursive_variant_ >,
    std::map< boost::recursive_variant_, boost::recursive_variant_ >
>::type Val;

typedef std::vector<Val> Vector;
typedef std::list<Val> List;
typedef std::map<Val, Val> Map;

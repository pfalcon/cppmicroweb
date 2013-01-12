#include <string>
#include <iostream>
#include <sstream>
#include <iterator>
#include "pcre++.h"

using namespace std;
using namespace pcrepp;

template<typename T>
std::ostream& operator<<(std::ostream& out, std::vector<T> const& v)
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



class UrlParams
{
protected:
    const Pcre& pcre_;
public:
    UrlParams(const Pcre& pcre) : pcre_(pcre) {};
    string named(const string& name, const string& def=NULL) const { return pcre_.named(name, def); }
    string no(int idx) const { return pcre_.get_match(idx); }
};
//typedef Pcre& UrlParams;

string index(UrlParams p)
{
    string eol = "\n";
    return "foo" + eol;
}

string num(UrlParams p)
{
    ostringstream buf;
    buf << "Number is: " << hex << 42 << ' ' << dec << p.named("val", "NaN") << endl;
    return buf.str();
}

typedef string (*handler_t)(UrlParams p);

struct Route
{
    const char *regexp;
    handler_t handler;
};

Route routes[] = {
    {"/num/(?<val>[0-9]+)?", num},
    {"/", index},
    {NULL}
};

string route(const string path)
{
    string out;
    for (Route *r = routes; r->regexp; r++) {
        Pcre regexp(r->regexp, PCRE_ANCHORED);
        if (regexp.search(path)) {
            out = r->handler(UrlParams(regexp));
            break;
        }
    }
    return out;
}

int main(int argc, char *argv[])
{
    cout << route(argv[1]);
}

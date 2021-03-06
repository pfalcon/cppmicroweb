#include "microweb.hpp"
#include "pcre++.h"

using namespace pcrepp;

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

void index(ostream& out, UrlParams p)
{
    string eol = "\n";
    out << "foo" + eol;
}

void num(ostream& out, UrlParams p)
{
    out << "Number is: " << hex << 42 << ' ' << dec << p.named("val", "NaN") << endl;
}

void iter(ostream& out, UrlParams p)
{
    int val = p.named("val", "10");
    vector<int> vec;
    for (int i = 0; i < val; i++)
        vec.append(i);
    #include "iter.tpl.render"
}

typedef void (*handler_t)(ostream& out, UrlParams p);

struct Route
{
    const char *regexp;
    handler_t handler;
};

Route routes[] = {
    {"/num/(?<val>[0-9]+)?", num},
    {"/iter/(?<val>[0-9]+)?", iter},
    {"/", index},
    {NULL}
};

void route(ostream& out, const string& path)
{
    for (Route *r = routes; r->regexp; r++) {
        Pcre regexp(r->regexp, PCRE_ANCHORED);
        if (regexp.search(path)) {
            r->handler(out, UrlParams(regexp));
            break;
        }
    }
}

#if 0
int main(int argc, char *argv[])
{
    ostringstream buf;
    route(buf, argv[1]);
    cout << buf.str();
}
#endif

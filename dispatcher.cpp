#include <string>
#include <iostream>
#include <sstream>
#include "pcre++.h"

using namespace std;
using namespace pcrepp;

typedef Pcre& UrlParams;

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

string route(string path)
{
    string out;
    for (Route *r = routes; r->regexp; r++) {
        Pcre regexp(r->regexp, PCRE_ANCHORED);
        if (regexp.search(path)) {
//        if (path == r->regexp) {
            out = r->handler(regexp);
            break;
        }
    }
    return out;
}

int main(int argc, char *argv[])
{
    cout << route(argv[1]);
}

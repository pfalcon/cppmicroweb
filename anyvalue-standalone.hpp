#include <vector>
#include <list>
#include <map>
#include "smarter_string.hpp"
#include <iostream>
#include "ostream_container.hpp"

class Val;
typedef std::vector<Val> Vector;
typedef std::list<Val> List;
typedef std::map<Val, Val> Map;

class Val
{
public:
    enum Type {UNK, EMPTY, INT, STRING, VECTOR, LIST, MAP};
    int _type;
    int _int;
    String _string;
    Vector _vector;
    List _list;
    Map _map;

    Val() : _type(EMPTY) {}
    Val(int v) : _type(INT), _int(v) {}
    Val(const char *v) : _type(STRING), _string(v) {}
    Val(String v) : _type(STRING), _string(v) {}
    Val(Vector v) : _type(VECTOR), _vector(v) {}
    Val(List v) : _type(LIST), _list(v) {}
    Val(Map v) : _type(MAP), _map(v) {}

    class IndexError : std::exception
    {
        const char *msg;
    public:
        IndexError(const char *s) : msg(s) {}
    };

    Val& operator [](int i) {
        switch (_type) {
        case Val::STRING:
            if (i >= _string.length())
                throw IndexError("string index out of range");
            {
            Val* a = new Val(_string.substr(i, 1));
            return *a;
            }
        case Val::VECTOR:
            return _vector.Vector::operator[](i);
        case Val::MAP:
            return _map.Map::operator[](i);
        default:
            throw IndexError("Undefined operator[int]");
        }
    }

    Val& operator [](String s) {
        return _map.Map::operator[](s);
    }
};

bool operator<(const Val& x, const Val& y)
{
    switch (x._type) {
    case Val::STRING:
        return x._string < y._string;
    }

    return true;
}

std::ostream& operator<<(std::ostream& out, const Val& val)
{
    switch (val._type) {
    case Val::EMPTY:
        out << "None";
        break;
    case Val::INT:
        out << val._int;
        break;
    case Val::STRING:
        out << val._string;
        break;
    case Val::VECTOR:
        out << val._vector;
        break;
    case Val::LIST:
        out << val._list;
        break;
    case Val::MAP:
        out << val._map;
        break;
    default:
        out << "UNK<" << val._type << ">";
    }
    return out;
}

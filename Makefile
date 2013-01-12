CXX = g++-4.7
CXXFLAGS = -std=c++11
LDFLAGS = -L.
LDLIBS = -lpcre++ -lpcre

dispatcher: dispatcher.cpp tpl.cpp microweb.hpp


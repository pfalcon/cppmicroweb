CXX = g++-4.7
CXXFLAGS = -std=c++11
LDFLAGS = -L.
LDLIBS = -lpcre++ -lpcre

%.cpp: %.tpl
	python jinja2cpp.py $^

dispatcher: dispatcher.cpp iter.cpp

dispatcher: microweb.hpp

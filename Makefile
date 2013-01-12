CXX = g++-4.7
CXXFLAGS = -std=c++11
LDFLAGS = -L.
LDLIBS = -lpcre++ -lpcre

%.tpl.cpp: %.tpl
	python jinja2cpp.py $^

dispatcher: dispatcher.cpp iter.tpl.cpp

dispatcher: microweb.hpp

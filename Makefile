CXX = g++-4.7
CXXFLAGS = -std=gnu++11
LDFLAGS = -L.
LDLIBS = -lpcre++ -lpcre -lpthread -ldl

%.tpl.cpp: %.tpl
	python jinja2cpp.py $^

dispatcher: dispatcher.cpp mongoose-handler.cpp mongoose/mongoose.o iter.tpl.cpp

mongoose/mongoose.o: mongoose/mongoose.c

dispatcher: microweb.hpp

parse_iwlist: parse_iwlist.cpp

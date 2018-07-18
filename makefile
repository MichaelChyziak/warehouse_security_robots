#SUBDIRS := $(wildcard */.)
#
#.PHONY : all $(SUBDIRS)
#
#all:	$(SUBDIRS)
#
#$(SUBDIRS) :
#	$(MAKE) -C $@ clean all
#

CXX := g++

# Can add sources here
SRCS=warehouse_security_robots.cc graph/graph.cc graph/edge.cc graph/node.cc
OBJS=$(subst .cc,.o,$(SRCS))

all: warehouse_security_robots

%.o: %.cpp
	$(CXX) -c $< -o $@

%.o: %.hpp
	$(CXX) -c $< -o $@

warehouse_security_robots: $(OBJS)
	$(CXX) $(LDFLAGS) -o warehouse_security_robots $(OBJS) $(LDLIBS)

clean:
	rm -f $(OBJS)
	rm -f warehouse_security_robots

.PHONY : all clean

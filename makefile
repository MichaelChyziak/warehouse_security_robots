CXX := g++

# Can add sources here
SRCS=graph/graph.cc chinese_postman/chinese_postman.cc dijkstra/dijkstra.cc robots/robots.cc
OBJS=$(subst .cc,.o,$(SRCS))

all: warehouse_security_robots chinese_test

warehouse_security_robots: $(OBJS)
	$(CXX) -o warehouse_security_robots warehouse_security_robots.cc $(OBJS)

chinese_test: $(OBJS)
	$(CXX) -o chinese_postman_test chinese_postman_test.cc $(OBJS)

robots_test: $(OBJS)
	$(CXX) -o robots_test robots_test.cc $(OBJS)

clean:
	rm -f $(OBJS)
	rm -f warehouse_security_robots
	rm -f chinese_postman_test
	rm -f robots_test

.PHONY : all clean

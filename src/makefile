TARGET = test_main

OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp) )

all: $(TARGET)

$(TARGET): $(OBJS)
	g++ -g -o $@ $(OBJS) -lpthread

.cpp.o:
	g++ -g -c $<

clean:
	rm -f *.o
	rm -f *.gcda *.gcno
	rm -f test_main


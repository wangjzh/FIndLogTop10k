main : test_topx.cpp TopX.o LogsCount.o ThreadPool.o
	g++ -g -o main test_topx.cpp TopX.o LogsCount.o ThreadPool.o -lpthread
ThreadPool.o : ThreadPool.cpp ThreadPool.h
	g++ -g -c ThreadPool.cpp
TopX.o : TopX.h TopX.cpp LogInfor.h
	g++ -g -c TopX.cpp
LogsCount.o: LogsCount.h LogsCount.cpp LogInfor.h
	g++ -g -c LogsCount.cpp
clean:
	rm -rf main *.o *.gch

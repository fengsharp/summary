all:
	@#clang++ -g -Wall ztest_01_Atomic.cpp -o out.01
	@#clang++ -g -Wall Thread.cpp ztest_02_Thread.cpp -o out.02 -lpthread
	@#clang++ -g -Wall Exception.cpp Thread.cpp ThreadPool.cpp ztest_03_Threadpool.cpp -o out.03 -lpthread
	@#clang++ -g -Wall Exception.cpp Thread.cpp ThreadPool.cpp ztest_04_ThreadLocal.cpp -o out.04 -lpthread
	@#clang++ -g -Wall Exception.cpp Thread.cpp ThreadPool.cpp ztest_05_Singleton.cpp -o out.05 -lpthread
	@#clang++ -g -Wall Exception.cpp Thread.cpp ThreadPool.cpp ztest_06_SingletonThreadLocal.cpp -o out.06 -lpthread
	@#clang++ -g -Wall Exception.cpp Thread.cpp ThreadPool.cpp ztest_07_ThreadLocalSingleton.cpp -o out.07 -lpthread
	@#clang++ -g -Wall Exception.cpp Thread.cpp ThreadPool.cpp ztest_08_Exception.cpp -o out.08 -lpthread
	@#clang++ -g -Wall Exception.cpp Thread.cpp ThreadPool.cpp ztest_09_Observer.cpp -o out.09 -lpthread
	@#clang++ -g -Wall Exception.cpp Thread.cpp ThreadPool.cpp ztest_10_SelfDeadLock.cpp -o out.10 -lpthread
	@#clang++ -g -Wall Exception.cpp Thread.cpp ThreadPool.cpp ztest_11_BlockingQueue.cpp -o out.11 -lpthread
	clang++ -g -Wall EventLoop.cpp Exception.cpp Thread.cpp ThreadPool.cpp ztest_100_eventloop.cpp -o out.100 -lpthread
	
clean:
	rm -fr out.*
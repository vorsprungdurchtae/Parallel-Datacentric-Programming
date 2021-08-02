build: tsqueue.cpp
	$(CXX) -std=c++11 -lpthread -g tsqueue.cpp -o tsqueue.exe

solution: tsqueue-sol.cpp
	$(CXX) -fsanitize=thread -std=c++11 -lpthread -g tsqueue-sol.cpp -o tsqueue-sol.exe

tsan: tsqueue.cpp
	$(CXX) -fsanitize=thread -std=c++11 -lpthread -g tsqueue.cpp -o tsqueue_tsan.exe

clean:
	rm -rf core*, *.exe

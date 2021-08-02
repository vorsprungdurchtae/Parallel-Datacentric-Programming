build: access.cpp
	$(CXX) -std=c++11 -lpthread -g access.cpp -o access.exe

tsan: access.cpp
	$(CXX) -fsanitize=thread -std=c++11 -lpthread -g access.cpp -o access_tsan.exe

clean:
	rm -rf core*, *.exe

server:server.cpp 
	g++ -std=c++11 $^ -o $@ -L/usr/include -L/lib64/mysql -ljsoncpp -lmysqlclient -lpthread
main:main.cpp
	g++ -std=c++11 $^ -o $@ -L/usr/include -L/lib64/mysql -ljsoncpp -lmysqlclient 
json:json.cpp
	g++ -std=c++11 $^ -o $@ -L/usr/include -ljsoncpp

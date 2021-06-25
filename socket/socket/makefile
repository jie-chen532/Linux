all:tcp_cli tcp_process
tcp_process:tcp_process.cpp 
	g++ $^ -o $@
tcp_thread:tcp_thread.cpp 
	g++ $^ -o $@ -lpthread
tcp_cli:tcp_cli.cpp 
	g++ $^ -o $@
tcp_ser:tcp_ser.cpp 
	g++ $^ -o $@
udp_cli:udp_cli.cpp
	g++ $^ -o $@
udp_ser:udp_ser.cpp   
	g++ $^ -o $@

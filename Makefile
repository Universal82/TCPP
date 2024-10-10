Client: ./src/client.cpp
	g++ ./src/client.cpp -o Client
Server: ./src/server.cpp
	g++ ./src/server.cpp -o Server
Main: ./src/client.cpp
	g++ ./src/tcp.cpp ./main.cpp -o Main
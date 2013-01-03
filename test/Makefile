all: hello tcpclient tcpserver

hello: hello.c
	gcc -o hello hello.c
tcpclient: tcpclient.c
	gcc -o tcpclient tcpclient.c
tcpserver: tcpserver.c
	gcc -o tcpserver tcpserver.c
clean:
	rm -f hello
	rm -f tcpclient
	rm -f tcpserver

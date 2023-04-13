.PHONY: all

all: dcl_echo_srv_abs dcl_echo_srv

dcl_echo_srv_abs: unix_abstract_socket_server.c
	gcc -o $@ $^

dcl_echo_srv: unix_socket_server.c
	gcc -o $@ $^

install: dcl_echo_srv dcl_echo_srv_abs
	install -m 755 dcl_echo_srv ${DESTDIR}
	install -m 755 dcl_echo_srv_abs ${DESTDIR}

clean:
	rm -f dcl_echo_srv dcl_echo_srv_abs

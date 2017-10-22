.PHONY: all install clean

all: bin/mydaemon

install: bin/mydaemon conf/systemd/mydaemon.service
	cp bin/mydaemon /usr/sbin/mydaemon
	cp conf/systemd/mydaemon.service /etc/systemd/system/mydaemon.service
	systemctl enable mydaemon

liveinstall: bin/mydaemon conf/systemd/mydaemon.service
	systemctl stop mydaemon
	cp bin/mydaemon /usr/sbin/mydaemon
	cp conf/systemd/mydaemon.service /etc/systemd/system/mydaemon.service
	systemctl daemon-reload
	systemctl start mydaemon
	php -d zend.assertions=1 -d assert.exception=1 ./doc/simpletest.php 

clean:
	rm -rf bin/

bin/mydaemon: src/*.cpp src/*.h
	mkdir -p bin
	g++ -Wall src/*.cpp -pthread -lfcgi++ -lfcgi -std=gnu++14 -o bin/mydaemon
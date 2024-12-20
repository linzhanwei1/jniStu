TARGET = HelloWorld

all:
	javac -h . C.java
	gcc -shared -I/usr/lib/jvm/java-11-openjdk-amd64/include -I/usr/lib/jvm/java-11-openjdk-amd64/include/linux -fPIC -o libHelloWorld.so HelloWorld.c	
	export LD_LIBRARY_PATH=.

.PHONY: clean run
clean:
	rm -rf *.so *.class *.h
run:
	@java -Djava.library.path=. C
TARGET = ObjectArray

all:
	javac -h . ${TARGET}.java
	gcc -shared -I/usr/lib/jvm/java-11-openjdk-amd64/include -I/usr/lib/jvm/java-11-openjdk-amd64/include/linux -fPIC -o lib${TARGET}.so ${TARGET}.c	
	export LD_LIBRARY_PATH=.

.PHONY: clean run
clean:
	rm -rf *.so *.class *.h
run:
	@java ${TARGET}

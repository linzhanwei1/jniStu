TARGET = ConstructorCall

all:
	javac -h . ${TARGET}.java
	javap -s -p ${TARGET}
	export LD_LIBRARY_PATH=.
	gcc -shared -I/usr/lib/jvm/java-11-openjdk-amd64/include -I/usr/lib/jvm/java-11-openjdk-amd64/include/linux -fPIC -o lib${TARGET}.so ${TARGET}.c	

.PHONY: clean run
clean:
	rm -rf *.so *.class *.h
run:
	@java -Djava.library.path=. ${TARGET}

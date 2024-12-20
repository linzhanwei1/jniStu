TARGET = invoke

all:
	cc -I/usr/lib/jvm/java-11-openjdk-amd64/include -I/usr/lib/jvm/java-11-openjdk-amd64/include/linux -L/usr/lib/jvm/java-11-openjdk-amd64/lib/server/ -o ${TARGET} ${TARGET}.c -lpthread -ljvm
	javac Prog.java
.PHONY: clean run
clean:
	rm -rf ${TARGET} *.class
run:
	export LD_LIBRARY_PATH=/usr/lib/jvm/java-11-openjdk-amd64/lib/server
	./${TARGET}

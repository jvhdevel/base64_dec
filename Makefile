SOURCES=$(wildcard *.cpp)
OBJECTS=$(addprefix build/,${SOURCES:.cpp=.o})

BINARY=base64_dec

all: dirs out/${BINARY}

out/${BINARY}: ${OBJECTS}
	g++ -o $@ $^

build/%.o: %.cpp
	g++ -c -O2 -o $@ $<

.PHONY: dirs
dirs:
	mkdir -p build/
	mkdir -p out/

.PHONY: clean
clean:
	-rm -r build/
	-rm -r out/

.PHONY: all clean

all: input output
	zip data.zip *.in *.out

input:
	g++ -O2 -o generator -std=c++17 generator.cpp
	./generator
	bash copy-hardcoded.sh

output:
	bash ./make-output.sh

clean:
	-rm generator
	-rm *.in *.out data.zip

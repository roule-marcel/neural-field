all: neural-field test_spike plot

neural-field: bin/main.o
	gcc -o $@ $^ -lm

test_spike: bin/test_spike.o
	gcc -o $@ $^ -lm

plot: bin/plot.o
	gcc -o $@ $^ -lm -ljpeg


bin/%.o: src/%.c
	mkdir -p `dirname $@`
	gcc -std=c99 -o $@ -c $<

clean:
	rm -rf bin
	rm -f neural-field test_spike plot

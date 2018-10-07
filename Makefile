utf8validate: utf8validate.c include/simdutf8check.h
	cc -std=c99 -march=native -O3 -Wall -o utf8validate utf8validate.c -Iinclude
clean:
	rm -r -f utf8validate

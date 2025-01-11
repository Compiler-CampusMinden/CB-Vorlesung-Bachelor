all: vars refs expr ifthenelse while func

%: %.cpp driver.h
	g++ -include driver.h $<
	./a.out

clean:
	rm -rf a.out *.~

.PHONY: all clean

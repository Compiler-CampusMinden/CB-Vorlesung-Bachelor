all: vars refs expr

%: driver.cpp %.cpp
	g++ $< -D$@
	./a.out

clean:
	rm -rf a.out *.~

.PHONY: all clean

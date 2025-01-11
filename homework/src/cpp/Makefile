all: vars refs expr ctrlflow

%: driver.cpp %.cpp
	g++ $< -D$@
	./a.out

clean:
	rm -rf a.out *.~

.PHONY: all clean

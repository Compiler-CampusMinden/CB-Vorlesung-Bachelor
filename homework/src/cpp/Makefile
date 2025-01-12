## Ausführen der Testfälle mit dem g++
##
## "make"     => führt alle Tests aus
## "make xyz" => führt die Test in der Datei xyz.cpp aus
##
## Beachten Sie auch die auskommentierten Tests - diese sollten von Ihrem
## Interpreter bzw. Compiler zurückgewiesen werden (analog zum g++/clang)!


all: vars refs expr ifthenelse while func class inheritance polymorphie

%: %.cpp driver.h
	g++ -include driver.h $<
	./a.out

clean:
	rm -rf a.out *.~

.PHONY: all clean

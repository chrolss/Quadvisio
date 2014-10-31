CXXFLAGS += -g -Wall -O2

demo: demo.cpp BMP085.o
	$(CXX) $(CXXFLAGS) demo.cpp BMP085.o -o demo

BMP085.o: BMP085.cpp BMP085.hpp

clean:
	@-rm *.o *.a *.so *.gch
	@-rm test demo a.out

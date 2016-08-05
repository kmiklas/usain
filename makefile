CXX=g++
CXXFLAGS=-std=c++11
TARGET=usain

$(TARGET):
	$(CXX) ./*.cpp -o $(TARGET) $(CXXFLAGS)

clean:
	rm -f *.o

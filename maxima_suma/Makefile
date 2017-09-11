TARGET=maxima_suma

all: $(TARGET)

$(TARGET): $(TARGET).cc
	g++ -Wall -std=c++11 $< -o $@

clean:
	rm -rf $(TARGET)

# Compiler and Flags
CXX = g++
CXXFLAGS = -Wall -O2 -I/raylib
LDFLAGS = -L/raylib -lraylib -lm -lpthread -ldl -lrt -lX11

# Target Executable
TARGET = mygame

# Source Files
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)


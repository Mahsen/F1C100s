# Compiler
CXX = ../buildroot-sinux/output/host/bin/arm-buildroot-linux-gnueabi-g++
# Compiler flags
CXXFLAGS = -Wall -g -pthread
# Build dir
BUILD_DIR = Build
# Target executable
TARGET = $(BUILD_DIR)/Application
# Source files
SRCS = *.cpp \
	Module/*.cpp \
	Driver/*.c \
	Core/*.c

all:
	clear
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) 
	cp $(TARGET) ../buildroot-sinux/board/mahsen/sinux/f1/rootfs/root/
	
clean:
	del $(TARGET)

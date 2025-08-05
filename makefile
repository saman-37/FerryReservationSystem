# Makefile for Ferry Reservation System

CXX = g++
CXXFLAGS = -Wall -std=c++17
OBJS = main.o UI.o Util.o Vehicle.o Vessel.o Reservation.o Sailing.o SailingControl.o OtherControls.o

# Default target
all: ferry topdowntest

# Build main system
ferry: $(OBJS)
	$(CXX) $(CXXFLAGS) -o ferry $(OBJS)

# Build top-down test driver
topdowntest: TopDownTestDriver.o Util.o Vehicle.o Vessel.o Reservation.o Sailing.o SailingControl.o OtherControls.o
	$(CXX) $(CXXFLAGS) -o topdowntest TopDownTestDriver.o Util.o Vehicle.o Vessel.o Reservation.o Sailing.o SailingControl.o OtherControls.o

# Compile individual .cpp files to .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f *.o ferry topdowntest
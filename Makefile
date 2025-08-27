CXX = g++
CXXFLAGS = -std=c++17 -I. -IContainers -IMenu -ISequences -ISequences/Mutable -ISequences/Immutable
TARGET = lab2.exe
SOURCES = main.cpp
HEADERS = \
	Containers/DynamicArray.h \
	Containers/LinkedList.h \
	Menu/Menu.h \
	Menu/tests.h \
	Sequences/Sequence.h \
	Sequences/ArraySequence.h \
	Sequences/ListSequence.h \
	Sequences/Mutable/MutableArraySequence.h \
	Sequences/Mutable/MutableListSequence.h \
	Sequences/Immutable/ImmutableArraySequence.h \
	Sequences/Immutable/ImmutableListSequence.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCES)

clean:
	del $(TARGET) 2>nul || true

.PHONY: all clean

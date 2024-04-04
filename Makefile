# Variables
CXX = /usr/bin/clang++
CXXFLAGS = -std=c++20 -fcolor-diagnostics -fansi-escape-codes -g -pg
SFML_INCDIR = /opt/homebrew/Cellar/sfml/2.5.1_2/include
SFML_LIBDIR = /opt/homebrew/Cellar/sfml/2.5.1_2/lib
GLOG_INCDIR = /opt/homebrew/Cellar/glog/0.6.0/include
GLOG_LIBDIR = /opt/homebrew/Cellar/glog/0.6.0/lib
GFLAGS_INCDIR = /opt/homebrew/Cellar/gflags/2.2.2/include
GFLAGS_LIBDIR = /opt/homebrew/Cellar/gflags/2.2.2/lib
INCDIR = ./include
SRCDIR = ./src
BINDIR = ./bin
TARGET = $(BINDIR)/chess
# Source and Object Files
SOURCES = $(wildcard $(SRCDIR)/*.cpp $(SRCDIR)/classes/*.cpp $(SRCDIR)/classes/pieces/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
# Default target
all: $(TARGET)
# Build rule
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) \
		-I$(SFML_INCDIR) \
		-I$(GLOG_INCDIR) \
		-I$(GFLAGS_INCDIR) \
		-I$(INCDIR) \
		-L$(SFML_LIBDIR) \
		-L$(GLOG_LIBDIR) \
		-L$(GFLAGS_LIBDIR) \
		$^ -o $@ -lglog -lsfml-graphics -lsfml-window -lsfml-system
# Rule for object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(SFML_INCDIR) -I$(GLOG_INCDIR) -I$(GFLAGS_INCDIR) -I$(INCDIR) -c $< -o $@
# Clean
clean:
	rm -f $(OBJECTS) $(TARGET)
# Run
run: all
	./$(TARGET)
.PHONY: all clean run default
TARGET = bin/haffmanCode
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)
	del /F /Q $(subst /,\,$(OBJECTS))

$(TARGET): $(OBJECTS)
	g++ $^ -o $@

src/%.o: src/%.cpp
	g++ -c $^ -o $@

.PHONY: clean
clean:
	del /F /Q $(subst /,\,$(OBJECTS)) $(subst /,\,$(TARGET))
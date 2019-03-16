CC = g++
CPPFLAGS = -pedantic-errors -std=c++11 -Iinclude
EXE = account

CPP = $(wildcard src/*.cpp)

OBJ = $(CPP:%.cpp=obj/%.o)

DEP = $(OBJ:%.o=%.d)

all: bin/$(EXE)

bin/$(EXE): $(OBJ)
	$(CC) $^ -o $@

-include $(DEP)

obj/%.o: %.cpp
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) -MMD -c $< -o $@

.PHONY: clean

clean: 
	@rm -f $(OBJ) bin/$(EXE) $(DEP)
	@echo Clean done!

run:
	./bin/Release/$(EXE)

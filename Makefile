INCLUDE_DIR=. ./headers/private/ ./headers/public/
SRC_DIR=. ./src

CC=g++
OPT=-O0

# Generate files that encode make rules for the .h dependencies
DEP_FLAGS=-MP -MD

OUTPUT=output_exe

# Automatically add the -I onto each include directory eg(-I.  -I./Test/includes/)
CFLAGS=$(foreach DIR, $(INCLUDE_DIR), -I$(DIR)) $(OPT) $(DEP_FLAGS) -std=c++14

# Finding all .cpp files in the src directories
CPP_FILES=$(foreach DIR, $(SRC_DIR), $(wildcard $(DIR)/*.cpp))

# regular expression replacement using pattern-substitution
# Generate object files for all .cpp files
OBJECT_FILES=$(patsubst %.cpp, %.o, $(CPP_FILES))

# Generate dependency .d files this will re compile if a header is changed.
DEP_FILES=$(patsubst %.cpp, %.d, $(CPP_FILES))

all: $(OUTPUT)
	echo $(CFLAGS)
	echo $(CPP_FILES)
	echo $(OBJECT_FILES)
	echo $(DEP_FILES)

$(OUTPUT): $(OBJECT_FILES)
	$(CC) -o $@ $^
	mkdir -p build/obj build/dep build/bin
	mv $(OBJECT_FILES) build/obj
	mv $(DEP_FILES) build/dep
	mv $(OUTPUT) build/bin
	
# only want the .cpp file dependency here, thus $< instead of $^.
%.o:%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OUTPUT) $(OBJECT_FILES) $(DEP_FILES) build/
CC = g++

PRGGRAM_NAME = \
	 bin/Main

CXXFLAGS = \
	 -MMD \
	 -Wall \
	 -Wextra \
	 -Wno-deprecated \
	 -g \
	 -std=c++11 \

LDLIBS = \
	-pthread \

INCLUDE_PATH= \
	 /usr/include/ \
	 ./precomp/ \
	 ./src/ \

INCLUDE_PATH := $(addprefix -I,$(INCLUDE_PATH))

INCLUDE := $(addprefix -include ,$(INCLUDE))

# Files

SRCDIR += \
	 ./src \

CPP_FILES = $(wildcard $(addsuffix /*.cpp,$(SRCDIR)))
HEADER_FILES = $(wildcard src/*.h)

OBJECTS = $(addprefix obj/,$(CPP_FILES:.cpp=.o))
PRECOMPILE_HEADER = $(addprefix precomp/,$(HEADER_FILES:.h=.h.gch))
DEPENDS = $(addsuffix .d,$(OBJECTS))

# Targets

all: $(PRGGRAM_NAME)

$(PRGGRAM_NAME) : $(OBJECTS)
	@echo "LD	$@"
	@mkdir -p $(dir $@)
	@$(CC) -o $@ $(OBJECTS) $(LDLIBS) 

obj/%.o : %.cpp
	@echo "CC 	$<"
	@mkdir -p $(dir $@)
	@g++ $(CXXFLAGS) -MF $@.d $(INCLUDE_PATH) $(INCLUDE) -c -o $@ $<

precompile: $(PRECOMPILE_HEADER)

demangle: $(PRGGRAM_NAME)
	@./bin/Main | c++filt --types

.PHONY: all clean precompile demangle

clean:
	@echo "RM	$(PRECOMPILE_HEADER)"
	@rm -f $(PRECOMPILE_HEADER)
	@echo "RM	$(OBJECTS)"
	@rm -f $(OBJECTS) 
	@echo "RM	$(DEPENDS)"
	@rm -f $(DEPENDS)
	@echo "RM	$(PRGGRAM_NAME)"
	@rm -f $(PRGGRAM_NAME)

-include $(DEPENDS)

PROJECT = sfml

SOURCES = src/main.cpp src/Element.cpp src/Store.cpp src/Sources.cpp src/FrontElement.cpp src/Vector2.cpp src/Wave.cpp
INCLUDES += -I include
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
DEFINES =
CFLAGS = #-Wall -Wextra
COMP = g++

OBJS = $(SOURCES:.cpp=.o)

CFLAGS += $(DEFINES) $(INCLUDES) $(DEFINES)

RM = rm -rf

.PHONY: all clean tags

link: $(OBJS)
	$(COMP) -o $(PROJECT) $(OBJS) $(LIBS)

all: clean link

clean:
	$(RM) $(PROJECT) $(OBJS)

%.o: %.cpp
	$(COMP) $(CFLAGS) -c $(@:.o=.cpp) -o $@

tags:

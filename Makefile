CC		= gcc
CFLAGS	= -g -Wall 
RM		= rm

CSRCS	= main.c game_of_life.c
TARGET	= game_of_life_openMP
OBJECTS	= $(CSRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
		$(CC) $(OBJECTS) -o $@ 

.c.o:
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) -f $(OBJECTS) $(TARGET) *~
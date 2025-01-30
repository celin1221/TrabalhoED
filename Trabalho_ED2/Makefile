CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Nome do executável
TARGET = gerador

# Arquivos fonte
SRCS = main.c gerador.c

# Arquivos objeto
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: all
	./$(TARGET)

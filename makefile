CC=gcc
CFLAGS=-Wall -Wextra -Werror -lm -pedantic

#aqui metes o binario
TARGET = guiao04
#aqui metes todos os .c
SRCS = ./src/guiao04.c ./src/functions.c
OBJS = $(SRCS:.c=.o)

# Regras
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o ./bin/$@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)


# Limpeza de arquivos temporários
clean:
	rm -f $(OBJS) $(TARGET)
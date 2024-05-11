CC=gcc
CFLAGS=-Wall -Wextra -Werror -lm -pedantic# -pg -g -O

#aqui metes o binario
TARGET = guiao04v2
#aqui metes todos os .c
SRCS = src/guiao04v2.c src/functions.c
OBJS = $(SRCS:.c=.o)

# Regras
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o ./bin/$@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


# Limpeza de arquivos temporários
clean:
	rm -f $(OBJS) $(TARGET)

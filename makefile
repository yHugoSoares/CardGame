CC=gcc
CFLAGS=-Wall -Wextra -Werror -lm -pedantic -pg -g -O

#aqui metes o binario
TARGET = guiaoFinal
#aqui metes todos os .c
SRCS = src/guiaoFinal.c src/functions.c
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

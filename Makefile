# Компилятор C
CC = gcc

# Флаги компиляции
CFLAGS = -Wall -Wextra -Wpedantic -O2 -std=c11

# Цель по умолчанию
all: c-prog

# Сборка исполняемого файла
c-prog: main.c
    $(CC) $(CFLAGS) $^ -o $@

# Очистка временных файлов
clean:
    rm -f c-prog

.PHONY: clean
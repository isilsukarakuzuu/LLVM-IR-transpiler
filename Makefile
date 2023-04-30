CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -g

default:
		$(CC) $(CFLAGS) -o advcalc2ir ./src/AdvCalc.c
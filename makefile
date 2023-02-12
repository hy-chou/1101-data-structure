# ******************************************************************************
# File       [makefile]
# Author     [HsuanYu CHOU]
# Synopsis   [The makefile for PM program]
# Modify     [2021-12-26 HsuanYu CHOU]
# ******************************************************************************

CC = g++
CFLAGS = -Wall -Werror -Wextra -c
OFLAGS = -O2

all	: pm

pm	: hychou_pm.o hychou_main.o
	$(CC) $(OFLAGS) hychou_pm.o hychou_main.o -o pm
hychou_main.o	: hychou_main.cpp
	$(CC) $(CFLAGS) $(OFLAGS) $< -o $@
hychou_pm.o	: hychou_pm.cpp hychou_pm.h
	$(CC) $(CFLAGS) $(OFLAGS) $< -o $@

.PHONY : clean fclean test

clean:
	rm *.o pm
fclean:
	rm -rf *.o pm

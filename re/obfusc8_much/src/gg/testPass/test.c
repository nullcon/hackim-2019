/*
 * untitled.c
 *
 * Copyright 2018 Sudhakar Verma <sudhakar@payatu>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */


#include <stdio.h>

char msg[] = "AAAAAAAAAAAAAAAA";

int sum(int x, int y){
    return x+y;
}

int fib(int n){
    if(!n)
        return 0;
    if(n == 1 || n == 2)
        return 1;
    return fib(n-1)+fib(n-2);
}

int main(int argc, char **argv)
{
    int i;
    for (i = 0; i < 16; ++i)
    {
        printf("%d:", sum(i, 3));
    }
    printf("%s\n", msg);

    for (i = 0; i < 16; ++i)
    {
        printf("%d:", fib(i));
    }
    printf("%s\n", msg);
	return 0;
}


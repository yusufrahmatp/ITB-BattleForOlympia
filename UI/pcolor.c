/**
Filename: pcolor.c (implementation of pcolor.h)
Description: Print character with some color in terminal
Prepared by: Asisten IF2110
Created at: 30/10/2017
**/

#include <stdio.h>
#include "pcolor.h"

void print_char_red(char c) {
    printf("%s%c%s", RED, c, NORMAL);
}

void print_char_green(char c) {
    printf("%s%c%s", GREEN, c, NORMAL);
}

void print_char_yellow(char c) {
    printf("%s%c%s", YELLOW, c, NORMAL);
}

void print_char_blue(char c) {
    printf("%s%c%s", BLUE, c, NORMAL);
}

void print_char_magenta(char c) {
    printf("%s%c%s", MAGENTA, c, NORMAL);
}

void print_char_cyan(char c) {
    printf("%s%c%s", CYAN, c, NORMAL);
}

void print_red(char * s) {
    printf("%s%s%s", RED, s, NORMAL);
}

void print_green(char * s) {
    printf("%s%s%s", GREEN, s, NORMAL);
}

void print_yellow(char * s) {
    printf("%s%s%s", YELLOW, s, NORMAL);
}

void print_blue(char * s) {
    printf("%s%s%s", BLUE, s, NORMAL);
}

void print_magenta(char * s) {
    printf("%s%s%s", MAGENTA, s, NORMAL);
}

void print_cyan(char * s) {
    printf("%s%s%s", CYAN, s, NORMAL);
}

void print_const_under(const char c[5]) {
    printf("%s%s", c, NORMAL);
}

void print_const_under_red(const char c[5]) {
    printf("%s%s%s%s", UNDERLINE, RED, c, NORMAL);
}

void print_const_under_green(const char c[5]) {
    printf("%s%s%s%s", UNDERLINE, GREEN, c, NORMAL);
}

void print_const_under_yellow(const char c[5]) {
    printf("%s%s%s%s", UNDERLINE, YELLOW, c, NORMAL);
}

void print_const_under_blue(const char c[5]) {
    printf("%s%s%s%s", UNDERLINE, BLUE, c, NORMAL);
}

void print_const_under_magenta(const char c[5]) {
    printf("%s%s%s%s", UNDERLINE, MAGENTA, c, NORMAL);
}

void print_const_under_cyan(const char c[5]) {
    printf("%s%s%s%s", UNDERLINE, CYAN, c, NORMAL);
}

#ifndef _TTY_UTILS_H_
#define _TTY_UTILS_H_
#include "project.h"
 
void tty_init(void) ;

void print(char *str) ;

/**
 * get_string()
 * check if we received any char via tty
 * and store the char into str[]
 * when a delimiter is detected
 * it puts NULL at the current end of str[] and return the length of str
 * if the length is exceeding that STR_BUF_LEN,
 * it puts NULL at the end of str[] and returns -1 
 */
int get_string(void) ;

/**
 * get_line() 
 * similar with get_string() but only accept CR or LF for delimiter
 * so you can get a line up to the STR_BUF_LEN 
 */
int get_line(void) ;

void splash(char *prog_name) ;

void prompt(void) ;

extern char str[] ; /* print buf */

#endif /* _TTY_UTILS_H_ */

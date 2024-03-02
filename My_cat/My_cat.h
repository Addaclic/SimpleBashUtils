/**
 * \mainpage The **cat utility** is used to concatenate and display the contents
 *           of one or more files.
 *
 * \author Andrey addaclic
 * \copyright GNU Public License
 */

#ifndef MY_CAT_H
#define MY_CAT_H

#ifdef __linux__
#define LETTERS_CASE "benstvET"
#else
#define LETTERS_CASE "+benstvET"
#endif

#include <getopt.h>
#include <stdio.h>

/**
 * @brief Struct for storing options conditions reading from the command line
 */
typedef struct {
  char e;
  char n;
  char s;
  char t;
  char v;
  char b;
} my_cat_opt;

/**
 * @brief Function for parsing options from the command line
 * @param int first argument of the function argc
 * @param char_ptr second argument of the function argv
 * @param my_cat_opt third argument of the function that contains options
 * @return a condition of success or failure
 */
int parse_opts(int, char *[], my_cat_opt *);

/**
 * @brief Read and print file
 * @param int first argument of the function argc
 * @param char_ptr second argument of the function argv
 * @param my_cat_opt third argument of the function that contains options
 */
void output_file(int, char *[], my_cat_opt);

/**
 * @brief Print text with options
 * @param FILE_ptr first argument of the function that contains file data
 * @param my_cat_opt second argument of the function that contains options
 */
void print_text(FILE *, my_cat_opt);

#endif  // MY_CAT_H
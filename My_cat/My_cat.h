/**
 * \mainpage The **cat utility**
 * \file
 * \brief This utilitie is used to concatenate and display the contents
 *        of one or more files andprovide powerful text manipulation
 *        capabilities in the bash shell
 * \version 0.1
 * \todo Tests & Bugfix
 * \author Andrey addaclic
 * \copyright GNU Public License
 */

#ifndef MY_CAT_H
#define MY_CAT_H

#ifdef __linux__
#define LETTERS_CASE "+benstvET"
#else
#define LETTERS_CASE "benstvET"
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
 * @param[in] argc first argument of the function count of arguments
 * @param[in] argv second argument of the function lists of names of arguments
 * @param[out] my_cat_opt third argument of the function that contains options
 * @return a condition of success or failure of parsing
 */
int parse_opts(int, char *[], my_cat_opt *);

/**
 * @brief Read and print file in commond line
 * @param[in] argc first argument of the function "argc"
 * @param[in] argv second argument of the function "argv"
 * @param[in] my_cat_opt third argument of the function that contains options
 */
void output_file(int, char *[], my_cat_opt);

/**
 * @brief Print text with given options
 * @param FILE_ptr first argument of the function that contains file data
 * @param my_cat_opt second argument of the function that contains options
 */
void print_text(FILE *, my_cat_opt);

#endif  // MY_CAT_H
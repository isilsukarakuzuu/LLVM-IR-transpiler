#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "variables.h"

bool debug = false;
bool error = false;
bool check = true; // checks if the input file has no syntax errors and undefined variables
const char *operators = "+-*&|/_";
// % --> _
char *reserved_functions[] = {"xor", "not", "ls", "rs", "lr", "rr"};
// xor --> ^, ls --> <, rs --> >, lr --> [, rr --> ]
const char *new_operators = "^~<>[]";
int temp_count = 1;

FILE *fp;  // input file
FILE *fp2; // output file

// function declarations

// function to print the error message if debug is true
void debug_printer(char *error_message)
{
  if (debug)
  {
    printf("error:%s\n", error_message);
  }
}

// function to print the array if debug is true
void array_printer(char *array, int length)
{
  if (debug)
  {
    for (int i = 0; i < length; i++)
    {
      printf("%c ", array[i]);
    }
    printf("\n");
  }
}

// function to find the index of the last operator in the operator array, returns -1 if no operator is found
// by finding the last, we obtain a left associative rule
int index_finder(char *input, int length, char *operator_array)
{
  // returns the index of the first operator in the operator array
  for (int i = length - 1; i >= 0; i--)
  {
    for (int j = 0; operator_array[j] != '\0'; j++)
    {
      if (input[i] == operator_array[j])
      {
        return i;
      }
    }
  }
  return -1;
}

int contains_valid_chars(char *input)
{
  int i = 0;
  for (i = 0; input[i] != '\0'; i++)
  {
    // checks if the character is a digit
    if (input[i] >= '0' && input[i] <= '9')
    {
      continue;
    }
    // check if the character is lowercase letter
    if (input[i] >= 'a' && input[i] <= 'z')
    {
      continue;
    }
    // check if the character is uppercase letter
    if (input[i] >= 'A' && input[i] <= 'Z')
    {
      continue;
    }
    // check if the character is a space
    if (input[i] == ' ' || input[i] == '\t')
    {
      continue;
    }
    // check if the character is in given another set of valid characters
    char *valid_chars = "(),+*-&|=/%%";
    if (strchr(valid_chars, input[i]) != NULL)
    {
      continue;
    }
    return 0;
  }
  return 1;
}

int are_spaces_placed_correctly(char *input)
{
  // checks if the input has spaces in the correct places
  for (int i = 1; input[i] != '\0'; i++)
  {
    if (input[i] == ' ' || input[i] == '\t')
    {

      if (!(isalpha(input[i - 1]) || isdigit(input[i - 1])))
      {
        continue;
      }
      while ((input[i] == ' ' || input[i] == '\t') && input[i] != '\0')
      {
        i++;
      }
      if (!(isalpha(input[i]) || isdigit(input[i])))
      {
        continue;
      }
      return 0;
    }
  }
  return 1;
}

int space_deleter(char *input)
{
  // deletes all the spaces in the input
  int i = 0;
  int j = 0;
  while (input[i] != '\0')
  {
    if (input[i] != ' ' && input[i] != '\t')
    {
      input[j] = input[i];
      j++;
    }
    i++;
  }
  input[j] = '\0';
  return 1;
}

int variable_checker(char *input, int length)
{
  // checks if the input is not empty
  if (length == 0)
  {
    return 0;
  }

  // checks if the input has only uppercase and lowercase letters
  for (int i = 0; i < length; i++)
  {
    if (input[i] >= 'a' && input[i] <= 'z')
    {
      continue;
    }
    if (input[i] >= 'A' && input[i] <= 'Z')
    {
      continue;
    }
    return 0;
  }

  // checks if the input is not exactly one of the reserved words
  for (int i = 0; i < 6; i++)
  {
    char *var = (char *)calloc((length + 1), sizeof(char));
    var[length] = '\0';

    // copy input to var
    for (int j = 0; j < length; j++)
    {
      var[j] = input[j];
    }

    if (!strcmp(var, reserved_functions[i]))
    {
      free(var);
      return 0;
    }
    free(var);
  }
  return 1;
}

// checks if the input has a valid integer value
char *value_checker(char *input, int length)
{
  // checks if the input is not empty
  if (length == 0)
  {
    return "-1";
  }

  // checks if the input has only digits
  for (int i = 0; i < length; i++)
  {
    if (input[i] >= '0' && input[i] <= '9')
    {
      continue;
    }
    return "-1";
  }

  char *value2 = (char *)calloc((length + 1), sizeof(char));
  value2[length] = '\0';
  for (int i = 0; i < length; i++)
  {
    value2[i] = input[i];
  }
  return value2;
}

// controls if the input is a assignment or expression
int is_it_a_equation(char *input)
{
  // checks if the input has only 1 equal sign
  int count = 0;
  int length = 0;
  for (int i = 0; input[i] != '\0'; i++)
  {
    if (input[i] == '=')
    {
      length = i;
      count++;
    }
  }
  if (count == 1)
  {
    if (length == 0)
    {
      debug_printer("No variable name before the equal sign.");
      error = true;
      return -1;
    }
    return length;
  }
  if (count > 1)
  {
    debug_printer("More than one equal sign.");
    error = true;
    return -1;
  }
  return 0;
}

int are_parantheses_placed_correctly(char *input)
{
  // checks if the input has equal number of ( and )
  int count = 0;
  for (int i = 0; input[i] != '\0'; i++)
  {
    if (input[i] == '(')
    {
      count++;
    }
    if (input[i] == ')')
    {
      count--;
      if (count < 0)
      {
        return 0;
      }
    }
  }
  if (count == 0)
  {
    return 1;
  }
  return 0;
}

// parses the complex functions in AdvCalc such as: xor, ls, rs, lr, rr, not. replaces the functions with new operators
void function_parser(char *input)
{
  for (int i = 0; input[i] != '\0'; i++)
  {

    if (input[i] != '(')
      continue;

    // itarates the string backwards till its not uppercase or lowercase letter, then it checks the final string is in the reserved functions
    int j = i - 1;
    while (j >= 0 && ((input[j] >= 'a' && input[j] <= 'z') || (input[j] >= 'A' && input[j] <= 'Z')))
    {
      j--;
    }
    j++;
    char *function = calloc((i - j + 1), sizeof(char));
    for (int k = 0; k < i - j; k++)
    {
      function[k] = input[j + k];
    }
    function[i - j] = '\0';
    for (int k = 0; k < 6; k++)
    {
      if (strcmp(function, reserved_functions[k]))
        continue;

      // it replaces the function name chars with space from actual string
      for (int l = j; l < i; l++)
      {
        input[l] = ' ';
      }
      if (k == 1)
      {
        input[i - 1] = '!';
        continue;
      }
      int level = 0;
      int m = i;
      int comma_count = 0;
      int comma_index = -1;
      do
      {
        if (input[m] == '(')
        {
          level++;
        }
        if (input[m] == ')')
        {
          level--;
        }
        if (input[m] == ',' && level == 1)
        {
          comma_count++;
          comma_index = m;
        }
        m++;
      } while (level != 0);
      if (comma_count > 1 || comma_index == -1)
      {
        debug_printer("Invalid number of commas.");
        error = true;
        continue;
      }
      // it replaces the comma with assigned new function operator
      input[comma_index] = new_operators[k];
    }
    free(function);
  }
}

// assigns the register of the parsed expression (by expression_parser), returns the value as a register
char *expression_value_finder(char *input, int length)
{
  if (length == 0)
  {
    debug_printer("Empty input in exp value finder.");
    error = true;
    return 0;
  }
  // check whether the input's first or last char is an operator
  if (strchr(operators, input[0]) != NULL || strchr(operators, input[length - 1]) != NULL)
  {
    debug_printer("Input starts or ends with an operator.");
    error = true;
  }

  // check whether the input has two operators next to each other
  for (int i = 0; i < length - 1; i++)
  {
    if (strchr(operators, input[i]) != NULL && strchr(operators, input[i + 1]) != NULL)
    {
      debug_printer("Two operators next to each other.");
      error = true;
    }
  }
  int index = -1;
  // new operators
  index = index_finder(input, length, "^~<>[]");

  if (index != -1)
  {
    // xor --> ^, not --> ~, ls --> <, rs --> >, lr --> [, rr --> ]
    if (input[index] == '^')
    {
      char *value1 = expression_value_finder(input, index);
      char *value2 = expression_value_finder(input + index + 1, length - index - 1);
      char *temp = (char *)calloc(10, sizeof(char));
      sprintf(temp, "%%%d", temp_count++);
      fprintf(fp2, "%s = xor i32 %s, %s\n", temp, value1, value2);
      free(value1);
      free(value2);
      return temp;
    }
    if (input[index] == '<')
    {
      char *value1 = expression_value_finder(input, index);
      char *value2 = expression_value_finder(input + index + 1, length - index - 1);
      char *temp = (char *)calloc(10, sizeof(char));
      sprintf(temp, "%%%d", temp_count++);
      fprintf(fp2, "%s = shl i32 %s, %s\n", temp, value1, value2);
      free(value1);
      free(value2);
      return temp;
    }
    if (input[index] == '>')
    {
      char *value1 = expression_value_finder(input, index);
      char *value2 = expression_value_finder(input + index + 1, length - index - 1);
      char *temp = (char *)calloc(10, sizeof(char));
      sprintf(temp, "%%%d", temp_count++);
      fprintf(fp2, "%s = ashr i32 %s, %s\n", temp, value1, value2);
      free(value1);
      free(value2);
      return temp;
    }
    if (input[index] == '[')
    {
      char *value1 = expression_value_finder(input, index);
      char *value2 = expression_value_finder(input + index + 1, length - index - 1);
      char *temp1 = (char *)calloc(10, sizeof(char));
      sprintf(temp1, "%%%d", temp_count++);
      fprintf(fp2, "%s = sub i32 32, %s\n", temp1, value2);
      char *temp2 = (char *)calloc(10, sizeof(char));
      sprintf(temp2, "%%%d", temp_count++);
      fprintf(fp2, "%s = shl i32 %s, %s\n", temp2, value1, value2);
      char *temp3 = (char *)calloc(10, sizeof(char));
      sprintf(temp3, "%%%d", temp_count++);
      fprintf(fp2, "%s = lshr i32 %s, %s\n", temp3, value1, temp1);
      char *temp = (char *)calloc(10, sizeof(char));
      sprintf(temp, "%%%d", temp_count++);
      fprintf(fp2, "%s = or i32 %s, %s\n", temp, temp2, temp3);
      free(value1);
      free(value2);
      free(temp1);
      free(temp2);
      free(temp3);
      return temp;
    }
    if (input[index] == ']')
    {
      char *value1 = expression_value_finder(input, index);
      char *value2 = expression_value_finder(input + index + 1, length - index - 1);
      char *temp1 = (char *)calloc(10, sizeof(char));
      sprintf(temp1, "%%%d", temp_count++);
      fprintf(fp2, "%s = sub i32 32, %s\n", temp1, value2);
      char *temp2 = (char *)calloc(10, sizeof(char));
      sprintf(temp2, "%%%d", temp_count++);
      fprintf(fp2, "%s = lshr i32 %s, %s\n", temp2, value1, value2);
      char *temp3 = (char *)calloc(10, sizeof(char));
      sprintf(temp3, "%%%d", temp_count++);
      fprintf(fp2, "%s = shl i32 %s, %s\n", temp3, value1, temp1);
      char *temp = (char *)calloc(10, sizeof(char));
      sprintf(temp, "%%%d", temp_count++);
      fprintf(fp2, "%s = or i32 %s, %s\n", temp, temp2, temp3);
      free(value1);
      free(value2);
      free(temp1);
      free(temp2);
      free(temp3);
      return temp;
    }
  }

  // | operator
  index = index_finder(input, length, "|");

  if (index != -1)
  {
    char *value1 = expression_value_finder(input, index);
    char *value2 = expression_value_finder(input + index + 1, length - index - 1);
    char *temp = (char *)calloc(10, sizeof(char));
    sprintf(temp, "%%%d", temp_count++);
    fprintf(fp2, "%s = or i32 %s, %s\n", temp, value1, value2);
    free(value1);
    free(value2);
    return temp;
  }
  // & operator
  index = index_finder(input, length, "&");

  if (index != -1)
  {
    char *value1 = expression_value_finder(input, index);
    char *value2 = expression_value_finder(input + index + 1, length - index - 1);
    char *temp = (char *)calloc(10, sizeof(char));
    sprintf(temp, "%%%d", temp_count++);
    fprintf(fp2, "%s = and i32 %s, %s\n", temp, value1, value2);
    free(value1);
    free(value2);
    return temp;
  }

  // +-* operators
  index = index_finder(input, length, "+-");

  if (index != -1)
  {
    if (input[index] == '+')
    {
      char *value1 = expression_value_finder(input, index);
      char *value2 = expression_value_finder(input + index + 1, length - index - 1);
      char *temp = (char *)calloc(10, sizeof(char));
      sprintf(temp, "%%%d", temp_count++);
      fprintf(fp2, "%s = add i32 %s, %s\n", temp, value1, value2);
      free(value1);
      free(value2);
      return temp;
    }
    else
    {
      char *value1 = expression_value_finder(input, index);
      char *value2 = expression_value_finder(input + index + 1, length - index - 1);
      char *temp = (char *)calloc(10, sizeof(char));
      sprintf(temp, "%%%d", temp_count++);
      fprintf(fp2, "%s = sub i32 %s, %s\n", temp, value1, value2);
      free(value1);
      free(value2);
      return temp;
    }
  }

  index = index_finder(input, length, "*/_");

  if (index != -1)
  {
    if (input[index] == '*')
    {
      char *value1 = expression_value_finder(input, index);
      char *value2 = expression_value_finder(input + index + 1, length - index - 1);
      char *temp = (char *)calloc(10, sizeof(char));
      sprintf(temp, "%%%d", temp_count++);
      fprintf(fp2, "%s = mul i32 %s, %s\n", temp, value1, value2);
      free(value1);
      free(value2);
      return temp;
    }
    if (input[index] == '/')
    {
      char *value1 = expression_value_finder(input, index);
      char *value2 = expression_value_finder(input + index + 1, length - index - 1);
      char *temp = (char *)calloc(10, sizeof(char));
      sprintf(temp, "%%%d", temp_count++);
      fprintf(fp2, "%s = sdiv i32 %s, %s\n", temp, value1, value2);
      free(value1);
      free(value2);
      return temp;
    }
    if (input[index] == '_')
    {
      char *value1 = expression_value_finder(input, index);
      char *value2 = expression_value_finder(input + index + 1, length - index - 1);
      char *temp = (char *)calloc(10, sizeof(char));
      sprintf(temp, "%%%d", temp_count++);
      fprintf(fp2, "%s = srem i32 %s, %s\n", temp, value1, value2);
      free(value1);
      free(value2);
      return temp;
    }
  }

  if (input[0] == '!')
  {
    char *value = expression_value_finder(input + 1, length - 1);
    char *temp = (char *)calloc(10, sizeof(char));
    sprintf(temp, "%%%d", temp_count++);
    fprintf(fp2, "%s = xor i32 %s, -1\n", temp, value);
    free(value);
    return temp;
  }

  if (input[0] == '%')
  {
    char *var = calloc((length + 1), sizeof(char));
    for (int i = 0; i < length; i++)
    {
      var[i] = input[i];
    }
    var[length] = '\0';
    return var;
  }

  char *value = value_checker(input, length);
  if (strcmp(value, "-1") != 0)
  {
    return value;
  }

  if (variable_checker(input, length))
  {
    return get_variable(input, length, temp_count++, fp2, &error);
  }
  debug_printer("Invalid exp value finder.");
  array_printer(input, length);
  error = true;
  return "-1";
}

// parses the experssion while checking for paranthesis, returns a inner expression, and calls the expression_value_finder function
char *expression_parser(char *input, int length)
{
  debug_printer("expression_parser called.");
  array_printer(input, length);
  char *sub_expr = (char *)calloc(6 * length, sizeof(char));
  int k = 0;
  int level = 0;
  for (int i = 0; i < length; i++)
  {
    if (input[i] == '(')
    {
      int j = i;
      level++;
      while (level != 0)
      {
        j++;
        if (input[j] == '(')
        {
          level++;
        }
        if (input[j] == ')')
        {
          level--;
        }
      }

      char *expression = expression_parser(input + i + 1, (j - 1) - (i + 1) + 1);
      // change temp_count to a string and set it as a variable

      sprintf(sub_expr + k, " %s ", expression);

      // increase k by the number of digits in the expression + 2
      k += strlen(expression) + 2;
      i = j;
      free(expression);
    }
    else
    {
      sub_expr[k] = input[i];
      k++;
    }
  }
  sub_expr[k] = '\0';
  if (!are_spaces_placed_correctly(sub_expr))
  {
    debug_printer("spaces are not placed correctly");
    error = 1;
  }
  space_deleter(sub_expr);
  char *temp = expression_value_finder(sub_expr, strlen(sub_expr));

  free(sub_expr);
  return temp;
}

int main(int argc, char *argv[])
{
  char input[258];
  char *filename;
  char *filename2;
  if (argc < 2)
  {
    return 1;
  }
  else
  {
    filename = argv[1];
  }

  // constructing the output file name
  for (size_t i = 0; i < strlen(filename); i++)
  {
    if (filename[i] == '.')
    {
      filename2 = (char *)calloc((i + 4), sizeof(char));
      filename2[i + 3] = '\0';
      for (size_t j = 0; j < i; j++)
      {
        filename2[j] = filename[j];
      }
      filename2[i] = '.';
      filename2[i + 1] = 'l';
      filename2[i + 2] = 'l';
      break;
    }
  }

  fp = fopen(filename, "r");
  fp2 = fopen(filename2, "w");

  // initializing the output file
  char *init_line = "; ModuleID = 'advcalc2ir'\n";
  char *init_line2 = "declare i32 @printf(i8*, ...)\n";
  char *init_line3 = "@print.str = constant [4 x i8] c\"%d\\0A\\00\"\n";
  char *init_line4 = "define i32 @main() {\n";

  fprintf(fp2, "%s", init_line);
  fprintf(fp2, "%s", init_line2);
  fprintf(fp2, "%s\n", init_line3);
  fprintf(fp2, "%s", init_line4);

  int line_count = 0;
  // reading the input file line by line
  while (true)
  {
    error = false;
    if (fgets(input, sizeof(input), fp) == NULL)
    {
      break;
    }

    line_count++;
    input[strcspn(input, "\n")] = '\0';

    // check whether input is new line
    if (input[0] == '\0')
    {
      continue;
    }

    size_t space_check = 0;
    // check whether input consist only spaces
    for (size_t i = 0; i < strlen(input); i++)
    {
      if (input[i] == ' ' || input[i] == '\t' || input[i] == '\n')
      {
        space_check++;
      }
    }
    if (space_check == strlen(input))
    {
      continue;
    }

    // checks if the input contains only valid characters
    if (!contains_valid_chars(input))
    {
      debug_printer("contains invalid chars");
      printf("Error on line %d!\n", line_count);
      check = false;
      continue;
    }

    // replace all %'s with _
    for (size_t i = 0; i < strlen(input); i++)
    {
      if (input[i] == '%')
      {
        input[i] = '_';
      }
    }

    // checks if the spaces are placed correctly
    if (!are_spaces_placed_correctly(input))
    {
      debug_printer("spaces are not placed correctly");
      array_printer(input, strlen(input));
      printf("Error on line %d!\n", line_count);
      check = false;

      continue;
    }

    // deletes all the spaces in the input
    space_deleter(input);

    // checks the parantheses briefly
    if (!are_parantheses_placed_correctly(input))
    {
      debug_printer("parantheses are not placed correctly");
      printf("Error on line %d!\n", line_count);
      check = false;
      continue;
    }

    int length = is_it_a_equation(input);
    if (error)
    {
      printf("Error on line %d!\n", line_count);
      check = false;
      error = false;
      continue;
    }

    // checks if the input is a equation
    if (length >= 1)
    {
      // checks the left side of the equal sign, it must be a variable
      if (!variable_checker(input, length))
      {
        debug_printer("left side of the equal sign is not a variable");
        printf("Error on line %d!\n", line_count);
        check = false;
        continue;
      }
      function_parser(input);
      space_deleter(input);

      char *result = expression_parser(input + length + 1, strlen(input) - length - 1);
      if (error)
      {
        printf("Error on line %d!\n", line_count);
        check = false;
        error = false;
        continue;
      }
      char *variable = calloc(length + 1, sizeof(char));
      strncpy(variable, input, length);
      variable[length] = '\0';
      set_variable(variable, result, fp2);
      free(result);
      continue;
    }

    function_parser(input);
    space_deleter(input);

    char *result = expression_parser(input, strlen(input));

    if (error)
    {
      printf("Error on line %d!\n", line_count);
      check = false;
      error = false;
      continue;
    }

    fprintf(fp2, "call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %s)\n", result);
    free(result);
    temp_count++;
  }
  fprintf(fp2, "ret i32 0\n");
  fprintf(fp2, "}");
  // free the variables
  free_variables();

  fclose(fp);
  fclose(fp2);
  if (check == false)
  {
    remove(filename2);
  }
  free(filename2);
}
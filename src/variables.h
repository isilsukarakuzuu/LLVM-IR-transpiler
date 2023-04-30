// implement a list for variables, it must hold keys as variables and values as their values

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct variable
{
  char *name;
};

struct variable *variables[256];
int variable_count = 0;

char *get_variable(char *name, int length, int tempcount, FILE *fp2)
{
  for (int i = 0; i < variable_count; i++)
  {
    if (strncmp(variables[i]->name, name, length) == 0)
    {
      char *temp = (char *)calloc(10, sizeof(char));
      sprintf(temp, "%%%d", tempcount);
      char *temp2 = (char *)calloc(10, sizeof(char));
      for (int j = 0; j < length; j++)
      {
        temp2[j] = name[j];
      }
      fprintf(fp2, "%%%d = load i32, i32* %%%s\n", tempcount, temp2);
      // print the name
      return temp;
    }
  }
  return 0;
}

void set_variable(char *name, char *value, FILE *fp2)
{
  for (int i = 0; i < variable_count; i++)
  {
    if (strcmp(variables[i]->name, name) == 0)
    {
      fprintf(fp2, "store i32 %s, i32* %%%s\n", value, name);
      free(name);
      return;
    }
  }
  variables[variable_count] = (struct variable *)calloc(1, sizeof(struct variable));
  fprintf(fp2, "%%%s = alloca i32\n", name);
  fprintf(fp2, "store i32 %s, i32* %%%s\n", value, name);
  variables[variable_count]->name = name;
  variable_count++;
}

void free_variables()
{
  for (int i = 0; i < variable_count; i++)
  {
    free(variables[i]->name);
    free(variables[i]);
  }
}

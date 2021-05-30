#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "esh.h"

char **esh_cpy_arr(const char *const *arr)
{
  size_t len = 0;
  while (arr[len] != NULL)
    len++;
  char **ret = (char **)malloc(sizeof(char *) * (len + 1));
  if (ret != NULL)
  {
    size_t i = 0;
    while (arr[i] != NULL)
    {
      ret[i] = strdup(arr[i]);
      i++;
    }
    ret[i] = NULL;
  }
  return ret;
}

void esh_free_str(char **str)
{
  if (str == (char **)NULL || *str == (char *)NULL)
    return;
  free(*str);
  *str = NULL;
}

void esh_free_str_arr(char ***arr)
{
  size_t i = 0;
  while ((*arr)[i] != NULL)
  {
    free((*arr)[i++]);
  }
  free(*arr);
  *arr = NULL;
}

void esh_print_str(char const *s, int fd) { write(fd, s, strlen(s)); }

void esh_println_str(char const *s, int fd)
{
  esh_print_str(s, fd);
  esh_print_str("\n", fd);
}

void esh_println_str(int i, int fd)
{
  char *s;
  sprintf(s, "%d", i);
  esh_print_str(s, fd);
  esh_print_str("\n", fd);
}

#ifndef ESH_H
#define ESH_H

/* duplicate. */
char** esh_cpy_arr(const char *const *arr);

/* print. */
void esh_print_str(char const *s, int fd);
void esh_println_str(char const *s, int fd);
void esh_println_str(int i, int fd);

/* free. */
void esh_free_str(char **str);
void esh_free_str_arr(char ***arr);

#endif
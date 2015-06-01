/* shameless copy of examples/loadables/mypid.c
 *
 * from mksh's man page:
 * EPOCHREALTIME
 *   Time since the epoch, as returned by gettimeofday(2), formatted as decimal
 *   tv_sec followed by a dot ('.') and tv_usec padded to exactly six decimal digits.
*/

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "builtins.h"
#include "shell.h"
#include <sys/time.h>

#define INIT_DYNAMIC_VAR(var, val, gfunc, afunc) \
  do \
    { SHELL_VAR *v = bind_variable (var, (val), 0); \
      v->dynamic_value = gfunc; \
      v->assign_func = afunc; \
    } \
  while (0)

static SHELL_VAR *
assign_epochrealtime (
     SHELL_VAR *self,
     char *value,
     arrayind_t unused,
     char *key )
{
  return (self);
}


static SHELL_VAR *
get_epochrealtime (SHELL_VAR *var)
{
  struct timeval tv;
  char *output = malloc(18);

  gettimeofday(&tv, NULL);
  sprintf (output, "%d.%d", tv.tv_sec, tv.tv_usec);

  FREE (value_cell (var));

  var_setvalue (var, output);
  return (var);
}

int
enable_epochrealtime_builtin(WORD_LIST *list)
{
  INIT_DYNAMIC_VAR ("EPOCHREALTIME", (char *)NULL, get_epochrealtime, assign_epochrealtime);

  return 0;
}

char const *enable_epochrealtime_doc[] = {
  "Enable $EPOCHREALTIME.",
  "",
  "Time since the epoch, as returned by gettimeofday(2), formatted as decimal",
  "tv_sec followed by a dot ('.') and tv_usec padded to exactly six decimal digits.",
  (char *)0
};

struct builtin enable_epochrealtime_struct = {
  "enable_epochrealtime",
  enable_epochrealtime_builtin,
  BUILTIN_ENABLED,
  (char**)(void*)enable_epochrealtime_doc,
  "enable_epochrealtime",
  0
};

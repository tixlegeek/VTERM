#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "vterm.h"

#include "string.h"


void* printterm(uint8_t* str) {
  printf("|%s|\n", str);
}

int main() {
  vterm_ctx_t* vtermptr = vterm_init(10, 10);
  vterm_goto(vtermptr, 6, 6);
  vterm_write(vtermptr, "Oh Yeah");
  vterm_dumppipe(vtermptr, &printterm);

  return 0;
}

/**
╦  ╦╔╦╗┌─┐┬─┐┌┬┐  A tiny multipurpose virtual term screen, coded with love by
╚╗╔╝ ║ ├┤ ├┬┘│││  Tixlegeek < @tixlegeek - http://www.tixlegeek.io >
 ╚╝  ╩ └─┘┴└─┴ ┴  This code's purpose is to offer a nice, and smart terminal-like
V1.0              display feature. It takes care of everything, just stuff it up
                  with text, and pass it to the dumppiper.                    */
/*
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
*/

#include "vterm.h"
/**
  Create a new vterm context
*/
vterm_ctx_t* vterm_init(uint8_t rows, uint8_t lines) {
  uint8_t i;
  vterm_ctx_t* newctx = (vterm_ctx_t*)malloc(sizeof(vterm_ctx_t));
  if (newctx == NULL)
    return NULL;
  newctx->lines = lines;
  newctx->rows = rows;
  newctx->offset = 0;
  newctx->scroll = 0;
  newctx->status = OFFSET;
  newctx->ltrim = false;

  newctx->buffer = (vterm_line_t**)malloc(lines * sizeof(vterm_line_t*));
  for (i = 0; i <= lines; i++) {
    newctx->buffer[i] = vterm_ctx_createLines(&newctx->rows);
    newctx->buffer[i]->id = i;
  }
  newctx->currentline = newctx->buffer[0];
  return newctx;
}

/**
  Create a new line context
*/
vterm_line_t* vterm_ctx_createLines(uint8_t* rows) {
  vterm_line_t* newline = (vterm_line_t*)malloc(sizeof(vterm_line_t));
  if (newline == NULL)
    return NULL;
  memset(newline, ' ', sizeof(vterm_line_t));

  newline->rows = rows;
  newline->status = OFFSET;
  newline->offset = 0;

  newline->linebuffer = (uint8_t*)malloc(sizeof(uint8_t) * *(newline->rows));
  memset(newline->linebuffer, ' ', *(newline->rows) * sizeof(uint8_t));

  return newline;
}

/**
  Scrolls the vterm down with a line
*/
vterm_action_t vterm_scroll_down(vterm_ctx_t* vterm) {
  vterm->offset++;
  if (vterm->offset >= vterm->lines)
    vterm->offset = 0;

  vterm->scroll++;
  vterm->scroll = vterm->scroll % vterm->lines;

  vterm->currentline = vterm->buffer[vterm->offset];
  vterm->currentline->offset = 0;
  memset(vterm->buffer[vterm->offset]->linebuffer, ' ', vterm->rows);
  return SUCCESS;
}

/**
  Debug the vscreen.
*/
vterm_action_t vterm_debug(vterm_ctx_t* vterm) {
  uint8_t i = 0;
  printf(" %d --------------------------------\n", vterm->scroll);
  for (i = 0; i < vterm->lines; i++) {
    if (vterm->currentline == vterm->buffer[i])
      printf("\033[7m");  // invert for current line ptr
    printf("%d %s\n\033[m", vterm->buffer[i]->id, vterm->buffer[i]->linebuffer);
  }
  printf("--------------------------------\n");
  return SUCCESS;
}

/**
  retrieve the screen structure in a multidimentionnal
  array to be passed to a display function.
*/
uint8_t** vterm_getscreen(vterm_ctx_t* vterm) {
  uint8_t i = 0;
  uint8_t** vtermscreen = (uint8_t**)malloc(sizeof(uint8_t*) * vterm->lines);
  uint8_t index = (vterm->scroll) % (vterm->lines);
  for (i = 0; i < vterm->lines; i++) {
    index = (vterm->scroll + 1 + i) % (vterm->lines);
    vtermscreen[i] = vterm->buffer[index]->linebuffer;
  }
  return vtermscreen;
}
/**
  write a string on the vterm
*/
vterm_action_t vterm_write(vterm_ctx_t* vterm, uint8_t* str) {
  //  uint8_t strl = strlen(str);
  uint8_t* strc = str;
  while ((strc = vterm_writeline(vterm, strc)) != NULL) {
  }
  return SUCCESS;
}

/*
  Place the term's cursor at x/y.
*/
vterm_action_t vterm_goto(vterm_ctx_t* vterm, uint8_t x, uint8_t y) {
  // if(vterm->offset < x)
  vterm->offset = y;
  vterm->currentline = vterm->buffer[vterm->offset];
  vterm->currentline->offset = x;
  vterm->currentline->status = OFFSET;
  return SUCCESS;
}

/*
  Pipe all lines in order, to a callback function.
  The callback is called for each lines. All lines are transmitted
  one at a time.
*/
vterm_action_t vterm_dumppipe(vterm_ctx_t* vterm,
                              vterm_action_t (*out_callback)()) {
  uint8_t** vscreen = vterm_getscreen(vterm);
  while (*(vscreen) != NULL) {
    out_callback(*(vscreen));
    vscreen++;
  }
}
/**
  Fills up each lines it needs then returns the rest, or NULL if finished.
  You can sum up it action by imagining a butcher filling up sausages in a
  factory.
*/
uint8_t* vterm_writeline(vterm_ctx_t* vterm, uint8_t* str) {
  if (vterm->currentline->status == FULL) {
    vterm_scroll_down(vterm);
  }
  while ((vterm->currentline->offset < *(vterm->currentline->rows)) &&
         (*(str) != '\0') && (*(str) != '\n')) {
    vterm->currentline->linebuffer[vterm->currentline->offset] = *str;
    vterm->currentline->offset++;
    str++;
  }
  uint8_t m = 0;
  if (*(str) == '\n') {
    str++;
    vterm_scroll_down(vterm);
    if (vterm->ltrim == true) {
      while (m = strrchr("\r ", *str) != NULL) {
        str++;
      };
    }
    return str;
  }

  if (*(str) == '\0') {
    vterm->currentline->status =
        (vterm->currentline->offset == *(vterm->currentline->rows)) ? FULL
                                                                    : OFFSET;
    return NULL;
  } else {
    vterm->currentline->status = FULL;
    vterm->currentline->linebuffer[vterm->currentline->offset] = 0;
    return str;
  }
}

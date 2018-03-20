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

#ifndef VTERM_H
#define VTERM_H

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "string.h"

#define false 0
#define true 1

typedef enum vterm_status_t {
  OFFSET,
  EMPTY,
  FULL,
} vterm_status_t;

typedef struct vterm_line_t {
  uint8_t* linebuffer;
  uint8_t* rows;
  uint8_t offset;
  uint8_t id;
  vterm_status_t status;
} vterm_line_t;

typedef struct vterm_ctx_t {
  vterm_status_t status;
  vterm_line_t** buffer;
  vterm_line_t* currentline;
  uint8_t rows;
  uint8_t lines;
  uint8_t offset;
  uint8_t scroll;
  uint8_t ltrim;
} vterm_ctx_t;

typedef enum vterm_action_t {
  ERROR,
  SUCCESS,
} vterm_action_t;

vterm_ctx_t* vterm_init(uint8_t rows, uint8_t lines);
vterm_line_t* vterm_ctx_createLines(uint8_t* rows);
uint8_t** vterm_getscreen(vterm_ctx_t* vterm);
uint8_t* vterm_writeline(vterm_ctx_t* vterm, uint8_t* str);
vterm_action_t vterm_scroll_down(vterm_ctx_t* vterm);
vterm_action_t vterm_debug(vterm_ctx_t* vterm);
vterm_action_t vterm_write(vterm_ctx_t* vterm, uint8_t* str);
vterm_action_t vterm_goto(vterm_ctx_t* vterm, uint8_t x, uint8_t y);

#endif

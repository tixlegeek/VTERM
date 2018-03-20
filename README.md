```
╦  ╦╔╦╗┌─┐┬─┐┌┬┐  A tiny multipurpose virtual term screen, coded with love by
╚╗╔╝ ║ ├┤ ├┬┘│││  Tixlegeek < @tixlegeek - http://www.tixlegeek.io >
 ╚╝  ╩ └─┘┴└─┴ ┴  This code's purpose is to offer a nice, and smart terminal-like
V1.0              display feature. It takes care of everything, just stuff it up
                  with text, and pass it to the dumppiper.                   ```
# VTERM
This is vterm, a dumb-simple and smart tool to handle terminal-like display. It's aim is to provide a bullshit-free text-display management.
I can't find better things to say about it, it's a little thing i made for a project, not a ground-breakin startup shit. I don't do shit, it makes people look like salesmen.

# Example
Lets assume you decide to code an amazing stuff using my little thingy:

```
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
```
Then you open your haxor term and call a good make:
```
tixlegeek@devship:~$ make
rm -f main
# COMPILING ###########################################################
cc -o main main.c termscr.c utils.c
# RUN #################################################################
cp ./main /tmp/main
chmod +x /tmp/main
/tmp/main
|          |
|          |
|          |
|          |
|      Oh Y|
|eah       |
|          |
|          |
|          |
|          |
tixlegeek@devship:~$
```
BOOM! Laser robots.

# Side note
As i don't write code following any rules (what a punk, you'll say), i sometime
write uncomprehensible commentaries or readmes. Please use your imagination <3

# License                 
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

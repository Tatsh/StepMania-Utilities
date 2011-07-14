/**
 * Copyright 2011 Andrew Udvare
 *
 * This file is part of StepMania Utilities.
 *
 * StepMania Utilities is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * StepMania Utilities is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * StepMania Utilities. If not, see http://www.gnu.org/licenses/.
 */

#include "globals.h"
#include "print_message.h"

/**
 * Print a message to stderr. A '\n' will be appended.
 * @param char fmt,... Formatted string.
 * @return void
 */
void printErrorMessage(char *fmt, ...) {
  int len = strlen(fmt) + 1;
  char buffer[len];
  memset(buffer, 0, len);

  sprintf(buffer, "%s\n", fmt);
  va_list ap;
  va_start(ap, fmt);
  va_end(ap);
  vfprintf(stderr, buffer, ap);
}

/**
 * Print a message to stdout. A '\n' will be appended.
 * @param char fmt,... Formatted string.
 * @return void
 */
void printMessage(char *fmt, ...) {
  int len = strlen(fmt) + 1;
  char buffer[len];
  memset(buffer, 0, len);

  sprintf(buffer, "%s\n", fmt);
  va_list ap;
  va_start(ap, fmt);
  va_end(ap);
  vfprintf(stdout, buffer, ap);
}

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
#include "dwi.h"

/**
 * Entry point.
 * @param int argc Number of arguments passed from shell.
 * @param char argv Array of pointers to the arguments.
 * @return int Zero if successful, non-zero if something failed.
 */
int main(int argc, char *argv[]) {
  if (argc != 3) {
    printErrorMessage("Usage: %s FILE ADJUSTMENT", argv[0]);
    printErrorMessage("  where ADJUSTMENT is an integer.");
    exit(EXIT_FAILURE);
  }

  DWISong *song = DWIParseFilename(argv[1]);
  //printDWIInformation(song);

  FILE *fout;
  char *filename = malloc(strlen(argv[1]) + 10); // leave room to add -fixed.dwi
  memset(filename, 0, strlen(argv[1]) + 10);
  int i = 0;
  char *data;
  size_t ret;

  while (i < strlen(argv[1])) {
    if (argv[1][i] == '.') {
      if (argv[1][i+1] == '/') {
        strcat(filename, "./");
        i++;
        continue;
      }
      else {
        break;
      }
    }

    filename[i] = argv[1][i];
    i++;
  }
  strcat(filename, "-fixed.dwi");

  song->gap += atoi(argv[2]);

  if ((fout = fopen(filename, "w")) != NULL) {
    data = malloc(MAX_SECTION_LENGTH);
    memset(data, 0, MAX_SECTION_LENGTH);

    if (song->CDTitlePath != NULL) {
      sprintf(data, "#CDTITLE:%s;\n", song->CDTitlePath);
      ret = fwrite(data, strlen(data), 1, fout);
      assert(ret == 1);
    }

    memset(data, 0, MAX_SECTION_LENGTH);
    sprintf(data, "#TITLE:%s;\n", song->title);
    ret = fwrite(data, strlen(data), 1, fout);
    assert(ret == 1);

    memset(data, 0, MAX_SECTION_LENGTH);
    sprintf(data, "#BPM:%.2f;\n", song->initialBPM);
    ret = fwrite(data, strlen(data), 1, fout);
    assert(ret == 1);

    memset(data, 0, MAX_SECTION_LENGTH);
    sprintf(data, "#GAP:%d;\n", song->gap);
    ret = fwrite(data, strlen(data), 1, fout);
    assert(ret == 1);

    if (song->sampleStart != -1) {
      memset(data, 0, MAX_SECTION_LENGTH);
      sprintf(data, "#SAMPLESTART:%.2f;\n", song->sampleStart);
      ret = fwrite(data, strlen(data), 1, fout);
      assert(ret == 1);
    }

    if (song->sampleLength != -1 ) {
      memset(data, 0, MAX_SECTION_LENGTH);
      sprintf(data, "#SAMPLELENGTH:%.2f;\n", song->sampleLength);
      ret = fwrite(data, strlen(data), 1, fout);
      assert(ret == 1);
    }

    memset(data, 0, MAX_SECTION_LENGTH);
    for (i = 0; i < song->otherSectionsCount; i++) {
      if (song->otherSections[i] != NULL) {
        ret = fwrite(song->otherSections[i], strlen(song->otherSections[i]), 1, fout);
        assert(ret == 1);
      }
    }

    free(data);
    fclose(fout);
  }
  else {
    printErrorMessage("Failed to open output file.");
  }

  DWIFreeSong(song);
  free(filename);

  exit(EXIT_SUCCESS);
}

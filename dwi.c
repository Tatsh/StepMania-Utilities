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
#include "dwi.h"

/**
 * Parse a section of the file given a pointer to the file.
 * @param FILE fin Pointer to the already initialised file.
 * @return char Pointer to a new string. Must be freed. Returns NULL if insufficient memory is available.
 */
char *DWIParseSection(FILE *fin) {
  int c, i;
  char data[MAX_SECTION_LENGTH];

  c = getc(fin);

  for (i = 0; i < MAX_SECTION_LENGTH && !feof(fin) && c != ';'; i++) {
    data[i] = c;
    c = getc(fin);
  }

  if (feof(fin) || c != ';') {
    fprintf(stderr, "DWI file is non-compliant.\n");
    exit(EXIT_FAILURE);
  }

  data[i] = 0;

  return strdup(data);
}

/**
 * Free the DWISong structure.
 * @param DWISong song Pointer to an initialised structure.
 * @return void
 */
void DWIFreeSong(DWISong *song) {
  int i;
  for (i = 0; i < song->otherSectionsCount; i++) {
    if (song->otherSections[i] != NULL) {
      free(song->otherSections[i]);
    }
  }

  if (song->CDTitlePath != NULL) {
    free(song->CDTitlePath);
  }
  if (strcmp("########NOARTIST", song->artist) != 0) {
    free(song->artist);
  }
  if (strcmp("#######NOTITLE", song->title) != 0) {
    free(song->title);
  }

  free(song->otherSections);
  free(song);
}

/**
 * Initialise a default DWISong structure.
 * @return DWISong Pointer to a new DWISong strucutre. Must be freed by calling DWIFreeSong().
 */
DWISong *DWIInitialize() {
  DWISong *song = malloc(sizeof(DWISong));

  song->otherSections = malloc(sizeof(char *) * MAX_SECTIONS);
  song->otherSectionsCount = 0;
  song->sampleStart = -1;
  song->sampleLength = -1;
  song->gap = 0;
  song->artist = "########NOARTIST";
  song->title = "#######NOTITLE";
  song->CDTitlePath = NULL;
  song->initialBPM = 0.0f;

  return song;
}

/**
 * Based on Tapmania's parser.
 * Parse a DWI file given a file name.
 * @param char filename String with filename to read.
 * @return DWISong Pointer to a new DWISong structure. Must be freed by calling DWIFreeSong().
 */
DWISong *DWIParseFilename(const char *filename) {
  FILE *fin;
  int c; // Incoming char
  char varName[64]; // Variable after # to indicate section
  int i = 0, integer = 0, length = 0;
  double doble = 0;
  char *data;
  DWISong *song = DWIInitialize();

  if (!(fin = fopen(filename, "r"))) {
    fprintf(stderr, "Could not open file.\n");
    exit(EXIT_FAILURE);
  }

  while (!feof(fin)) {
    c = getc(fin);

    if (c == '#') {
      //printf("Opening new section.");
      varName[0] = '\0';

      c = getc(fin);
      i = 0;

      while (!feof(fin) && c != ':') {
        if (i >= 31) {
          fprintf(stderr, "DWI file is not compliant.\n");
          DWIFreeSong(song);
          exit(EXIT_FAILURE);
        }

        varName[i++] = c;
        c = getc(fin);
      }

      if (feof(fin)) {
        fprintf(stderr, "DWI file ended abruptly.\n");
        DWIFreeSong(song);
        exit(EXIT_FAILURE);
      }

      varName[i] = 0;

      if (!strcasecmp(varName, "TITLE")) {
        data = DWIParseSection(fin);
        song->title = data;
      }
      else if (!strcasecmp(varName, "CDTITLE")) {
        data = DWIParseSection(fin);
        song->CDTitlePath = data;
      }
      else if (!strcasecmp(varName, "ARTIST")) {
        data = DWIParseSection(fin);
        song->artist = data;
      }
      else if (!strcasecmp(varName, "BPM")) {
        data = DWIParseSection(fin);
        doble = atof(data);
        song->initialBPM = doble;
        free(data);
      }
      else if (!strcasecmp(varName, "GAP")) {
        data = DWIParseSection(fin);
        integer = atoi(data);
        song->gap = integer;
        free(data);
      }
      else if (!strcasecmp(varName, "SAMPLESTART")) {
        data = DWIParseSection(fin);
        doble = (double)atof(data);
        song->sampleStart = doble;
        free(data);
      }
      else if (!strcasecmp(varName, "SAMPLELENGTH")) {
        data = DWIParseSection(fin);
        doble = (double)atof(data);
        song->sampleLength = doble;
        free(data);
      }
      else {
        data = DWIParseSection(fin);
        length = strlen(varName) + 3; // add the \0 and two for # and :
        length += strlen(data);
        length += 2; // add two for ;\n

        song->otherSections[song->otherSectionsCount] = malloc(length);
        memset(song->otherSections[song->otherSectionsCount], 0, length);
        sprintf(song->otherSections[song->otherSectionsCount], "#%s:%s;\n", varName, data);
        song->otherSectionsCount++;

        free(data);
      }
    }
  }

  if (fin != NULL) {
    fclose(fin);
  }

  return song;
}

/**
 * Print basic DWI information.
 * @param DWISong song Pointer to initialised song structure.
 * @return void
 */
void DWIPrintSongInformation(DWISong *song) {
  printf("CD Title: %s\n", song->CDTitlePath == NULL ? "None" : song->CDTitlePath);
  printf("Title: %s\n", song->title);
  printf("Artist: %s\n", song->artist);
  printf("Initial BPM: %.2f\n", song->initialBPM);
  printf("Gap: %d\n", song->gap);
  printf("Sample start: %.2f\n", song->sampleStart);
  printf("Sample length: %.2f\n", song->sampleLength);
  printf("%d other sections\n", song->otherSectionsCount);
}

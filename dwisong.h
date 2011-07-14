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

#ifndef __DWISONG_H
#define __DWISONG_H

#define MAX_SECTION_LENGTH 40960
#define MAX_SECTIONS 100

typedef struct _DWISong {
  double sampleStart;
  double sampleLength;
  double initialBPM;
  int gap;
  char *artist;
  char *title;
  char *CDTitlePath;
  char **otherSections;
  int otherSectionsCount;
} DWISong;

#endif // __DWISONG_H

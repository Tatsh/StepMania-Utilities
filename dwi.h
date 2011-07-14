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

#ifndef __DWI_H
#define __DWI_H

#include "dwisong.h"

char *DWIParseSection(FILE *fin);
DWISong *DWIParseFilename(const char *filename);
void DWIPrintSongInformation(DWISong *song);
void DWIFreeSong(DWISong *song);
DWISong *DWIInitialize();

#endif // __DWI_H


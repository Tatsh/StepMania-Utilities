# Copyright 2011 Andrew Udvare
#
# This file is part of StepMania Utilities.
#
# StepMania Utilities is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by the
# Free Software Foundation, either version 3 of the License, or (at your
# option) any later version.
#
# StepMania Utilities is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
# more details.
#
# You should have received a copy of the GNU General Public License along with
# StepMania Utilities. If not, see http://www.gnu.org/licenses/.
#

CC     = gcc
CFLAGS = -Wall -std=c99
OBJS   = print_message.o dwi.o

all: dwi-adjust-gap dwi-adjust-bpm

dwi-adjust-bpm: $(OBJS) dwi-adjust-bpm.c
	$(CC) -o $@ dwi-adjust-bpm.c $(OBJS)

dwi-adjust-gap: $(OBJS) dwi-adjust-gap.c
	$(CC) -o $@ dwi-adjust-gap.c $(OBJS)

dwi-adjust-gap.o:

dwi.o: dwi.c
	$(CC) -c -o dwi.o $(CFLAGS) dwi.c

print_message.o: print_message.c
	$(CC) -c -o print_message.o $(CFLAGS) print_message.c

clean:
	rm -f *.o dwi-adjust-gap

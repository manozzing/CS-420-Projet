# (C) Makefile for program #1             ATMS 502/CSE 566, Spring 2022
#
# A "makefile" is a series of directions needed to build a program.
# It is used by the Linux command "make".
#
# A makefile typically defines:
#   1. The compiler (that which turns code, like pgm1.c, into an intermediate object file, like pgm1.o)
#   2. Compiler options - any special (not-standard) settings telling the compiler what to do
#   3. The object files (".o" versions of source files ending in ".f90" if fortran, or ".c" if C)
#      The compiler makes object files from your source code files, and once all of those are
#      up to date, it combines ("links") object files into a running program.
#
# Lines starting with "#" are comments - like this one!
# Type "man make" for more information on make, or look at these sites:
#
#	https://www.cs.usask.ca/staff/oster/makefiles.html
#	http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
#       http://www.cprogramming.com/tutorial/makefiles_continued.html
#
#  In this case: typing -
#  "make"          gets you an annoying "help" message.
#  "make advect"  actually does what you want: builds running program "advect"
#  "make clean"    deletes all the object (.o), graphics and program files 
#  "make listing"  creates a text listing of all your code, with line numbers
#  "make archive"  creates a zip (pgm1.zip) file with copies of all your files.
#
#  Note: you Only have to "make clean" if you have changed your OPTIONS.
#  In regular use, just type "make pgm1" to compile/build your program;
#    make will figure out which source code files you have changed,
#    compiling only *those* files, and then build your running program.

PROGRAM	= advect
OBJECTS = main.o	advection.o	bc.o	ic.o	stats.o	advect1d.o comms.o helpers.o
SOURCE  = main.c	advection.c	bc.c	ic.c	stats.c	advect1d.c comms.c helpers.c
CC	= mpicc
ARCHIVE_TAR = advect.tar
ARCHIVE_ZIP = advect.zip

OPTIONS	= 
# >>> For debugging, put "#" in front of OPTIONS above, remove "#" before OPTIONS below
#OPTIONS = -g -debug extended -traceback -O0
# >>> For extensive debugging, use these.
#OPTIONS = -g -debug extended -traceback -O0 -Wuninitialized -Wcheck -check=uninit -Wmissing-prototypes -ftrapuv -fp-stack-check
# ... Debugging info:
#     Info: https://www.nas.nasa.gov/hecc/support/kb/recommended-intel-compiler-debugging-options_92.html
#           http://hmf.enseeiht.fr/travaux/projnum/sites/default/files/users/eablonet/Debogage.pdf

help:
	@echo Try:
	@echo make $(PROGRAM) .... to build the program named $(PROGRAM)
	@echo make clean .... to clean up, removing object files and program $(PROGRAM)
	@echo make listing .... to make a printable listing ... you may need to adjust the page length
	@echo make archive .... to make an archive tar file you can transfer or submit

$(PROGRAM):	$(OBJECTS)
#	$(CC) $(OPTIONS) -fopenmp $(OBJECTS) -o $(PROGRAM) -lm
	$(CC) $(OPTIONS) $(OBJECTS) -o $(PROGRAM) -lm
#	$(CC) $(OPTIONS) -o $(PROGRAM) $(OBJECTS) -lm

%.o:	%.c
	$(CC) -c $(OPTIONS) $<

clean:	
	rm -f $(OBJECTS) $(PROGRAM) gmeta gmeta.zip *.gif

listing:
	@echo Creating code listing named listing.txt ...
	pr -F --length=59 --page-width=72 -n    \
           $(SOURCE) Makefile README.txt > listing.txt
	@echo listing.txt is `cat listing.txt | wc -l` lines long.

archive:
	@echo Creating code archive tar-file $(ARCHIVE_ZIP) ...
	tar cf $(ARCHIVE_ZIP) $(SOURCE) Makefile *.txt
	@ls -l $(ARCHIVE_ZIP)
#	tar cf $(ARCHIVE_TAR) $(SOURCE) Makefile *.txt
#	@ls -l $(ARCHIVE_TAR)

//include time library
#include <time.h>
#include <stdio.h>

//Initialize additional material. 

//initialize the log file and write the start time of the program
FILE *file;
time_t rawtime;
file = fopen("/home/student/log.txt", "a"); //here 'a' means we append and not write over the whole file
time(&rawtime);
fprintf(file, "%s", ctime(&rawtime)); //print time and date only one time

//Note that the first fprintf is only to set a date to indicate when the program start execution. 

//Do stuff

//Use fprintf to write info to the logfile.
fprintf(file, "This is a debug statement!\n");

//Do stuff

//close the file at the end of execution
fclose(file);
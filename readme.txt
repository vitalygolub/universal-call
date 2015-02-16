Just illustrates, how to make universal function call, using information, preserved in log file.
Is not checked with other compilers, but definitely is possible to get ride on 32 bit.

The idea: 
* "Record" preserves all data, for references (pointers) will be preserved content of memory chunk, defined manually
 (for example, for input char * strlen(src)+1, for output string – the parameter for max returned length)
* "Play" restores stack frame and calls universal function int universal(stackframe s) by original function address.  

Advantages
* Full environment for called function is preserved, including initial values of variables, passed by reference
* One dispatch procedure can call any function in player
Restrictions
* Function should have known calling conventions (currently cdecl, stack frame is always the same because caller cares about cleanup).
  Can be solved for other calling conventions, but assumed player knows calling conventions. 
* Int size hardcoded to 32 bit in some places, can be fixed
* Records, made on 64 bit platform can't be played on 32 bit platform and vice versa (can't be fixed)  

Files
* library, implements 3 prototypes from real fmnvb project with simple binary logging
* recorder, makes call to each of 3 functions to save log file (log.txt in working directory, overwrite )
* player, performs calls from log (log.txt in working directory)
 

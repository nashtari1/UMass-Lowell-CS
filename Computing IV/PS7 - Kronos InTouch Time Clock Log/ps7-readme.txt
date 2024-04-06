/**********************************************************************
 *  readme.txt template                                                   
 *  PS7 Kronos 
 **********************************************************************/

Name: Nika Ashtarzadeh


Hours to complete assignment: 10 hours


/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not? 
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/
 Yes, I completed the whole assignment successfully. I tested the program 
 with several input files and compared the output with the expected results. 
 The program correctly extracts the date and time of each boot, calculates the 
 boot time, and generates an output file with the appropriate header information.


/**********************************************************************
 *  Copy here all regex's you created for parsing the file, 
 *  and explain individually what each ones does.
 **********************************************************************/
 I used two regular expressions to parse the input log file:

 regex startup("([0-9]+)-([0-9]+)-([0-9]+) ([0-9]+):([0-9]+):([0-9]+): \\(log.c.166\\) server started.*"): 
 This regular expression matches lines in the log file that indicate the start of a device boot. 
 It extracts the year, month, day, hour, minute, and second values from the log file, which are 
 then used to calculate the date and time of the boot.

 regex success("([0-9]+)-([0-9]+)-([0-9]+) ([0-9]+):([0-9]+):([0-9]+).([0-9]+):
 INFO:oejs.AbstractConnector:Started SelectChannelConnector@0.0.0.0:9080.*"): 
 This regular expression matches lines in the log file that indicate the completion 
 of a device boot. It extracts the year, month, day, hour, minute, and second values 
 from the log file, which are then used to calculate the boot time.


/**********************************************************************
 *  Describe your overall approach for solving the problem.
 *  100-200 words.
 **********************************************************************/
 My overall approach for solving the problem was to use regular expressions to 
 extract the relevant information from the log file and store it in appropriate 
 data structures. I used the Boost C++ libraries to work with dates and times, 
 and I created variables to track the state of the program as it processed each 
 line of the input file. Specifically, I used a boolean variable to track whether 
 a boot was currently in progress or not, and I used two boost::posix_time::ptime 
 variables to store the start and end times of each boot. Finally, I used std::ofstream 
 to generate an output file with the appropriate header information and boot information.



/**********************************************************************
 *  Did you use lambda expression? If yes describe there.
 **********************************************************************/
 No, I did not use lambda expressions in this program.




/**********************************************************************
 *  List whatever help (if any) you received from TAs,
 *  classmates, or anyone else.
 **********************************************************************/



/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/



/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/



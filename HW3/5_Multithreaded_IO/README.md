README 

Brief : Created an userspace code to perform Multithreaded I/O operations.
        
Author : Bhallaji Venkatesan  

 Implementation : 
Steps Done :
1. Created userspace code that uses POSIX standard pthreads for multithreaded file I/O

2. Created  write, read and report threads to continuously read command line inputs from the user and
   writes into a file provided at command line, till a "#" is pressed in a newline. After which the program waits for
   a SIGUSR1, to read the file and create statistics and waits for a SIGUSR2 signal to print out the statistics.The 
   program also handles kill command through "SIGINT" and gracefully exits the threads (inlcuding children).

3. $make for creating executable

4. USAGE : $ ./multhreading <filename> 
         : To send SIGUSR1, kill comands are used in the following way
         : >create a new terminal
         : > pkill -<signalname> multhreading

5. The program handles improper signals or improper order of signals as well.


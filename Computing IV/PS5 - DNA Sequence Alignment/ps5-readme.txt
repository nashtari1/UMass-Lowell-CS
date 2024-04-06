/**********************************************************************
 *  readme 
 *  DNA Sequence Alignment
 **********************************************************************/

Name: Nika Ashtarzadeh

Hours to complete assignment: 10 Hours

/**********************************************************************
 * Explain which approach you decided to use when implementing
 * (either recursive with memoization, recursive without memorization,
 * dynamic programming or Hirschberg’s algorithm). Also describe why
 * you chose this approach and what its pros and cons are.
 **********************************************************************/
In my implementation, I used the 2D vector method to store the optimal edit distances between the two input strings.

I decided to use the dynamic programming approach when implementing the 
solution to calculate the edit distance between two genetic sequences. 
The choice of dynamic programming was made due to its efficiency and ability 
to handle larger inputs compared to the recursive methods

Pros of using dynamic programming:

Efficient: Dynamic programming is more efficient than recursive methods 
as it iteratively builds the solution bottom-up, avoiding redundant calculations.

Scalable: It can handle larger inputs without running into stack overflow 
issues or performance degradation, unlike recursive methods.
Easier debugging: Dynamic programming solutions are often easier to debug, 
as there is no need to deal with the call stack and recursion.

Cons of using dynamic programming:

Increased memory usage: Dynamic programming requires additional memory to store 
the intermediate results in a table (in this case, a 2D vector called 'opt').

I did not choose the Hirschberg's algorithm for this program because it is
more complex and harder to implement than dynamic programming

/**********************************************************************
 * Does your code work correctly with the endgaps7.txt test file? 
 * 
 * This example should require you to insert a gap at the beginning
 * of the Y string and the end of the X string.
 **********************************************************************/
Input:

X  Y
a  t
t  a
a  t
t  t
t  a
a  t
t  a

   
Expected output:

a - 2
t t 0
a a 0
t t 0
t t 0
a a 0
t t 0
- a 2

  
What happened:
 Here, the alignment inserts a gap at the beginning of the Y string (indicated by '-') 
 and at the end of the X string (also indicated by '-'). The resulting edit distance is 
 4, which is the expected output for this test file


/**********************************************************************
 * Look at your computer’s specs in the settings. 
 * How much RAM does your computer have and explain what this means? 
 **********************************************************************/

I have 3.6GHz Intel core i9 10900k CPU and 32 GB of RAM on my computer. 
The size of the DNA sequences being compared and the size of the dynamic 
programming table used to compute the edit distance can impact the amount of 
RAM used by the program. A computer with more RAM, such as 32 GB worth, may be able to handle larger 
DNA sequences and larger dynamic programming tables without running into memory issues

/**********************************************************************
 *  For this question assume M=N. Look at your code and determine
 *  approximately how much memory it uses in bytes, as a function of 
 *  N. Give an answer of the form a * N^b for some constants a 
 *  and b, where b is an integer. Note chars are 2 bytes long, and 
 *  ints are 4 bytes long.
 *
 *  Provide a brief explanation.
 *
 *  What is the largest N that your program can handle if it is
 *  limited to 8GB (billion bytes) of memory?
 **********************************************************************/
 The two input strings s1 and s2: Each string has N characters, and each 
 character occupies 2 bytes. Therefore, the memory usage for both strings is 
 2 * N * 2 bytes.
 The 2D vector 'opt': This vector has dimensions N+1 x N+1. Each element is 
 an integer, occupying 4 bytes. So, the memory usage for 'opt' is (N+1) * 
 (N+1) * 4 bytes.

 The total memory usage, as a function of N, is:

 Memory(N) = 4 * N + 4 * (N+1)^2

The largest N is:
8 * (10^9) bytes = 4 * N^2

Solving for N:

N^2 ≈ 2 * (10^9)

N ≈ sqrt(2 * (10^9))

N ≈ 44,721

/**********************************************************************
 * Run valgrind if you can and attach the output file to your submission. 
 * If you cannot run it, explain why, and list all errors you’re seeing. 
 * If you can run it successfully, does the memory usage nearly match that 
 * found in the question above? 
 * Explain why or why not. 
/**********************************************************************
 I ran valgrind on ecoli28284.txt which generated massif.out.9096. 
 The the total memory usage for ecoli28284.txt is 73,744 bytes (around 72.02 KB)
 from the memory report. 

 Based on the memory usage calculation from the previous question, we expected the memory usage to be:

 Memory usage = 4 * (N+1) * (N+1) + 4 * N
 Memory usage = 4 * (28284+1) * (28284+1) + 4 * 28284
 Memory usage ≈ 3,205,796,576 bytes (about 3,205 MB)

 Compiler optimizations might be reducing the memory usage of your program. Modern compilers can apply 
 various optimizations that might change the memory layout and usage of your program

 If the program uses other types of memory (such as stack memory or memory-mapped files), 
 the reported memory usage might be lower than the actual memory usage.

/**********************************************************************
 *  For each data file, fill in the edit distance computed by your
 *  program and the amount of time it takes to compute it.
 *
 *  If you get segmentation fault when allocating memory for the last
 *  two test cases (N=20000 and N=28284), note this, and skip filling
 *  out the last rows of the table.
 **********************************************************************/

data file           distance       time (seconds)     memory (MB)
------------------------------------------------------------------
ecoli2500.txt        118             0.146           23.84
ecoli5000.txt	     160             0.600           95.37
ecoli7000.txt        194             1.149           186.92
ecoli10000.txt       223             2.346           381.47
ecoli20000.txt       3135            9.628           1525.883
ecoli28284.txt       8394            19.373          3050.16

/*************************************************************************
 *  Here are sample outputs from a run on a different machine for 
 *  comparison.
 ************************************************************************/

data file           distance       time (seconds)
-------------------------------------------------
ecoli2500.txt          118             0.171
ecoli5000.txt          160             0.529
ecoli7000.txt          194             0.990
ecoli10000.txt         223             1.972
ecoli20000.txt         3135            7.730



/**********************************************************************
 *  For this question assume M=N (which is true for the sample files 
 *  above). By applying the doubling method to the data points that you
 *  obtained, estimate the running time of your program in seconds as a 
 *  polynomial function a * N^b of N, where b is an integer.
 *  (If your data seems not to work, describe what went wrong and use 
 *  the sample data instead.)
 *
 *  Provide a brief justification/explanation of how you applied the
 *  doubling method.
 * 
 *  What is the largest N your program can handle if it is limited to 1
 *  day of computation? Assume you have as much main memory as you need.
 **********************************************************************/
 We can compare the time taken for ecoli2500.txt and ecoli5000.txt, and 
 then ecoli5000.txt and ecoli10000.txt. We'll calculate the ratio of their execution times.

 Ratio1 = Time(N=5000) / Time(N=2500) = 0.600 / 0.146 ≈ 4.11
 Ratio2 = Time(N=10000) / Time(N=5000) = 2.346 / 0.600 ≈ 3.91

 To find the constant 'a' in the equation, we can use one of the data points, e.g., N=2500:

 a = Time(N=2500) / (2500^2) = 0.146 / (2500^2) ≈ 2.336e-8

 So, the estimated running time function is T(N) ≈ 2.336e-8 * N^2.
 To find the largest N your program can handle in 1 day of computation, 
 we'll set the running time to 1 day (86400 seconds) and solve for N:

 The largest N my program can handle limited to 1 day of computation is:

 86400 = 2.336e-8 * N^2
 N^2 = 86400 / 2.336e-8
 N ≈ sqrt(86400 / 2.336e-8) 
 ≈ 18115
 
**********************************************************************
 *  Did you use the lambda expression in your assignment? If yes, where 
 * (describe a method or provide a lines numbers)
 **********************************************************************/
 Yes I used a lambda expression in my program. It is used in the min() function 
 on line 18 to create a lambda function that returns the minimum value between two 
 integer inputs. The expression min_lambda(min_lambda(a, b), c) first computes 
 the minimum of a and b using min_lambda(a, b) and then computes the minimum of 
 the result and c using min_lambda(min_lambda(a, b), c). The final result is the 
 minimum of the three integers. 
 
 Here is the relevant code snippet:

int EDistance::min(int a, int b, int c) {
    auto min_lambda = [](int x, int y) { return x < y ? x : y; };
    return min_lambda(min_lambda(a, b), c);
}

**********************************************************************
 *  List whatever help (if any) you received from the course TAs,
 *  instructor, classmates, or anyone else.
 **********************************************************************/


/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/


/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/

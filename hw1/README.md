Part 1:

a) At a size of 2^8, I ran at 40,000 iterations. I tried to get getting mean coordinate update times that were similar to each other with multiple runs with the same parameters. At the same time, I aimed for the program to run in a reasonable amount of time, so that I could feasibly conduct multiple runs. As I doubled the size, I halved the number of iterations. This does two things: first, it keeps the number of coordinate updates, and thus the statistical significance of the mean, a constant. Second, it keeps the running time within a reasonable limit. The number of iterations M for each object count N are given below/:

N           M
256         40000
512         20000
1024        10000
2048        5000
4096        2500
8192        1250
16384       625
32768       312
65536       156
131072      78
262144      39
524288      19
1048576     9
2097152     4
4194304     2
8388608     1
16777216    1

b) I picked the median value so that I would get a value that actually appeared in the results (as opposed to the mean), but was still representative of the values obtained across all the runs (as opposed to the minimum or maximum). Picking the median over the mean also has the benefit of ignoring the effect of outliers on the data, in one sense. If the mean were used instead, the outliers would bring the mean up or down to a value that does not reflect the rest of the data. The median is unaffected if the values towards the ends of the range are swapped for outliers, and is thus immune to outliers in one sense. After showing my plot to Eitan, I came up with a revised plot for the C code, containing means instead of medians for N = 512, N = 2048, and N = 8192.

If dividing the number of iterations by 2 did not produce a whole number, I would round down; this could lead to some bias in the last 6-7 data points, pulling the values downward. For the last couple of data points, I simply conducted each benchmark once.

Part 2:

Due to increased performance, I was able to run more iterations for each object count. This makes the obtained mean value more statistically significant. I can also run the test for larger object counts, allowing us to see the performance of the code over a larger input range.

N       	M    
256			5000000 
512			2500000 
1024		1250000 
2048		625000 
4096		312500 
8192		156250 
16384		78125 
32768		39062 
65536		19531 
131072		9765 
262144		4882 
524288		2441 
1048576		1220 
2097152		610 
4194304		305 
8388608		152 
16777216	76 

Part 3:

When using float, the median co-ordinate update time for 2^16 objects is 0.008209 us.
When using double,the average co-ordinate update time for 2^16 objects is 0.009705 us, a considerable jump from the value for floats.
When using int8_t, the average time is 0.007769 us, somewhat faster than for floats, but not by a large margin.
When using int16_t, the average time is 0.007867 us, similar to that for int8_t and still somewhat faster than for float.
When using int32_t, the average time is 0.008272 us, slower than both float and the previously measured integer types, although still faster than double.
When using int64_t, the average time is 0.009241 us, slower then int32_t but still significantly faster than double.

Part 4:

The Python code, when running with 2^20 objects and 9 iterations, uses up to 211284 kB of RAM at any given moment (the maximum resident set size is 211284 kB). The C code, on the other hand, uses only up to 26176 kB at any given point. Thus the C code is vastly superior in terms of performance and memory consumption.

20 objects and 9 iterations, uses up to 211284 kB of RAM at any given moment (the maximum resident set size is 211284 kB). The C code, on 
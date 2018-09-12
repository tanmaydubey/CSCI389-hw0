#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

float* generate_random_list(int size, int bound) {
    
    float *numbers = malloc(sizeof(float) * size);
    // TODO: check for failed allocation here
    for (int i = 0; i < size; i++) {

        // found the below trick for generating random negative integers on StackOverflow.
        float number = (random() / ((float) RAND_MAX) * 2 * bound) - bound;
        numbers[i] = number;

    }
    
    return numbers;
}

void update_coords(float *x, float *y, float *z, float *vx, float *vy, float *vz, uint32_t size) {
    
    for (uint32_t i = 0; i < size; i++) {
        x[i] = x[i] + vx[i];
        y[i] = y[i] + vy[i];
        z[i] = z[i] + vz[i];
    }
}

float sum(float *x, uint32_t size) {
    
    float value = 0;
    
    for(uint32_t i = 0; i < size; i++) {
        value = value + x[i];
    }
    return value;

}

int main(int argc, char *argv[]) {
    
    if (argc != 3) {
        
        printf("Required arguments: vector_length(N) and iterations_num(M)");
        return -1;

    } else {
        
        uint32_t size = atoi(argv[1]);
        uint32_t iters = atoi(argv[2]);
        srandom(size);
        // float test = random() / ((float) RAND_MAX);
        // printf("%f\n", test);

        float *x = generate_random_list(size, 1000.0);
        float *y = generate_random_list(size, 1000.0);
        float *z = generate_random_list(size, 1000.0);
        float *vx = generate_random_list(size, 1.0);
        float *vy = generate_random_list(size, 1.0);
        float *vz = generate_random_list(size, 1.0);

        struct timespec start = {.tv_sec = 0, .tv_nsec = 0};
        struct timespec end = {.tv_sec = 0, .tv_nsec = 0};
        
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (uint32_t i = 0; i < iters; i++) {
            update_coords(x, y, z, vx, vy, vz, size);
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        // found out how to use clock_gettime here: https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/gettime.html

        /* start.tv_nsec is the nanosecond count, which is divided by 10**9
        to convert into seconds. It is then added to the second count to get
        a more precise time reading. Still, however, the readings are not as
        precise as they are for the Python code. */

        float start_time = start.tv_sec + (start.tv_nsec / 1000000000.0);
        // printf("Start time is %f\n", start_time);
        float end_time = end.tv_sec + (end.tv_nsec / 1000000000.0);
        // printf("End time is %f\n", end_time);
        float t = end_time - start_time;
        // printf("Process time is %f\n", t);

        float chksum = sum(x, size) + sum(y, size) + sum(z, size);
        printf("Mean time per coordinate: %lfus\n", (t * 1000000) / (size * iters));
        printf("Final checksum is: %f\n", chksum);

        return 0;

    }
}
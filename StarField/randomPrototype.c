#include <stdlib.h>
#include <stdio.h>

long randomIntUniform(long lowerBound, long upperBound)
{
    unsigned long
        intervals = (unsigned long) upperBound - lowerBound + 1,
        max = (unsigned long) RAND_MAX + 1,
        intervalSize = max / intervals,
        defect = max % intervals;
    
    long x;
    do {
        x = rand();
    }
    while (max - defect <= (unsigned long) x);

    return x / intervalSize + lowerBound;
} 

long randomIntEasy(long lowerBound, long upperBound)
{
    return (unsigned long) rand()%(upperBound-lowerBound+1)+lowerBound;
}
int main()
{
    srand(time(0));
    long values1[101];
    long values2[101];
    long result;
    for(int k = 0; k < 101; k++) 
    {
        values1[k] = 0;
        values2[k] = 0;
    }
    
    for(int j = 0; j < 1000000000; j++) 
    {
        result = randomIntUniform(10,110);
        values1[result-10]++;
        result = randomIntEasy(10, 110);
        values2[result-10]++;
    }
    printf("Uniform\t\tEasy\n");
    for(int i = 0; i < 101; i++)
    {
        printf("%d\t%d\n", values1[i], values2[i]);
    }
    return EXIT_SUCCESS;
}

/*
    So, since I can't see a marked difference between the two algorithms for
    random numbers I'll go with the easy one since it potentially makes less
    calls to rand()
*/
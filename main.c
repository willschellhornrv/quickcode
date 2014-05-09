#include <stdio.h>

static int counter; // will keep track of number of primes we read in from file
int isPrime(int test_val, int* prime_array);



int main()
{
	// read in list of primes from 0 to 1024 from file
	const char file_to_open[13] = "primes.txt";
	FILE* f_ptr = fopen(file_to_open, "r");


	// store them in an array
	int prime_holder[1000]; // array of length greater than range of numbers, could be a lot smaller
	counter = 0; // count number of primes

	// scan primes up to & including 1021
	// while counting them
	while (fscanf(f_ptr, "%d", &prime_holder[counter]) == 1)
	{	
		printf("number scanned is %d\n", prime_holder[counter]);
		counter++;
	}

	fclose(f_ptr);

	// generate verilog code for 1024 by 1 ROM
	// which will act as a flag array of whether a number 0:1023 is prime
	// write it to its own file

	const char file_to_write[16] = "verilog_rom.txt";
	FILE* file_out = fopen(file_to_write, "w");

	fprintf(file_out, "case 0 : out = 1'b0\n"); // 0 is not prime
	fprintf(file_out, "case 1 : out = 1'b0\n"); // 1 is not prime
		
	for (int i = 2; i < 1024; i++)
	{
		if (isPrime(i, prime_holder)) 
			fprintf(file_out, "case %d : out = 1'b1\n", i);
		else 
			fprintf(file_out, "case %d : out = 1'b0\n", i);
	
	}

}


// using prime_holder, detect whether number's prime
int isPrime(int test_val, int* prime_array)
{
	for (int i = 0; i <= counter; i++)
		if (prime_array[i] == test_val)
			return 1;
	return 0;

}

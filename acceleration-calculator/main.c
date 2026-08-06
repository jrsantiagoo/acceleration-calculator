#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

extern void calculate_acceleration(int num_cars, float* car_matrix, int* car_accelerations);

void clear_buffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

int run_interactive()
{
	// Y
	int num_cars, i, j;

	// Y x 3 matrix
	float car_matrix[10000][3];

	// Acceleration values stored as integers
	int car_accelerations[10000];


	printf("\n*========== Interactive Mode ==========*\n");
	printf("Number of Cars: ");
	while (scanf_s("%d", &num_cars) != 1)
	{
		clear_buffer();
		printf("Invalid input! Please try again.\n");
		printf("Number of Cars: ");
	}


	for (i = 0; i < num_cars; i++)
	{
		printf("*--------------- CAR %d ----------------*\n", i + 1);

		printf("Initial Velocity (KM/H): ");
		while (scanf_s("%f", &car_matrix[i][0]) != 1)
		{
			clear_buffer();
			printf("Invalid input! Please try again.\n");
			printf("Initial Velocity (KM/H): ");
		}

		printf("Final Velocity (KM/H): ");
		while (scanf_s("%f", &car_matrix[i][1]) != 1)
		{
			clear_buffer();
			printf("Invalid input! Please try again.\n");
			printf("Final Velocity (KM/H): ");
		}

		printf("Time (S): ");
		while (scanf_s("%f", &car_matrix[i][2]) != 1)
		{
			clear_buffer();
			printf("Invalid input! Please try again.\n");
			printf("Time (S): ");
		}
	}

	printf("\n*------------ ACCELERATION ------------*\n");
	calculate_acceleration(num_cars, car_matrix, car_accelerations);

	for (i = 0; i < num_cars; i++)
	{
		printf("Car %d: %d m/s^2\n", i + 1, car_accelerations[i]);
	}

	return 0;
}

void run_benchmark(int size, int trials)
{
	float* car_matrix = (float*)malloc(size * 3 * sizeof(float));
	int* car_accelerations = (int*)malloc(size * sizeof(int));

	if (car_matrix == NULL || car_accelerations == NULL)
	{
		printf("Memory allocation failed!\n");
		free(car_matrix);
		free(car_accelerations);
		return;
	}

	// Seed once, generate random but plausible test data
	for (int i = 0; i < size; i++)
	{
		float vi = (float)(rand() % 100);          // 0-99 km/h
		float vf = vi + (float)(rand() % 150 + 1);  // vi + 1..150 km/h
		float t = (float)(rand() % 15 + 1) + 0.1f; // 1.1 - 15.1 s
		car_matrix[i * 3 + 0] = vi;
		car_matrix[i * 3 + 1] = vf;
		car_matrix[i * 3 + 2] = t;
	}

	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);

	// Warm-up call (not timed) - avoids first-call cache/page-fault skew
	calculate_acceleration(size, (float*)car_matrix, car_accelerations);

	double total_ms = 0.0;
	for (int t = 0; t < trials; t++)
	{
		QueryPerformanceCounter(&start);
		calculate_acceleration(size, car_matrix, car_accelerations);
		QueryPerformanceCounter(&end);

		total_ms += (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
	}

	double avg_ms = total_ms / trials;
	printf("Y = %-6d | Trials = %d | Avg time = %.6f ms\n", size, trials, avg_ms);

	free(car_matrix);
	free(car_accelerations);
}

int run_benchmark_suite() 
{
	srand((unsigned int)time(NULL));

	int size;
	do {
		printf("\n*======= ASM Function Benchmark =======*\n");
		printf("Input size (Max: 10000, Exit: -1): ");
		scanf_s("%d", &size);
		if (size != -1)
			run_benchmark(size, 30);
	} while (size != -1);

	return 0;
}

int main()
{
	int choice;

	printf("*======= Car Acceleration Calculator =======*\n");
	printf("Select Mode:\n");
	printf("[1] Interactive\n[2] Benchmark\nChoice: ");
	scanf_s("%d", &choice);

	if (choice == 1)
		run_interactive();
	else if (choice == 2)
		run_benchmark_suite();

	return 0;
}
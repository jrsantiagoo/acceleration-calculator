#include <stdio.h>

extern void calculate_acceleration(int num_cars, float* car_matrix, int* car_accelerations);

void clear_buffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
	// Y
	int num_cars, i, j;

	// Y x 3 matrix
	float car_matrix[10000][3]; 

	// Acceleration values stored as integers
	int car_accelerations[10000]; 
	

	printf("Number of Cars: ");
	while (scanf_s("%d", &num_cars) != 1)
	{
		clear_buffer();
		printf("Invalid input! Please try again.\n");
		printf("Number of Cars: ");
	}
	

	for(i = 0; i < num_cars; i++)
	{
		printf("*---------- CAR %d ----------*\n", i + 1);
		
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

	printf("\n*-------- CAR MATRIX --------*\n");
	for(i = 0; i < num_cars; i++)
	{
		for(j = 0; j < 3; j++)
		{
			printf("%f ", car_matrix[i][j]);
		}
		printf("\n");
	}

	printf("\n*------- ACCELERATION -------*\n");
	calculate_acceleration(num_cars, car_matrix, car_accelerations);

	for (i = 0; i < num_cars; i++)
	{
		printf("Car %d: %d m/s^2\n", i+1, car_accelerations[i]);
	}
	
	return 0;
}
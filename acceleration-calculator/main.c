#include <stdio.h>

void clear_buffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
	float car_matrix[10000][3]; // Y x 3 matrix
	int num_cars; // Y
	int i, j;

	printf("Number of Cars: ");
	while (scanf_s("%d", &num_cars) != 1)
	{
		clear_buffer();
		printf("Invalid input! Please try again.\n");
		printf("Number of Cars: ");
	}
	

	for(i = 0; i < num_cars; i++)
	{
		printf("*------- CAR %d -------*\n", i + 1);
		
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

	printf("\n*------- CAR MATRIX -------*\n");
	for(i = 0; i < num_cars; i++)
	{
		for(j = 0; j < 3; j++)
		{
			printf("%f ", car_matrix[i][j]);
		}
		printf("\n");
	}

	return 0;
}
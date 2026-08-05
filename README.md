# Car Acceleration Calculator (C + x86-64 Assembly)

An x86-to-C interface programming project that calculates the acceleration of multiple cars given its Initial Velocity (Vi), Final Veolocity (Vf), and Time (T). Input collection and output printing are handled
in C; the actual unit conversion, acceleration calculation, and float-to-integer conversion are performed in a hand-written x86-64 assembly function using scalar SIMD floating-point instructions (`movss`, `subss`, `divss`, `cvtss2si`).

## Formula

```
Acceleration (m/s^2) = (Vf - Vi) / T
```

Where:

- **Vi** - Initial Velocity (KM/H)
- **Vf** - Final Velocity (KM/H)
- **T** - Time (seconds)

Velocities are converted from KM/H to M/S (divided by 3.6) inside the assembly
function before the acceleration is computed. The final result is rounded to the
nearest integer.

## Project Structure

| File                          | Description                                                                                                                                        |
| ----------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------- |
| `main.c`                      | C driver program. Handles user input, memory allocation, calls into the assembly function, and prints results.                                     |
| `acceleration_calculator.asm` | x86-64 NASM assembly function that performs the KM/H to M/S conversion, computes acceleration for each car, and converts the result to an integer. |

## Functionality

The program has two modes, selectable from a menu on launch:

**1. Interactive Mode**

- Prompts for the number of cars (Y) and, for each car, its Initial Velocity, Final Velocity, and Time.
- Validates all numeric input (re-prompts on invalid entries).
- Displays the collected Y × 3 input matrix.
- Calls the assembly function to compute acceleration for every car.
- Prints the resulting acceleration (in m/s²) for each car.

**2. Benchmark Mode**

- Prompts for an input size (Y), up to 10,000 cars.
- Randomly generates plausible test data (Vi, Vf, T) for Y cars.
- Runs one untimed warm-up call, then times 30 calls to the assembly function using `QueryPerformanceCounter` (high-resolution Windows timer).
- Reports the average execution time (in milliseconds) across the 30 runs.

## How to Run

### Requirements

- Windows
- Visual Studio (with the NASM build customization / NASM installed and configured for this project)

### Build

1. Open the project/solution in Visual Studio.
2. Build the solution (`Ctrl+Shift+B`), selecting the desired configuration (Debug/Release, x64).
3. Run the produced executable (`Ctrl+F5` or `F5`).

### Usage

On launch, choose a mode:

```
*======= Car Acceleration Calculator =======*
Select Mode:
[1] Interactive
[2] Benchmark
Choice:
```

**Interactive Mode**: enter `1`, then follow the prompts to enter the number of cars and each car's Vi, Vf, and T values. Example:

```
Number of Cars: 3
Initial Velocity (KM/H): 0.0
Final Velocity (KM/H): 62.5
Time (S): 10.1
...
```

**Benchmark Mode**: enter `2`, then enter the number of cars to generate and time (e.g., `10`, `100`, `1000`, `10000`). The program will output the average execution time over 30 runs.

## Performance Results

_(To be filled in — execution time table and short analysis for Y = 10, 100, 1000, 10000)_

## Correctness Check

_(To be filled in — screenshot of program output demonstrating correct results)_

## Demo Video

_(To be filled in — link to a 5–10 minute video showing source code, compilation, and execution of both the C and x86-64 program)_

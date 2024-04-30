# Philosophers

This project is part of the 42 school curriculum which involves solving the classic synchronization problem known as the "Dining Philosophers" problem with a focus on using threads and mutexes (for the mandatory part) and processes and semaphores (for the bonus part). The simulation involves philosophers sitting at a round table with forks between them, where they alternatively eat, think, or sleep.

## Warning for 42 Students

This repository is intended as a reference and educational tool. **42 students are strongly advised not to copy this code without fully understanding its functionality.** Plagiarism in any form is against 42's principles and could lead to serious academic consequences. Use this repository responsibly to learn and better understand how to implement similar functionalities on your own.

## Project Overview

Philosophers are arranged around a table with one fork between each pair. To eat, a philosopher needs to pick up the two forks adjacent to them. After eating, philosophers will sleep and then think, repeating the cycle until one of them dies of starvation. The challenge is to implement a solution that prevents any philosopher from dying.

### Features

- Philosophers alternate between eating, sleeping, and thinking.
- Deadlock and starvation are prevented using synchronization mechanisms.
- The state of each philosopher is logged with precise timestamps.

## Requirements

This program should take the following arguments:
```
number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
- **number_of_philosophers**: Number of philosophers and forks.
- **time_to_die** (in milliseconds): Maximum time a philosopher can spend without eating before dying.
- **time_to_eat** (in milliseconds): Time a philosopher spends eating.
- **time_to_sleep** (in milliseconds): Time a philosopher spends sleeping.
- **number_of_times_each_philosopher_must_eat** (optional): If specified, the simulation will stop once all philosophers have eaten this many times.

## Compilation

To compile the philosophers program, clone the repository and run make:
```
git clone https://github.com/zolfagharipour/philosophers.git
cd philosophers
make
```

## Usage

To start the simulation, run the program with the required arguments:
```
./philosophers 5 800 200 200
```
This will start a simulation with 5 philosophers where:
- A philosopher dies if they haven't started eating 800ms after their last meal.
- Each philosopher takes 200ms to eat.
- Each philosopher sleeps for 200ms.

## Logs

The program logs each action of the philosophers with the following format:
```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```
Where **timestamp_in_ms** is the current timestamp in milliseconds and **X** is the philosopher number.

## Bonus Part

For the bonus part, philosophers are implemented using processes and the available forks are managed using semaphores. This variation introduces different synchronization challenges and solutions.

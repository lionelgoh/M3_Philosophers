*This project has been created as part of the 42 curriculum by liogoh.*

# Philosophers

## Description

`Philosophers` is a concurrency project from the 42 curriculum based on the classic Dining Philosophers problem.

The goal of the project is to simulate a group of philosophers sitting around a table. Each philosopher alternates between eating, sleeping, and thinking. To eat, a philosopher must take two forks: one on their left and one on their right. Since forks are shared between neighbouring philosophers, access to each fork must be synchronized.

This project introduces the basics of multithreaded programming in C, including thread creation, mutexes, race conditions, deadlocks, starvation, and time-based simulation.

The mandatory version uses:

- one thread per philosopher
- one mutex per fork
- mutex-protected shared state
- a monitor thread to detect death and completion conditions

## Instructions

### Compilation

From the `philo/` directory, run:

```bash
make
```

This creates the executable:

```bash
./philo
```

### Cleaning

Remove object files:

```bash
make clean
```

Remove object files and executable:

```bash
make fclean
```

Rebuild from scratch:

```bash
make re
```

### Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:

```bash
./philo 5 800 200 200
```

## Program Arguments

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers and forks |
| `time_to_die` | Time in milliseconds before a philosopher dies if they do not start eating |
| `time_to_eat` | Time in milliseconds spent eating |
| `time_to_sleep` | Time in milliseconds spent sleeping |
| `number_of_times_each_philosopher_must_eat` | Optional. If provided, the simulation stops once every philosopher has eaten at least this many times |

## Output Format

Each state change is printed in the following format:

```txt
timestamp_in_ms philosopher_id state
```

Possible states:

```txt
has taken a fork
is eating
is sleeping
is thinking
died
```

Example output:

```txt
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
```

## Technical Overview

### Threads

Each philosopher is represented by one thread. All philosopher threads run concurrently and execute the same routine:

```txt
take forks
eat
release forks
sleep
think
repeat
```

### Mutexes

Mutexes are used to protect shared resources and prevent data races.

| Resource | Protection |
|---|---|
| Forks | One mutex per fork |
| Printing | A print mutex prevents overlapping messages |
| Stop flag | A stop mutex protects the shared simulation stop state |
| Meal data | Each philosopher has a meal mutex protecting `last_meal_time` and `meals_eaten` |

### Monitor Thread

A separate monitor thread checks whether:

- any philosopher has died
- all philosophers have eaten enough times, if the optional argument is provided

If a philosopher dies, the monitor prints the death message and stops the simulation.

## Examples

### Basic simulation

```bash
./philo 5 800 200 200
```

Expected behavior: philosophers should continue eating, sleeping, and thinking without dying under normal conditions.

### Simulation with meal limit

```bash
./philo 5 800 200 200 7
```

Expected behavior: the simulation stops once every philosopher has eaten at least 7 times.

### One philosopher

```bash
./philo 1 800 200 200
```

Expected behavior: the philosopher takes one fork and eventually dies, because one philosopher can never obtain two forks.

### Impossible timing

```bash
./philo 4 200 210 100
```

Expected behavior: a philosopher should die because `time_to_eat` is longer than `time_to_die`.

## Edge Cases Tested

```bash
./philo 1 800 200 200
./philo 2 800 200 200
./philo 4 410 200 100
./philo 4 310 200 100
./philo 5 800 200 200
./philo 5 800 200 200 7
./philo 4 200 210 100
```

Invalid input tests:

```bash
./philo
./philo 0 800 200 200
./philo 5 -800 200 200
./philo 5 800 abc 200
./philo 5 800 200 200 0
```

## Key Concepts Learned

This project helped reinforce the following concepts:

- threads and concurrent execution
- shared memory between threads
- mutex locking and unlocking
- race conditions
- deadlock prevention
- starvation
- timing with `gettimeofday`
- responsive sleeping with `usleep`
- safe cleanup of dynamically allocated memory and mutexes

## Resources

- `man pthread_create`
- `man pthread_join`
- `man pthread_mutex_init`
- `man pthread_mutex_lock`
- `man pthread_mutex_unlock`
- `man pthread_mutex_destroy`
- `man gettimeofday`
- `man usleep`
- [Dining Philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

## Use of AI

AI assistance was used as a learning aid during this project.

Specifically, AI was used to:

- break down the subject requirements
- explain concurrency concepts such as threads, mutexes, race conditions, deadlocks, and starvation
- discuss possible struct design
- reason about monitor logic and death detection
- review edge cases and testing strategy
- help draft this README

All code was reviewed, tested, and understood before being included in the project.
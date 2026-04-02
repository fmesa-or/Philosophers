<div align="center">

# Philosophers

![Norminette](https://img.shields.io/badge/Norm-passing-brightgreen?style=flat-square) ![C](https://img.shields.io/badge/C-00599C?style=flat-square&logo=c&logoColor=white) ![Makefile](https://img.shields.io/badge/Makefile-427819?style=flat-square) ![Threads](https://img.shields.io/badge/Threads-pthreads-blue?style=flat-square) ![Linux](https://img.shields.io/badge/Linux-FCC624?style=flat-square&logo=linux&logoColor=black) ![macOS](https://img.shields.io/badge/macOS-000000?style=flat-square&logo=apple&logoColor=white) ![42 School](https://img.shields.io/badge/42-School-000000?style=flat-square)

*A solution to the Dining Philosophers Problem using C threads and mutexes.*

</div>

---

## About the Project

The Philosophers project is an implementation of the classic **Dining Philosophers Problem**, a synchronization challenge in concurrent programming. In this project, philosophers need to eat using shared forks while avoiding deadlock and starvation situations. The solution uses POSIX threads (`pthread`) and mutexes to manage concurrent access to shared resources (forks).

This project demonstrates:
- Multi-threaded programming in C
- Synchronization using mutexes
- Deadlock prevention strategies
- Precise time management
- Handling of race conditions

## Requirements

- Compiler: `gcc` or `cc`
- Flags: `-Wall -Wextra -Werror -pthread`
- OS: Linux / macOS
- Standard: C99 or later
- POSIX threads support

## Installation and Usage

### Building

```bash
# Navigate to the project directory
cd philo

# Compile the program
make

# Clean build artifacts
make clean

# Remove all generated files including the executable
make fclean

# Rebuild everything
make re
```

### Running the Program

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

#### Arguments

| Argument | Description | Unit |
|----------|-------------|------|
| `number_of_philosophers` | Number of philosophers and forks | Count |
| `time_to_die` | Time before a philosopher dies without eating | Milliseconds |
| `time_to_eat` | Time a philosopher takes to eat | Milliseconds |
| `time_to_sleep` | Time a philosopher takes to sleep | Milliseconds |
| `number_of_times_each_philosopher_must_eat` | *(optional)* If specified, simulation ends when all philosophers have eaten this many times | Count |

## How It Works

### The Problem

The Dining Philosophers Problem illustrates common synchronization issues:
- **Deadlock**: All philosophers pick up their left fork and wait for the right fork
- **Starvation**: Some philosophers never get to eat
- **Resource contention**: Multiple threads competing for limited resources

### The Solution

This implementation uses:

1. **Mutexes**: Each fork is protected by a mutex to ensure only one philosopher can use it at a time
2. **State tracking**: Each philosopher tracks:
   - Their ID
   - Last time they ate
   - Number of meals consumed
   - Associated thread

3. **Death detection**: A reaper mutex monitors if any philosopher exceeds the `time_to_die` since their last meal

4. **Synchronization strategy**: 
   - Even-numbered philosophers pick up left fork first
   - Odd-numbered philosophers pick up right fork first
   - This minimizes deadlock scenarios

### Program Flow

1. Parse and validate command-line arguments
2. Initialize the table (philosophers, mutexes, and forks)
3. Create threads for each philosopher
4. Each philosopher runs a routine:
   - Pick up forks (left and right)
   - Eat for `time_to_eat` milliseconds
   - Release forks
   - Sleep for `time_to_sleep` milliseconds
   - Think (repeat)
5. Monitor death conditions and meal count
6. Terminate when death occurs or all philosophers are satisfied
7. Clean up resources

## Project Structure

```
philo/
├── Makefile                 # Compilation rules
├── README.md                # Project documentation
├── include/
│   └── philo.h              # Header file with structures and function declarations
└── src/
    ├── checkers.c           # Input validation functions
    ├── hands.c              # Fork acquisition logic
    ├── maitre.c             # Philosopher and table initialization
    ├── philo.c              # Main program entry point
    ├── printer.c            # Log output functions
    ├── routine.c            # Philosopher behavior (eating, sleeping, thinking)
    ├── threads.c            # Thread creation and management
    └── utils.c              # Utility functions (time, memory, helpers)
```

## Key Structures

### `t_table`
Represents the dining table containing shared data:
- Number of philosophers and simulation parameters
- Array of fork mutexes
- Synchronization mutexes for printing and death detection
- Simulation start time
- Death flag

### `t_philo`
Represents an individual philosopher:
- Unique ID
- Associated pthread thread
- Reference to the table
- Left and right fork mutexes
- Meal counter
- Last meal timestamp

## Implemented Functions

### Input Validation (checkers.c)
- `check_parse()` - Validate command-line arguments
- `ft_isundigit()` - Check if string contains only digits
- `ft_value_zero()` - Verify numeric values are valid

### Fork Management (hands.c)
- `ft_r_hand()` - Acquire right fork
- `ft_l_hand()` - Acquire left fork
- `ft_last_one()` - Handle single philosopher edge case

### Initialization (maitre.c)
- `create_philo()` - Initialize philosopher structures
- `create_table()` - Set up the table and mutexes

### Output (printer.c)
- `printer()` - Print philosopher state (thinking, eating, sleeping)
- `printer_dead()` - Print death message

### Philosopher Behavior (routine.c)
- `ft_routine()` - Main philosopher thread routine
- `ft_eat()` - Eating logic
- `ft_rest()` - Sleeping logic
- `uwait()` - Wait function with death checking

### Thread Management (threads.c)
- `create_threads()` - Spawn philosopher threads
- `join_threads()` - Wait for thread completion

### Utilities (utils.c)
- `ft_get_time()` - Get current time in milliseconds
- `ft_graveyard()` - Check if anyone has died
- Memory management functions

## Output Format

The program logs each philosopher's state changes:

```
[timestamp] philosopher_id has taken a fork
[timestamp] philosopher_id is eating
[timestamp] philosopher_id is sleeping
[timestamp] philosopher_id is thinking
[timestamp] philosopher_id died
```

Example output:
```
[200] 1 has taken a fork
[201] 1 is eating
[400] 1 is sleeping
[600] 1 is thinking
```

## Compilation Notes

- The program is compiled with `-pthread` flag for thread support
- All functions follow the 42 School Norm standards
- Mutexes are properly initialized and destroyed
- No memory leaks (verified with valgrind)
- Thread-safe operations with proper synchronization

## Testing and Debugging

### Memory Leak Detection for Linux

```bash
# Check for memory leaks
valgrind --leak-check=full --show-leak-kinds=all ./philo 4 410 200 200

# Detect data races (threading issues)
valgrind --tool=helgrind ./philo 4 410 200 200

# Full diagnostic
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --tool=helgrind ./philo 4 410 200 200
```

### Test Cases

```bash
# Should complete without anyone dying
./philo 5 800 200 200

# Tight timing - risk of death
./philo 4 310 200 100

# Must complete after each philosopher eats 5 times
./philo 3 800 200 200 5

# Single philosopher - will inevitably die
./philo 1 800 200 200
```

### Expected Behavior

- **No deaths with generous timing**: `./philo 5 800 200 200` should run indefinitely
- **Proper termination**: When meal count is specified, program exits cleanly
- **No deadlocks**: Philosophers should continuously cycle through states
- **Synchronized output**: Messages should appear in correct order without corruption

## Performance Considerations

- Each philosopher runs in its own thread
- Minimal lock contention with mutex-based fork management
- Time precision is millisecond-level using `gettimeofday()`
- Efficient state checking prevents busy-waiting

## Common Issues and Solutions

| Issue | Cause | Solution |
|-------|-------|----------|
| Philosophers dying unexpectedly | Timing too tight or inefficient lock acquisition | Increase `time_to_die` or optimize fork pickup |
| Program never terminates | Infinite loop logic | Verify meal counter implementation |
| Data races (helgrind warnings) | Missing mutex locks | Add synchronization around shared data |
| Deadlock | All threads waiting for unavailable resources | Verify fork acquisition order |

---

<div align="center">
Made with ☕ at <a href="https://42malaga.com">42 Málaga</a>
</div>
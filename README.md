# Philosophers

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#about-the-project">About The Project</a></li>
    <li><a href="#rules">Rules</a></li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>

## About the Project
This project is about concurrent programming. For the project's mandatory part, I must solve the problem only using threads and mutexes. For the bonus part, I must only use processes and semaphores.

## Rules

The problem as follows:

* One or more philosophers sit at a round table.
* There is a large bowl of spaghetti in the middle of the table.
* The spaghetti can only be eaten with two forks.
* There are only as many forks as there are philosophers.
* Each philosopher eats, sleeps and thinks.
* If a philosopher hasn't eaten in a certain timeframe, they will die of starvation.
* Philosophers cannot communicate with each other.

I must create a program that keeps the philosophers alive as far as possible. 

The programs must take several parameters:

* **```number_of_philosophers```**: the number of philosophers around the table,
* **```time_to_die```**: a number representing the time in milliseconds a philosopher has to live after a meal. If a philosopher hasn’t started eating time_to_die milliseconds after the beginning of their last meal or the beginning of the simulation, they will die.
* **```time_to_eat```**: a number representing the time in milliseconds a philosopher takes to finish their meal. During that time, the philosopher keeps their two forks in hand.
* **```time_to_sleep```**: the time in milliseconds that a philosopher spends to sleep.
* **```number_of_times_each_philosopher_must_eat```**: an optional argument that allows the program to stop if all the philosophers have eaten at least that many times. If this argument is not specified, the simulation carries on unless a philosopher dies.

The programs outputs messages like below:

```
[timestamp_in_ms] [X] has taken a fork
[timestamp_in_ms] [X] is eating
[timestamp_in_ms] [X] is sleeping
[timestamp_in_ms] [X] is thinking
[timestamp_in_ms] [X] died
```

## Usage

Git clone the project and for the mandatory part:
```shell
cd philosophers/philo
or
cd philosophers/philo_bonus
```
To compile,

```shell
make
```

Run the program with the following arguments:

```shell
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philo_must_eat]
./philo 4 800 200 200 5
or
./philo_bonus 4 800 200 200 5
```

If the arguments are valid, the program will output the actions of each philosopher until one of them dies or until all of them have eaten number_of_times_each_philo_must_eat, if specified.

## Contact

- Luke Lai - [LinkedIn](https://www.linkedin.com/in/luke-lai-309a3522b/) - lukelai.dev@gmail.com

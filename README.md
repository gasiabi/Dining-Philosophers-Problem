# Dining Philosophers Problem

## Project Description

This project implements a solution to the dining philosophers problem in C using threads and semaphores. The program illustrates managing shared resources (forks) and thread synchronization.

## Features

1. Simulation of five philosophers meditating, eating, and waiting for forks.
2. Thread synchronization using:
   - **Semaphores (`sem_t`)** for forks.
   - **Mutex (`pthread_mutex_t`)** for input/output operations (to prevent overlapping thread outputs).
3. Execution of 7 eating cycles for each philosopher.

## Code Structure

- **Philosopher states**:
  - `m`: meditating
  - `C`: waiting
  - `L`: picks up the left fork
  - `P`: picks up the right fork
  - `J`: eating
  - `1`: puts down the left fork
  - `2`: puts down the right fork
  - `K`: finishes eating
- Synchronization of fork operations using semaphores.

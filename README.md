# Change-Machine — Change-Making with Optimization Algorithms

## Overview

**Change-Machine** is a console application written in **C** that solves the **change-making problem**. Given a set of coins and an amount to return, find the combination of coins that best satisfies the defined objective, for example, reaching the exact amount using the fewest coins.

The problem is treated as a **optimization problem** and solved with two different search methods, which can be compared against each other:

- **Hill Climbing** — a local search that iteratively improves a single solution
- **Evolutionary Algorithm with Tournament Selection** — a population of solutions that evolves over multiple generations

## Features

- **Hill Climbing** algorithm (local search)
- **Evolutionary algorithm** running over **multiple generations**
- Parent selection through **binary tournament** (size 2)
- **General tournament** selection with configurable tournament size (`tsize`)
- Several genetic operators:
  - **Two-point crossover**
  - **Uniform crossover**
  - **Binary mutation** with multiple mutation points
  - **Swap mutation** (active by default)
- Configurable parameters: population size, mutation probability, crossover probability, tournament size and number of generations
- Included test files (`file1.txt` to `file5.txt`)

## Evaluation Methods

The project implements two search methods that start from the same problem and the same fitness function, treated as a **minimization problem** (the lower the value, the better the solution).

| Method | Type | Description |
|--------|------|-------------|
| Hill Climbing | Local search | Starts from an initial solution, generates a neighbouring solution and accepts it if it is better, repeating for a fixed number of iterations |
| Tournament (evolutionary algorithm) | Population-based search | Maintains a population of solutions; each generation selects parents by tournament, applies genetic operators and builds the next population |

### Hill Climbing

1. Generate an initial solution.
2. Evaluate the solution (fitness).
3. Generate a neighbouring solution through a small change.
4. If the neighbour is better, replace the current solution.
5. Repeat until the maximum number of iterations is reached.

### Tournament and Generations

1. An initial population of `popsize` solutions is generated.
2. Each solution is evaluated.
3. **Selection:** `popsize` tournaments are held; in each one, the best solution (lowest fitness) is chosen as a parent.
4. **Genetic operators:** crossover (two-point or uniform) and mutation (binary or swap) produce the offspring.
5. The offspring are evaluated and form the next generation.
6. The process repeats for the configured number of generations, keeping track of the best solution found.

## Genetic Operators

| Operator | Function | Description |
|----------|----------|-------------|
| Binary tournament | `tournament` | Randomly picks two solutions and selects the better one |
| General tournament | `tournament_geral` | Picks `tsize` distinct solutions and selects the best one |
| Two-point crossover | `recombinacao_dois_pontos_corte` | Swaps genes between two random cut points |
| Uniform crossover | `recombinacao_uniforme` | Each gene is inherited from one of the parents with equal probability |
| Binary mutation | `mutation` | Replaces each gene, with probability `pm`, by a value between 0 and 9 |
| Swap mutation | `mutacao_por_troca` | Swaps two genes' positions with probability `pm` |

> **Note:** crossover only works with an **even** population size, and swap mutation requires `num_moedas > 1`.

## Main Parameters

| Parameter | Description |
|-----------|-------------|
| `popsize` | Population size |
| `num_moedas` | Number of coin types / solution length |
| `tsize` | Tournament size |
| `pm` | Mutation probability |
| `pr` | Crossover probability |
| Number of generations | Stopping criterion for the evolutionary algorithm |
| Number of iterations | Stopping criterion for Hill Climbing |

## Test Files

The files `file1.txt` to `file5.txt` contain problem instances with different configurations, allowing the performance of **Hill Climbing** and the **tournament-based algorithm** to be compared across several scenarios.

## Method Comparison

| Criterion | Hill Climbing | Tournament (multiple generations) |
|-----------|---------------|-----------------------------------|
| Search type | Local | Population-based |
| Search space exploration | Low | High |
| Risk of getting stuck in local optima | High | Low |
| Computational cost | Low | Higher |
| Solutions handled simultaneously | 1 | `popsize` |

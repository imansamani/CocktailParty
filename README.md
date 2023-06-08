# Cocktail Party Simulation

This project is a simulation of a cocktail party at an academic conference. It aims to create a program that simulates the interactions between individuals in a room based on their interests.

## Problem Statement

The simulation is designed to address the following problem:

We want to simulate a cocktail party at an academic conference. It takes place in Room A containing N Persons. Each person has a unique ID and one of four interests: epidemiology, biostatistics, clinical research, or health policy. At each timestep, a person is randomly chosen to approach another random person. The first person will inquire about the other person's interest. The second person should respond to the inquiry. If they both share the same interest, they leave the room together and go to Room B. Otherwise, they both rejoin the pool of available people. The simulation continues until there are no more possible groupings in Room A or a specified timestep T is reached.

## Simulation Details

The simulation incorporates the following features:

1. Timestep Delay: The simulation pauses for approximately 1 second before proceeding to the next timestep.
2. Interaction Details: Text describing each interaction (who greeted whom and whether their interests matched) is printed for each timestep.
3. Internal State: The simulation prints its internal state, including who is in Room A and Room B, as well as the current grouping of individuals, at the end of each timestep.
4. Person Information Retrieval: A function is provided to retrieve a person's interest and location (Room A or Room B) when given their ID. This function can be called from the main event loop.

## Usage

To run the simulation, follow these steps:

1. Clone the repository:

   ```shell
   git clone https://github.com/your-username/cocktail-party-simulation.git


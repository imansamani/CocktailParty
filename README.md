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

## Solution

The simulation is implemented in both Python and C++. In both source codes, there are two objects: Person and Room. Each person is assigned a unique ID based on their interest, and initially, their location is set to null. Once a person moves to a room, their location is updated accordingly. Internally, the interests of the individuals are stored after moving them to Room A, and the count of persons with the same interest is maintained. The interest information is updated when a person leaves the room. This approach allows for checking if there is a possible grouping at each timestep.

To optimize access to the interests and person information, hash maps are used, resulting in constant access time regardless of the simulation size N. In Python, this results in O(1) time complexity and O(N) space complexity per timestep. However, in the C++ code, since randomly selecting a person from Room A requires scanning the hash map, the time complexity becomes O(N), while the space complexity remains O(N).

## Ideas

Given the assumption that the simulation will continuously increase in complexity, it becomes essential to revisit the random sampling approach in the C++ implementation to achieve a constant time complexity. Additionally, it might be interesting to explore alternative strategies for managing people interactions that are not solely based on randomness. This could involve investigating if an optimal solution exists for determining the number of timesteps before no more possible groupings are available. Such an analysis could potentially lead to more efficient and deterministic approaches to simulate the cocktail party scenario.

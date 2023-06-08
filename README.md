# Cocktail Party Simulation
## Problem Statement
We want to simulate a cocktail party at an academic conference. It takes place in a Room A
containing N Persons. Each person has a unique ID and 1 of 4 interests {epidemiology, biostatistics,
clinical research, health policy} which are assigned at random. At each timestep, a person should be chosen
at random to approach another random person. The first person will inquire to the other about their interest.
The 2nd person should answer the inquiry. If they both share the same interest, then they leave the room
together and go to Room B. Otherwise, they will both rejoin the pool of available people. At the next
timestep, another person will be chosen at random to approach another etc. etc. The sim continues until
there are no more possible groupings in Room A or timestep T is reached.

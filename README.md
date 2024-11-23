# Rover Run!
## Overview
As a part of the ESTF (Efrei Space Task Force) the team MLKJMLKJ answered to the help request of the MARC rover through Sir Nicolas Flasque, the director of the task force.
Due to the recent sun storm on mars, Marc is damaged. Our algorithm is going to help it to find back the base so that it can send us his mars samples.
Our algorithm is mainly composed of a tree function allowing Marc to think about all the possible moves it can do.
## Features

### Key Capabilities
1. **A fency lunching menu for ESTF administrator**:
    - Interactive menu system to configure mission parameters.
    - Ability to customize maps, terrain types, and mission complexity.

2. **Optimal Pathfinding**:
    - Implemented N-ary tree to simulate each MARC's possible movements in a phase.
    - In each phase selects the best movement's combinations using cost minimization techniques.

3. **Terrain Handling**:
    - Incorporates various Martian terrains, including plains, ergs, slopes, and crevasses.
    - Adjusts movement and cost calculations based on terrain effects.

4. **Complexity Analysis**:
    - Tracks and reports computational time complexity for tree construction, pathfinding, and overall mission execution.
      
5. **Animated Map**:
    - Map satellite imagery, we've sent a satellite on Mars so that you can see each move done by Marc.

## Project Structure
```plaintext
.
├── main.c                  # Main program entry point
├── menu.c                  # User interface for differents missions
├── menu.h                  # Function declarations for menu.c
├── CMakeLists.txt          # Build configuration
├── maps/                   # Input data for terrain configurations
├── created/                # Generated files and outputs
│   ├── node.c                 # Nodes of N-ary tree and queue of nodes
│   ├── node.h                 # Function declarations for node.c
│   ├── tree.c                 # Most of the work: tree generation, phase system, finding minLeaf, path...
│   └── tree.h                 # Function declarations for tree.c
└── modified/               # Files of the given which we modified
```

## How It Works

1. **Interactive Menu**:
    - Users configure the mission parameters, such as map size, movement options, and terrain complexity.

2. **Tree-Based Pathfinding**:
    - Constructs an N-ary tree using a queue of node, for each node in the queue we have to create its children. This part take in consideration the martian ground such as erg and crevasses.
    - Identifies the optimal sequence of moves by finding the leaf with the minimal cost and then finding back its combination of moves from the root.

3. **Complexity Metrics**:
    - Evaluating the time of execution of the main function in second or microseconds. We give also the time of a full sequence until Marc reach the base.


### Build Instructions
Our project is done in C version 11, on windows.<br>
I advise you to lunch it in the Windows terminal, the CMakeLists.txt is included.

## Example Workflow
1. **Start the program:**
    - Navigate through the menu to choose a mission or configure one (map, coordinate of beginning, displayed elements).

2. **Execution of the simulation:**
    - MARC will find the best moves for a phase.
    - Then, if you chose it, the map, number of phase and execution times will be displayed.
    - Please note that the execution time will be longer if you choose to display the map, due to the printing time and the delay of 1 seconde between each move.



## Creators
Sophie Jaffal, Aube Ramassamy, Pierre Mouriès
## License
This project is part of the **Efrei Paris** coursework for **TI301 - Algorithms and Data Structures 2** and is for educational purposes.



<br>

***The global structure of this document and some sentences were written by Chat gpt.*** 

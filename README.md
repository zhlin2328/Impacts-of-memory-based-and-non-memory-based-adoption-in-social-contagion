# Impacts-of-memory-based-and-non-memory-based-adoption-in-social-contagion
These are the related files for 'Impacts-of-memory-based-and-non-memory-based-adoption-in-social-contagion'. The repository contains code files.

# Simulation Code

This repository contains the simulation part.

## Usage Instructions

### 1. Modify Network File Path

Before running the simulation, open the file:

```
set_parms.h
```

and update the network file path to the correct location of your network data.

### 2. Compile the Code

Use the following command in the terminal to compile the simulation code after changing the directory to 'sources':

```bash
make
```

### 3. Run the Simulation

After successful compilation, run the following script to start the simulation:

```bash
./rename_and_submit.sh
```

## Parameter Notes

In the file `set_parms.cpp`, the parameter:

```cpp
g_Spd.MEMORY_LEN - 1
```

corresponds to the **memory length** \(m\) as defined in the paper.

---

Feel free to adjust other parameters as needed for your experiments.

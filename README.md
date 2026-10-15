# Banker's Algorithm Simulation — OS Mini Project

## Files
- `bankers_algorithm.c` — complete C source code
- `project_report.pdf` — formatted engineering mini-project report
- `flowchart.png` — flowchart diagram

## Compile and run
Using GCC:
```bash
gcc bankers_algorithm.c -o bankers
./bankers
```
On Windows:
```bash
gcc bankers_algorithm.c -o bankers.exe
bankers.exe
```

## Sample test data
Processes: `5`
Resource types: `3`

Allocation:
```text
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
```

Maximum:
```text
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
```

Available:
```text
3 3 2
```

Expected safe sequence: `P1 -> P3 -> P4 -> P0 -> P2`

Note: The program assumes valid non-negative resource counts and checks that each Maximum value is at least its Allocation value.

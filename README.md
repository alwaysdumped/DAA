# DAA
Tomita Clique Finder

This project implements the Tomita Algorithm for finding maximal cliques in an undirected graph. The implementation reads a graph from a dataset file, processes it using the Bron-Kerbosch variant with pivot selection, and outputs the discovered cliques along with statistical analysis.
Features
Graph Parsing: Reads an edge list from a file.
Maximal Clique Detection: Uses an optimized Bron-Kerbosch algorithm (Tomita et al.) to find all maximal cliques.
Performance Measurement: Measures execution time and logs statistics such as clique size distribution.
Results Export: Saves clique statistics and execution times to a file.

Requirements

C++ compiler (supports C++11 or later)

Compilation and Execution
Compilation

Use g++ to compile the program:
 g++ -o tomita_clique_finder main.cpp

Running the Program
 ./tomita_clique_finder

Input Format
The program reads graph data from a text file (e.g., as-skitter.txt). The format should be:
# Comment lines start with #
1 2
2 3
3 4
...
Each line represents an edge between two vertices.
The input text file should be placed in the same directory as the code and the path should be updated in the code.

Output
Results are saved in cliques_skitter.txt, containing:
Total number of maximal cliques found
Size of the largest clique
Execution time in milliseconds
Distribution of clique sizes

Example Output
Dataset: as-skitter.txt
Total cliques found: 12345
Largest clique size: 6
Execution time: 1500 ms
Clique size distribution:
Size 3: 5000 cliques
Size 4: 4000 cliques
Size 5: 2000 cliques
Size 6: 345 cliques
-----------------------------

References
Bron-Kerbosch Algorithm
Tomita et al. Pivoting Strategy


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

Comment lines start with #

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





------------------------------------------------

Bron–Kerbosch Maximal Clique Finder

This project implements the Bron–Kerbosch algorithm (with degeneracy ordering) to find all maximal cliques** in an undirected graph. It reads a graph from a file, computes degeneracy ordering, and applies an optimized recursive Bron–Kerbosch algorithm.

Project Structure

- “ELS.cpp”: Main source file containing graph structure, Bron–Kerbosch implementation, and logic to load data and run the algorithm.

 Dependencies

- Standard C++ libraries only (“iostream”, “fstream”, “unordered_map”, “unordered_set”,”vector”,”sstream”,algorithm”,”chrono”,”climits”)
- C++11 .

Compilation

Use “g++" to compile the program:


g++ -std=c++11 -o ELS ELS.cpp

.\ELS.exe <datasetFile> 

<datasetFile>: Path to the text file containing the edge list of the graph.


Input Format

The file should contain edges, one per line, in the format:

u v

Lines starting with # or empty lines are ignored.

Example:

1 2

2 3

3 1

4 5

This represents a graph with two components, one of which is a triangle (1–2–3–1), and the other a simple edge (4–5).

Output

The program will print:

Number of vertices and edges.


Number of vertices in degeneracy order.


Largest clique size.


Total number of maximal cliques found.


Execution time.


Distribution of cliques by size.


Example:

c++

CopyEdit

Processing the dataset graph.txt

The file is loaded now with 6 edges.

Graph loaded with 5 vertices

Bron Kerbosch Algorithm gives

no. of vertices are:5

no. of edges are:6

No of elements in the degeneracy ordering:5

The largest clique size is- 3

The total maximal cliques are 2

The execution time is 0.000123 secs


Clique Size distribution:

Clique size is:3 : 1 occurrences

Clique size is:2 : 1 occurrences

Algorithm Used

Bron–Kerbosch with pivoting and degeneracy ordering.

Efficiently finds all maximal cliques in sparse graphs.

Notes

The program maps input vertex labels to internal indices to improve memory efficiency.

Self-loops are ignored.

Duplicate edges are implicitly handled using unordered_set.



--------------------------------------------------

Maximal Clique Listing Algorithms

This project contains two well-known algorithms for finding *maximal cliques* in undirected graphs:

1. “Bron–Kerbosch Algorithm” (with degeneracy ordering)
2. “Chiba–Nishizeki Clique Listing Algorithm” (based on arboricity)

Both implementations are in C++ and take a graph as input in a simple edge list format.

 
 Files Included

- “bron_kerbosch.cpp” — Bron–Kerbosch algorithm with degeneracy optimization.
- “chiba.cpp” — Chiba–Nishizeki clique listing algorithm using arboricity.
- “README.md” — This documentation file.

How to Compile

Make sure you have a C++ compiler like “g++”. Then run:


g++ -std=c++11 -O2 -o bron bron_kerbosch.cpp

g++ -std=c++11 -O2 -o chiba chiba.cpp

How to Run

Both programs take a graph file as input:

./bron <graph_file>

./chiba <graph_file>

The graph file should be a simple text file with one edge per line:

1 2

2 3


3 1

4 5


Lines starting with # or blank lines are ignored.

Bron–Kerbosch Overview

Works well on sparse graphs.

Uses degeneracy ordering to reduce branching.

Efficient and easy to understand.

Outputs:

Number of vertices and edges

Largest clique size

Total number of maximal cliques

Clique size distribution

Execution time

Chiba–Nishizeki Overview

Based on arboricity of the graph.

Optimized for graphs with low arboricity, like planar or road network graphs.

Uses smart vertex ordering, auxiliary arrays, and pruning to improve performance.

Outputs each maximal clique directly.

May slow down on large graphs or dense networks.

Input Format (for both)

Each line contains two integers: u v meaning an undirected edge between u and v.

Vertex numbers can be any integers (they’ll be remapped internally).

No duplicate or self-loop edges are needed; the code handles those.

Output Examples

Bron–Kerbosch Output

Graph loaded with 100 vertices

Bron Kerbosch Algorithm gives:

Number of vertices: 100

Number of edges: 250

Largest clique size: 5

Total maximal cliques: 57

Execution time: 0.00312 secs

Clique Size distribution:

Size 3: 30 cliques

Size 4: 20 cliques

Size 5: 7 cliques

Chiba–Nishizeki Output

Clique: { 1 2 3 }

Clique: { 4 5 }

Clique: { 6 7 8 9 }

Notes

The Chiba–Nishizeki algorithm is very efficient for small or sparse graphs but may be slower on large datasets.

The Bron–Kerbosch version is generally more balanced and works well across different graph types.

Both programs are single-threaded.

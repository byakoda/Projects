# DNA Sequence and Protein Matching

This project is part of the C Programming course (CENG 140) at Middle East Technical University. The main objective is to analyze DNA sequences, identify introns and exons, and match the given DNA sequence to a protein sequence. This project allowed me to deepen my understanding of bioinformatics, dynamic memory allocation, and string manipulation in C.

## About the Developer
Hello! I’m Emre Akoda, a student at Middle East Technical University currently pursuing a degree in Computer Engineering.

I have a keen interest in programming and enjoy tackling challenges related to memory management, data structures, and system design. This project allowed me to deepen my understanding of DNA sequence analysis, dynamic memory allocation, and string manipulation in C.

Feel free to reach out if you have any questions or feedback regarding this project!

### Contact
You can contact me via:
- Email: eakoda10@gmail.com
- LinkedIn: [Emre Akoda](https://www.linkedin.com/in/emre-akoda-b07b36248)

## Table of Contents
- [Objectives](#objectives)
- [Specifications](#specifications)
- [Files](#files)
- [Functions](#functions)
- [Compilation and Execution](#compilation-and-execution)

## Objectives
The main objectives of this project are to:
1. Analyze DNA sequences to identify introns and exons.
2. Match the given DNA sequence to a protein sequence.
3. Implement the solution using dynamic memory allocation and string manipulation in C.

## Specifications
The project involves the following tasks:
1. **Input**: A list of nucleotides representing a gene, and a sequence of amino acids representing a protein.
2. **Output**: The start and end positions of introns, or "NONE" if the protein cannot be synthesized from the DNA sequence.

### DNA and Protein Details
- **Nucleotides**: A (Adenine), C (Cytosine), G (Guanine), T (Thymine).
- **Codons**: Groups of three nucleotides in exons that code for amino acids.
- **Introns and Exons**: Genes consist of functional parts (exons) and non-functional parts (introns). Only exons are used in protein synthesis.
- **mRNA**: Transcribed from DNA, mRNA is then translated into proteins.

### Example
**Input:**
- DNA Sequence: TCTGCAGCAGAGGGGCCGTC... (continues)
- Protein Sequence: rrrlpgsrlppepvrdaelvvhvevpttgqdtdpplvggpppvplspptedqdptflllipgtlprlf.
```makefile
**Output**
```
- 54 84 169 248
- There might be more than one solution for some cases.

## Files
- **the1.c**: The source code implementing the solution.
- **the1.pdf**: The problem statement and detailed instructions.

## Functions
1. **int main()**: The main function that reads input, processes the DNA and protein sequences, and outputs the results.
2. **void read_input(char *dna, char *protein)**: Reads the DNA and protein sequences from the terminal.
3. **void identify_introns(char *dna, char *protein, int *intron_positions)**: Identifies the positions of introns in the DNA sequence.
4. **void print_results(int *intron_positions)**: Prints the positions of introns or "NONE" if the protein cannot be synthesized.

## Compilation and Execution
### Compilation
To compile the project, use the following command:
```sh
gcc the1.c -o the1
```
### Execution
To run the compiled executable:
```sh
./the1 < input.txt
```

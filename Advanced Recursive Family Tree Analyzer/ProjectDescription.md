# Family Tree Analysis

This project is developed to analyze and extract kinship relationships from a given partial family tree. The family tree is represented as a nested list, and the program identifies relationships such as siblings, uncles, aunts, and cousins.This project allowed me to apply theoretical knowledge and gain practical experience in Python programming and recursive algorithms.

## About the Developer

Hello! I’m Emre Akoda, a student at Middle East Technical University currently pursuing a degree in Computer Engineering.
I have a keen interest in programming and enjoy tackling challenges related to memory management, data structures, and system design. This project allowed me to apply theoretical knowledge and gain practical experience in Python programming and recursive algorithms.

Feel free to reach out if you have any questions or feedback regarding this project!

### Contact
Contact
You can contact me via:

- Email: eakoda10@gmail.com
- LinkedIn: [Emre Akoda](https://www.linkedin.com/in/emre-akoda-b07b36248)

## Table of Contents
- [Objectives](#objectives)
- [Specifications](#specifications)
- [Functions](#functions)
- [Input and Output](#input-and-output)
- [Usage](#usage)
- [Example and Runs](#example-and-runs)

## Objectives
The main objectives of this project are to:

1. Analyze partial family tree data structures.
2. Implement functions to identify various kinship relationships.
3. Gain hands-on experience with recursion and nested lists in Python.

## Specifications
The project handles a partial family tree where each node can have at most one parent. The functions to be implemented include:

- brothers(T, pname): Returns the brothers of pname.
- sisters(T, pname): Returns the sisters of pname.
- siblings(T, pname): Returns the siblings of pname.
- uncles(T, pname): Returns the uncles of pname.
- aunts(T, pname): Returns the aunts of pname.
- cousins(T, pname): Returns the cousins of pname.

### Functional Requirements
- Gender Identification: Names starting with a lowercase letter are male, and names starting with an uppercase letter are female.
- Input Handling: No erroneous inputs will be provided.
- Output: Each function returns a list of names corresponding to the relationship queried.

## Functions
The main functions implemented in this project are:

### Brothers
```python
def brothers(T, pname):
    # Implementation
```
### Sisters
```python
def sisters(T, pname):
    # Implementation
```
### Siblings
```python
def siblings(T, pname):
    # Implementation
```
### Uncles
```python
def uncles(T, pname):
    # Implementation
```
### Aunts
```python
def aunts(T, pname):
    # Implementation
```
You can see implementations in the python file for funcitons.

## Input and Output

The family tree is represented as a nested list, and the functions take this list along with a person's name to determine the relationships.

```python
T = ['Fatma', ['sinan', 'Elif', 'mehmet'], 'veli', ['Ayse', 'Zeynep', 'fikret', 'hikmet']]
```

## Usage
To use this project, follow these steps:

1. Ensure you have Python installed on your system.
2. Save the project file as the4.py.
3. Run the functions with the desired input.

## Example and Runs
```python
>>> T = ['Fatma', ['sinan', 'Elif', 'mehmet'], 'veli', ['Ayse', 'Zeynep', 'fikret', 'hikmet']]
>>> cousins(T, 'Elif')
['Zeynep', 'fikret', 'hikmet']
>>> aunts(T, 'Zeynep')
[]
>>> uncles(T, 'Zeynep')
['sinan', 'veli']
```




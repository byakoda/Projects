# Overlapping Area Calculation between a Quadrilateral and a Triangle

This project aims to calculate the overlapping area between a convex quadrilateral and a triangle using Python. This project allowed me to apply theoretical knowledge to a practical problem, enhancing my skills in algorithm design and geometric computations. It not only allowed me to apply my theoretical knowledge but also provided practical experience with geometric computations and Python programming.

## About the Developer
Hello! I’m Emre Akoda, a student at Middle East Technical University currently pursuing a degree in Computer Engineering.

I have a keen interest in programming and enjoy tackling challenges related to memory management, data structures, and system design. This project not only allowed me to apply my theoretical knowledge but also provided practical experience with geometric computations and Python programming.

Feel free to reach out if you have any questions or feedback regarding this project!

### Contact
You can contact me via:

- Email: eakoda10@gmail.com
- LinkedIn: [Emre Akoda](https://www.linkedin.com/in/emre-akoda-b07b36248)

## Table of Contents
- [Objectives](#objectives)
- [Specifications](#specifications)
- [Function Definition](#function-definition)
- [Example Usage](#example-usage)
- [Usage](#usage)

## Objectives
The main objectives of this project are to:
1. Calculate the overlapping area between a given convex quadrilateral and a triangle.
2. Implement the algorithm efficiently in Python.
3. Gain hands-on experience with geometric algorithms and Python programming.

## Specifications
The project calculates the overlapping area between a convex quadrilateral and a triangle with the following specifications:
1. The quadrilateral and the triangle are given as lists of their corners in a clockwise order.
2. The function returns the intersection area as a real number.
3. The coordinates of the corners are integers.

### Functional Requirements
- **Area Calculation**: The function `area(Q, T)` calculates the overlapping area between a quadrilateral `Q` and a triangle `T`.

## Function Definition
The main function used in this project is:

### area
```python
def area(Q, T):
    """
    Calculate the intersection area between a convex quadrilateral and a triangle.

    Parameters:
    Q (list of tuples): List of coordinates representing the quadrilateral corners.
    T (list of tuples): List of coordinates representing the triangle corners.

    Returns:
    float: The intersection area.
    """
    # Implementation here
```
## Example Usage
To use the area(Q, T) function, you need to pass two lists of coordinates representing the quadrilateral and the triangle. The function will return the overlapping area between these two shapes.
```python
from the3 import area

Q = [(4,2), (1,7), (5,10), (11,5)]
T = [(4,4), (5,8), (13,5)]

result = area(Q, T)
print(f"The overlapping area is: {result}")
```

## Usage
To use this project:

1. Ensure you have Python installed.
2. Implement the area(Q, T) function in the the3.py file.
3. Test the function using the example usage provided.

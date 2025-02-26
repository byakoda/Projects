# Babysitting Schedule Feasibility Checker

This project aims to help a family check whether a proposed babysitting schedule is feasible or not, considering various rules and constraints associated with different caretakers. This project allowed me to apply theoretical knowledge to a practical problem, enhancing my skills in algorithm design and scheduling. It not only allowed me to apply my theoretical knowledge but also provided practical experience with scheduling algorithms and Python programming.


## About the Developer
Hello! I’m Emre Akoda, a student at Middle East Technical University currently pursuing a degree in Computer Engineering.

I have a keen interest in programming and enjoy tackling challenges related to memory management, data structures, and system design. This project not only allowed me to apply my theoretical knowledge but also provided practical experience with scheduling algorithms and Python programming.

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
1. Check the feasibility of a proposed babysitting schedule.
2. Implement the algorithm efficiently in Python.
3. Gain hands-on experience with scheduling algorithms and Python programming.

## Specifications
The project checks the feasibility of a babysitting schedule with the following specifications:
1. The babysitting schedule is given as a list of caretakers for each weekday of a month.
2. The function returns a list of breached rule numbers if any rules are breached, or the total cost of the schedule if it is valid.
3. The schedule includes various caretakers, each with their own availability and constraints.

### Functional Requirements
- **Schedule Checking**: The function `check_month(month_calendar)` checks the feasibility of the babysitting schedule and calculates the total cost if valid.

## Function Definition
The main function used in this project is:

### check_month
```python
def check_month(month_calendar):
    """
    Check the feasibility of a babysitting schedule.

    Parameters:
    month_calendar (list of str): List of caretakers for each weekday of a month.

    Returns:
    list or int: List of breached rule numbers if any rules are breached, or the total cost if valid.
    """
    # Implementation here
```

## Example Usage
To use the check_month(month_calendar) function, you need to pass a list of caretakers representing the babysitting schedule for each weekday of a month. The function will return a list of breached rule numbers if any rules are breached, or the total cost of the schedule if it is valid.

### Example
```python
from the2 import check_month

M1 = [
    "m", "b", "g", "b", "f",
    "m", "a1", "n", "a2", "f",
    "m", "b", "f", "a1", "b",
    "m", "b", "a1", "a2", "n"
]

result = check_month(M1)
print(result)  # Output: [2, 5, 6, 7]

M2 = [
    "g","m","f","a2","a1",
    "b","n","n","g","a1",
    "n","m","b","b","b",
    "b","m","f","b","a2",
    "a2"
]

result = check_month(M2)
print(result)  # Output: 645

```
## Usage
To use this project:

1. Ensure you have Python installed.
2. Implement the check_month(month_calendar) function in the the2.py file.
3. Test the function using the example usage provided.

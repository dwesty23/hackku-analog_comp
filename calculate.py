# calculate.py

import sys

def calculate_equation(equation):
    try:
        result = eval(equation)
        print("THIS IS THE EQUATION: ", equation)
        return str(result)
    except Exception as e:
        return str(e)

#!/bin/python3
"""
This file demonstrates how you would use the C Python module rhythm.so after you 
have compiled it. See run.sh for build instructions.
"""

# rhythm won't exist until you compile with run.sh
import rhythm  # type: ignore

# This is just a demo, you can modify or remove it.
start = [2, 3, 4]
size = 8
print(rhythm.permutations(start, size))

#!/usr/bin/env python
import condorcet

ranks = [
    [0, 1, 2],
    [1, 0, 2],
    [2, 1, 0]
]
winner = condorcet.find_winner(ranks, 3, 3)
print(f"Condorcet Winner: {winner}")

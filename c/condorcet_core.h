#include <stdio.h>
#include <string.h>

#define MAX_CANDIDATES 100

void calculate_pairwise_matrix(int ranks[][MAX_CANDIDATES], int num_voters, int num_candidates, int matrix[][MAX_CANDIDATES]) {
    for (int i = 0; i < num_candidates; i++) {
        for (int j = 0; j < num_candidates; j++) {
            if (i == j) {
                matrix[i][j] = 0; // No self-comparison
                continue;
            }
            int wins = 0;
            for (int v = 0; v < num_voters; v++) {
                if (ranks[v][i] < ranks[v][j]) { // Lower rank means higher preference
                    wins++;
                }
            }
            matrix[i][j] = wins;
        }
    }
}

int find_condorcet_winner(int matrix[][MAX_CANDIDATES], int num_candidates) {
    for (int i = 0; i < num_candidates; i++) {
        int is_winner = 1;
        for (int j = 0; j < num_candidates; j++) {
            if (i != j && matrix[i][j] <= matrix[j][i]) {
                is_winner = 0;
                break;
            }
        }
        if (is_winner) {
            return i; // Winner found
        }
    }
    return -1; // No winner
}

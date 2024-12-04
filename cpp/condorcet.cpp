#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <numeric> // Required for std::iota
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

class Condorcet {
private:
    int num_candidates;

    // Normalize the result table to percentage or scores
    std::vector<std::vector<double>> _get_normalized_table(const std::vector<std::vector<int>>& table) {
        std::vector<std::vector<double>> normalized(num_candidates, std::vector<double>(num_candidates, 0.0));
        for (int i = 0; i < num_candidates; i++) {
            for (int j = 0; j < num_candidates; j++) {
                if (i != j) {
                    normalized[i][j] = table[i][j] / static_cast<double>(table[i][j] + table[j][i]);
                }
            }
        }
        return normalized;
    }

public:
    Condorcet(int candidates) : num_candidates(candidates) {}

    // Evaluate votes for a pair of candidates
    int evaluate_votes_for_candidate_pair(const std::vector<std::vector<int>>& ranks, int candidate_0, int candidate_1) {
        int wins = 0;
        for (const auto& rank : ranks) {
            if (rank[candidate_0] < rank[candidate_1]) {
                wins++;
            }
        }
        return wins;
    }

    // Tabulate pairwise results
    std::vector<std::vector<int>> tabulate_pairwise_results(const std::vector<std::vector<int>>& ranks) {
        std::vector<std::vector<int>> results(num_candidates, std::vector<int>(num_candidates, 0));
        for (int i = 0; i < num_candidates; i++) {
            for (int j = 0; j < num_candidates; j++) {
                if (i != j) {
                    results[i][j] = evaluate_votes_for_candidate_pair(ranks, i, j);
                }
            }
        }
        return results;
    }

    // Get top N winners
    std::vector<int> get_n_winners_from_result_table(int n, const std::vector<std::vector<int>>& result_table) {
        std::vector<int> scores(num_candidates, 0);
        for (int i = 0; i < num_candidates; i++) {
            for (int j = 0; j < num_candidates; j++) {
                if (i != j && result_table[i][j] > result_table[j][i]) {
                    scores[i]++;
                }
            }
        }
        std::vector<int> indices(num_candidates);
        std::iota(indices.begin(), indices.end(), 0);
        std::sort(indices.begin(), indices.end(), [&scores](int a, int b) {
            return scores[a] > scores[b];
        });
        return std::vector<int>(indices.begin(), indices.begin() + std::min(n, num_candidates));
    }

	int get_winner_from_result_table(const std::vector<std::vector<int>>& result_table) {
    for (int i = 0; i < num_candidates; i++) {
        bool is_winner = true;
        for (int j = 0; j < num_candidates; j++) {
            if (i != j && result_table[i][j] <= result_table[j][i]) {
                // Candidate i doesn't beat candidate j
                is_winner = false;
                break;
            }
        }
        if (is_winner) {
            return i; // Found the Condorcet winner
        }
    }
    return -1; // No winner
}

    // Drop a candidate from the result table
    void drop_candidate_from_result_table(int candidate, std::vector<std::vector<int>>& result_table) {
        for (int i = 0; i < num_candidates; i++) {
            result_table[i][candidate] = 0;
            result_table[candidate][i] = 0;
        }
    }
};

// Bind the Condorcet class to Python
PYBIND11_MODULE(condorcet, m) {
    py::class_<Condorcet>(m, "Condorcet")
        .def(py::init<int>())
        .def("evaluate_votes_for_candidate_pair", &Condorcet::evaluate_votes_for_candidate_pair)
        .def("tabulate_pairwise_results", &Condorcet::tabulate_pairwise_results)
        .def("get_n_winners_from_result_table", &Condorcet::get_n_winners_from_result_table)
        .def("get_winner_from_result_table", &Condorcet::get_winner_from_result_table)
        .def("drop_candidate_from_result_table", &Condorcet::drop_candidate_from_result_table);
}


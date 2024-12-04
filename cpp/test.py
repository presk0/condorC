#!/usr/bin/env python
import condorcet

def run_tests():
    # Test 1: Basic Condorcet winner
    print("Test 1: Basic Condorcet Winner")
    condorcet_obj = condorcet.Condorcet(3)
    ranks = [
        [0, 2, 1],  # Voter 1 prefers Candidate 0 > 1 > 2
        [1, 0, 2],  # Voter 2 prefers Candidate 1 > 0 > 2
        [2, 1, 0],  # Voter 3 prefers Candidate 2 > 1 > 0
    ]
    pairwise_results = condorcet_obj.tabulate_pairwise_results(ranks)
    print("Pairwise Results:")
    for row in pairwise_results:
        print(row)
    winner = condorcet_obj.get_winner_from_result_table(pairwise_results)
    assert winner == -1, f"Expected no winner, got {winner}"

    # Test 2: Clear Condorcet winner
    print("\nTest 2: Clear Condorcet Winner")
    ranks = [
        [0, 1, 2],  # Voter 1 prefers Candidate 0 > 1 > 2
        [0, 1, 2],  # Voter 2 prefers Candidate 0 > 1 > 2
        [2, 1, 0],  # Voter 3 prefers Candidate 2 > 1 > 0
    ]
    pairwise_results = condorcet_obj.tabulate_pairwise_results(ranks)
    print("Pairwise Results:")
    for row in pairwise_results:
        print(row)
    winner = condorcet_obj.get_winner_from_result_table(pairwise_results)
    assert winner == 0, f"Expected winner Candidate 0, got {winner}"

    # Test 3: Tie between all candidates
    print("\nTest 3: Tie between All Candidates")
    ranks = [
        [0, 1, 2],
        [1, 2, 0],
        [2, 0, 1],
    ]
    pairwise_results = condorcet_obj.tabulate_pairwise_results(ranks)
    print("Pairwise Results:")
    for row in pairwise_results:
        print(row)
    winner = condorcet_obj.get_winner_from_result_table(pairwise_results)
    assert winner == -1, f"Expected no winner, got {winner}"

    # Test 4: Top N winners
    print("\nTest 4: Top N Winners")
    ranks = [
        [0, 1, 2],
        [1, 0, 2],
        [1, 2, 0],
        [2, 1, 0],
    ]
    pairwise_results = condorcet_obj.tabulate_pairwise_results(ranks)
    top_2 = condorcet_obj.get_n_winners_from_result_table(2, pairwise_results)
    print(f"Top 2 Winners: {top_2}")
    assert len(top_2) == 2, f"Expected 2 winners, got {len(top_2)}"

    # Test 5: Dropping a candidate
    print("\nTest 5: Dropping a Candidate")
    candidate_to_drop = 1
    condorcet_obj.drop_candidate_from_result_table(candidate_to_drop, pairwise_results)
    print("Pairwise Results After Dropping Candidate 1:")
    for row in pairwise_results:
        print(row)

    print("\nAll tests passed successfully!")


if __name__ == "__main__":
    run_tests()


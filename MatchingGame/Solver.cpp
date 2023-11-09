/**************************************
 *    Author: Lluís Vinent Juanico    *
 *    Date: 09/11/2023                *
 **************************************/

#include "Solver.h"

using namespace std;

/// <summary>
/// The constructor must receive two vectors of strings, one for each column.
/// </summary>
Solver::Solver(const vector<string>& col1, const vector<string>& col2)
{
    this->column1 = col1;
    this->column2 = col2;
}

/// <summary>
/// Finds a solution to the matching problem.
/// </summary>
/// <returns>Returns an array of indexes representing the solution.</returns>
vector<int> Solver::Solve(const int maxDifference) {

    queue<Candidate> candidatesQueue;
    set<tuple<int, string>> seenSituations;

    // Fill with initial candidates
    for (int i = 0; i < column1.size(); i++) {
        Candidate initialCandidate;
        initialCandidate.indexes = { i };
        initialCandidate.s = column1[i];
        initialCandidate.t = column2[i];
        candidatesQueue.push(initialCandidate);
    }

    // While there are remaining candidates
    while (!candidatesQueue.empty()) {
        // Take the first candidate from the queue
        const Candidate& candidate = candidatesQueue.front();

        // If the candidate is acceptable and the current state is new
        if (Acceptable(candidate, maxDifference) && !DejaVu(candidate, seenSituations)) {
            // If the solution is complete
            if (Complete(candidate)) {
                return candidate.indexes;
            }
            // If it's not complete, add children to the queue
            else {
                for (int i = 0; i < column1.size(); i++) {
                    // Instantiate the new candidate
                    Candidate newCandidate = candidate;
                    // Update the vector
                    newCandidate.indexes.push_back(i);
                    // Update the strings
                    newCandidate.s.append(column1[i]);
                    newCandidate.t.append(column2[i]);
                    // Put the new candidate in the queue
                    candidatesQueue.push(newCandidate);
                }
            }
        }
        candidatesQueue.pop();
    }

    // No solution found. Try increasing the maximum difference.
    return Solve(maxDifference + 1);
}


/// <summary>
/// Checks if the candidate can potentially become a solution.
/// It's acceptable ⇔ s·c1, t·c2 ⇒ (s ∩ t)=(s ∪ t), where c is the new word.
/// </summary>
/// Pre: This method is executed with the premise that everything preceding the last added word is acceptable.
/// <returns>Returns true if s is a substring of t, or t is a substring of s. False otherwise.</returns>
bool Solver::Acceptable(const Candidate& candidate, const int& maxDifference) {
    const string& s = candidate.s;
    const string& t = candidate.t;
    const int sizeS = s.size();
    const int sizeT = t.size();

    // If the difference between the two strings has become too large,
    // we reject the possibility of it becoming a solution.
    int diff = sizeS - sizeT;
    if (abs(diff) > maxDifference)
        return false;

    // Check if the new word makes string 't' cease to be a substring of 's' (or 's' a substring of 't')
    // Important: This method is executed with the premise that everything preceding the last added word is acceptable,
    // so we only need to check the last added word, not the entire string.
    const string& shorter = (sizeS > sizeT) ? t : s;
    const int& newIndex = candidate.indexes.back();
    const int newWordLength =
        (sizeS > sizeT) ? column2[newIndex].size() :
        (sizeS < sizeT) ? column1[newIndex].size() :
        max(column1[newIndex].size(), column2[newIndex].size());

    int end = shorter.size() - newWordLength;
    for (int i = shorter.size() - 1; i >= end; i--) {
        if (s[i] != t[i])
            return false;
    }

    return true;
}


/// <summary>
/// Checks if the candidate is in a situation that has been analyzed before.
/// For example:
/// Case 1: (s1 = AAB, t1 = A)
/// Case 2: (s2 = abbaAAB, t2 = abbA)
/// There's no need to recheck Case 2 because any state it can reach has already been covered by Case 1.
/// In other words, Case 2 is a déjà vu of Case 1; we reject it.
/// </summary>
/// <returns>True if it's a déjà vu (a previously seen situation), false otherwise.</returns>
bool Solver::DejaVu(const Candidate& candidate, set<tuple<int, string>>& seenSituations) {
    const string& s = candidate.s;
    const string& t = candidate.t;
    // Calculate the difference between s and t
    int lengthDifference = s.size() - t.size();
    // Declare the string that will hold the difference and allocate the necessary memory
    string difference;
    // If s is longer than t
    if (lengthDifference > 0)
        difference = s.substr(t.size() - 1, s.size() - t.size() + 1);
    // If t is longer than s
    else
        difference = t.substr(s.size() - 1, t.size() - s.size() + 1);

    tuple<int, string> currentSituation = make_tuple(lengthDifference, difference);
    // Have we seen this situation before?
    bool dejavu = seenSituations.find(currentSituation) != seenSituations.end();
    // If the situation is new, store it
    if (!dejavu)
        seenSituations.insert(currentSituation);
    return dejavu;
}


/// <summary>
/// Checks if the solution is complete and valid.
/// </summary>
/// <returns>True if it's a complete and valid solution, false otherwise.</returns>
bool Solver::Complete(const Candidate& solution) {

    // The fact that we've executed the 'Acceptable' method at each previous
    // iteration ensures that if the strings are the same length, they're actually equal.
    return solution.s.size() == solution.t.size();
}

#pragma once
#include <vector>
#include <string>
#include <tuple>
#include <queue>
#include <set>

using namespace std;

class Solver {
public:
    Solver(const vector<string>& col1, const vector<string>& col2);
    vector<int> Solve(const int maxDifference = 1);

private:
    struct Candidate {
        vector<int> indexes;
        string s;
        string t;
    };
    bool Acceptable(const Candidate& candidate, const int& maxDifference);
    bool DejaVu(const Candidate& candidate, set<tuple<int, string>>& seenSituations);
    bool Complete(const Candidate& solution);

    vector<string> column1;
    vector<string> column2;
};
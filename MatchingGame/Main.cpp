#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "Solver.h"

using namespace std;

void ReadFile(string);
void ShowSolution(const vector<int>& solution);
void CheckSolution(const vector<int>& solution);

vector<string> column1;
vector<string> column2;

int main() {

    double totalTime = 0;

    string files[9] =
    {
        "easy1.txt", "easy2.txt","easy3.txt","easy4.txt", "easy5.txt",
        "hard1.txt", "hard2.txt", "hard3.txt", "hard4.txt"
    };

    // For each file
    for (int i = 0; i < 9; i++)
    {
        string fileName = files[i];
        cout << fileName << endl;
        ReadFile(fileName);

        // Start the timer
        auto start = std::chrono::high_resolution_clock::now();
        Solver solver = Solver(column1, column2);
        // Find the solution
        vector<int> solution = solver.Solve();
        // Stop the timer
        auto end = std::chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        totalTime += duration.count();
        // If a solution is found
        if (!solution.empty()) {
            // Show the solution
            ShowSolution(solution);
            // Check if the solution is correct
            CheckSolution(solution);
            cout << endl << "Execution time: " << duration.count() << " seconds" << endl << endl;
        }
        else {
            cout << "No solution found" << endl << endl;
        }
    }

    cout << "The total duration for all files was " << totalTime << " seconds." << endl;

    return 0;
}

void ReadFile(string fileName)
{
    column1.clear();
    column2.clear();

    ifstream file(fileName);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string left, right;
            char comma;

            if (getline(ss, left, ',') && getline(ss, right)) {
                left.erase(remove(left.begin(), left.end(), '('));
                right.erase(remove(right.begin(), right.end(), ')'));
                column1.push_back(left);
                column2.push_back(right);
            }
        }
        file.close();
    }
    else
        cout << "Error reading the file " << fileName;
}

void ShowSolution(const vector<int>& solution)
{
    cout << "Solution: ";
    for (int i = 0; i < solution.size(); i++)
    {
        cout << solution[i] + 1;
    }
    cout << " (length " << solution.size() << ")";
}

void CheckSolution(const vector<int>& solution)
{
    cout << endl << "Test: ";
    string s = "";
    string t = "";
    for (int i = 0; i < solution.size(); i++)
    {
        s += column1[solution[i]];
        t += column2[solution[i]];
    }
    if (s == t)
        cout << "CORRECT";
    else
        cout << "ERROR";
}

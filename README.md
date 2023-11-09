# The Matching Game

<i>This is a programming challenge proposed by Professor Dr. Miquel Bofill Arasa, from the Computer Fundamentals subject at the University of Girona.</i>

## Challenge explanation
The matching game consists of, given a list of pairs of words
<p align="center"><i>
(s1, t1)<br>
(s2, t2)<br>
·<br>
·<br>
·<br>
(sn, tn)
</i></p><br>
find a sequence of indexes i<sub>1</sub>, i<sub>2</sub>, . . . , i<sub>k</sub> such that
<p align="center"><i>
s<sub>i<sub>1</sub></sub> s<sub>i<sub>2</sub></sub> ··· s<sub>i<sub>k</sub></sub> = t<sub>i<sub>1</sub></sub> t<sub>i<sub>2</sub></sub> ··· t<sub>i<sub>k</sub></sub>
</i></p><br>
Example: <i>Given the list of word pairs</i>
<p align="center"><i>
(a, baa)<br>
(ab, aa)<br>
(bba, bb)
</i></p><br>
<i>a possible solution would be</i>
<p align="center">3231</p><br>
<i>since</i>
<p align="center">
<img width="325" alt="d7beca6c6882cccb1a403effb7b292ed-removebg-preview" src="https://github.com/LluisV/MatchingGame/assets/100292815/72c55831-4d5c-4506-a736-1c72283e852b">
</p>


## Explanation of Proposed Solution

My proposed solution is based on a BFS (Breadth-First Search) scheme, chosen over DFS (Depth-First Search) to circumvent the pitfalls of cyclic branches.

```c++
queue<Candidate> candidatesQueue;

// Fill the queue with initial candidates
...

while (!candidatesQueue.empty()) {
    const Candidate& candidate = candidatesQueue.front();
    // If the candidate can become a solution
    if (Acceptable(candidate)) {
        // If the solution is complete, return it
        if (Complete(candidate)) {
            return candidate.indexes;
        }
        // If it's not complete, add new candidates to the queue
        else {
            ...
        }
    }
    candidatesQueue.pop();
}

```

#### Basic optimizations:
- Optimize function calls by passing parameters by reference.<br>
- In the 'Acceptable' method, there's no need to explicitly check for string equality; verifying that the most recent addition doesn't hinder equality suffices.<br>
- The 'Complete' method only needs to ensure that the two strings are of the same length; the 'Acceptable' method has already confirmed their equality.

#### Advanced optimizations:
- Check if the current candidate is a 'Déjà Vu'.<br> 
Example:<br> 
State 1: (s1 = AAB, t1 = A)<br> 
State 2: (s2 = abbAAB, t2 = abbA)<br>
State 2 can be rejected, as any state it can reach is already covered by State 1.<br><br>
Utilizing an exceptionally efficient data structure in terms of searching is crucial. While a <i>set</i> offers a commendable search cost of O(log n), making it easily implementable and versatile across various data types, our pursuit of maximum efficiency leads us to opt for an <i>unordered_set</i>. This unordered_set employs a custom data type named 'State', which incorporates its own hash function. This strategic choice is anticipated to yield a search cost of O(1), further enhancing the overall efficiency of our soulution.<br><br>
- Prune branches that stray too far from a possible solution.<br>
When there is a substantial difference in length between the two resulting strings, denoted as <i>s</i> and <i>t</i>, it is reasonable to infer that the likelihood of convergence diminishes. Consequently, when the disparity in length surpasses a specified threshold, we opt to discard the candidate. In the absence of a solution after evaluating all candidates, we increment the maximum number and initiate a new iteration.

## Compile & Run [GNU/LINUX]

Clone the project

```bash
  git clone github.com/LluisV/MatchingGame
```

Go to the project directory

```bash
  cd MatchingGame/MatchingGame
```

Compile

```bash
  g++ -O3 -o MatchingGame *.cpp
```

Run

```bash
  ./MatchingGame
```

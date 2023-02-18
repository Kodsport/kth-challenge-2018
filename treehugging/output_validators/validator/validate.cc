#include <vector>
#include <tuple>
#include <cstring>
#include "validate.h"

using namespace std;

pair<int, vector<pair<int, int>>> read_input(istream &in) {
    int n;
    in >> n;
    vector<pair<int, int>> P(2*(n-1));
    for (auto &v: P) {
        in >> v.first >> v.second;
    }
    return {n, P};
}

vector<bool> read_solution(int n, istream &sol, feedback_function feedback) {
    string S;
    if (!(sol >> S)) {
        feedback("Output file seems to be empty");
    }
    vector<bool> res;
    if (!strcasecmp(S.c_str(), "impossible")) {
        // do nothing, just return empty array
    } else {
        if (S.length() != 2*(n-1)) {
            feedback("%s is not a string of length exactly %d", S.c_str(), 2*(n-1));
        }

        res.resize(2*(n-1));
        for (int i = 0; i < 2*(n-1); ++i) {
            if (S[i] != 'L' && S[i] != 'R') {
                feedback("%s contains invalid characters (non-LR in position %d)", S.c_str(), i);
            }
            res[i] = (S[i] == 'R');
        }
    }
    if (sol >> S) {
        feedback("Trailing output");
    }
    return res;
}

void check_solution(int n, const vector<pair<int, int>> &P, const vector<bool> &Sol, feedback_function feedback) {
    vector<int> leftPars(n), rightPars(n);
    assert((int)P.size() == 2*(n-1));
    assert((int)Sol.size() == 2*(n-1));
    for (int i = 0; i < 2*(n-1); i++) {
        int a = P[i].first - 1;
        int b = P[i].second - 1;
        assert(a < b);
        if (Sol[i]) {
            rightPars[a]++;
        } else {
            leftPars[b]++;
        }
    }

    for (int i = 0; i < n-1; i++) {
        if (leftPars[i+1] != 1) {
            feedback("node %d has wrong number of parents in L tree (%d; should be 1)", i+2, leftPars[i+1]);
        }
        if (rightPars[i] != 1) {
            feedback("node %d has wrong number of parents in R tree (%d; should be 1)", i+1, rightPars[i]);
        }
    }

    assert(leftPars[0] == 0);
    assert(rightPars[n-1] == 0);
}


int main(int argc, char **argv) {
    init_io(argc, argv);

    int n;
    vector<pair<int, int>> P;
    tie(n, P) = read_input(judge_in);
    vector<bool> Out = read_solution(n, cin, wrong_answer);
    vector<bool> Ans = read_solution(n, judge_ans, judge_error);
    if (Out.empty()) {
        if (!Ans.empty()) {
            wrong_answer("'impossible' claimed, but there is a solution");
        }
    } else {
        check_solution(n, P, Out, wrong_answer);
        if (Ans.empty()) {
            judge_error("judge answer says 'impossible', but submission found a valid solution");
        }
    }

    accept();
}

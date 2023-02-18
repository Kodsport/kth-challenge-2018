#include <vector>
#include <tuple>
#include <cstring>
#include "validate.h"

using namespace std;

pair<int, vector<int>> read_input(istream &in) {
    int n, s;
    in >> n >> s;
    vector<int> P(s);
    for (int &v: P)
        in >> v;
    return make_pair(n, P);
}

int parse_binary(int n, const string &S, feedback_function feedback) {
    if (S.length() != n) {
        feedback("%s is not a (binary) string of length exactly %d", S.c_str(), n);
    }
    int val = 0;
    for (int i = 0; i < n; ++i) {
        if (S[i] != '0' && S[i] != '1') {
            feedback("%s is not a binary string (non-01 in position %d)", S.c_str(), i);
        }
        if (S[i] == '1') {
            val += 1<<(n-i-1);
        }
    }
    return val;
}

// Reads a claimed solution (and checks formatting of the input stream)
vector<int> read_solution(int n, istream &sol, feedback_function feedback) {
    string tok;
    if (!(sol >> tok)) {
        feedback("Output file seems to be empty");
    }
    vector<int> res;
    if (!strcasecmp(tok.c_str(), "impossible")) {
        // do nothing, just return empty array
    } else {
        res.push_back(parse_binary(n, tok, feedback));
        for (int i = 1; i < (1<<n); ++i) {
            if (!(sol >> tok)) {
                feedback("Failed to read %d'th string (EOF reached?)", i+1);
            }
            res.push_back(parse_binary(n, tok, feedback));
        }
    }
    if (sol >> tok) {
        feedback("Trailing output");
    }
    return res;
}

// Checks that a claimed solution is a permutation, and has all adjacent Hamming differences in P
void check_solution(int n, const vector<int> &P, const vector<int> &Sol, feedback_function feedback) {
    vector<bool> seen(1<<n, false);
    vector<bool> diff_ok(n+1, false);
    for (int p: P)
        diff_ok[p] = true;
    for (int i = 0; i < (1<<n); ++i) {
        if (seen[Sol[i]]) {
            feedback("value %X repeated", Sol[i]);
        }
        seen[Sol[i]] = true;
        if (i) {
            int diff = __builtin_popcount(Sol[i] ^ Sol[i-1]);
            if (!diff_ok[diff]) {
                feedback("transition %d: %X -> %X has forbidden diff %d", i, Sol[i-1], Sol[i], diff);
            }
        }
    }
}


int main(int argc, char **argv) {
    init_io(argc, argv);

    int n;
    vector<int> P;
    tie(n, P) = read_input(judge_in);
    vector<int> Out = read_solution(n, cin, wrong_answer);
    vector<int> Ans = read_solution(n, judge_ans, judge_error);
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

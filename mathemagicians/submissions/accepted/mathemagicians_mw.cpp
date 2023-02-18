#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = (a); i < int(b); ++i)
#define rrep(i, a, b) for(int i = (a) - 1; i >= int(b); --i)
#define trav(it, v) for(typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)
#define all(v) (v).begin(), (v).end()

typedef double fl;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpi;

char start[100005], stop[100005];
int startC, stopC;

int countChange(char* s){
	int ret=0;
	int len=strlen(s);
	rep(i,0,len){
		if(s[i] != s[(i+1)%len])
			++ret;
	}
	return ret;
}

int main(){
	int N;
	scanf("%d", &N);
	scanf("%s", start);
	scanf("%s", stop);
	startC=countChange(start);
	stopC=countChange(stop);
	if(stopC < startC){
		puts("yes");
		return 0;
	}
	if(stopC > startC || startC == strlen(start) || !startC){
		puts("no");
		return 0;
	}
	puts("yes");
}

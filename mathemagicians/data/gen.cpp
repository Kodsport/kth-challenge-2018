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

int N;
char start[100005], stop[100005];

void print(){
	printf("%d\n%s\n%s\n", N, start, stop);
}

void random(int argc, char ** argv){
    	if(argc < 4) fprintf(stderr, "not enough arguments\n");
    	else {
      		int seed = atoi(argv[2]);
      		srand(seed);
      		N = atoi(argv[3]);
		bool different = false;
		rep(i,0,N){
			if(rand()&1)
				start[i]='R';
			else
				start[i]='B';
			if(rand()&1)
				stop[i]='R';
			else
				stop[i]='B';
			if(start[i] != stop[i])
				different=true;
		}
		if(!different){
			if(stop[0] == 'R')
				stop[0]='B';
			else
				stop[0]='R';
		}
		print();
    	}
}

void monoColoured(int argc, char ** argv){
    	if(argc < 4) fprintf(stderr, "not enough arguments\n");
    	else {
      		int seed = atoi(argv[2]);
      		srand(seed);
      		N = atoi(argv[3]);
		char startColour='R';
		char stopColour='B';
		if(rand()&1){
			startColour='B';
			stopColour='R';
		}
		rep(i,0,N){
			start[i]=startColour;
			stop[i]=stopColour;
		}
		print();
    	}
}

void everyOther(int argc, char ** argv){
    	if(argc < 4) fprintf(stderr, "not enough arguments\n");
    	else {
      		int seed = atoi(argv[2]);
      		srand(seed);
      		N = atoi(argv[3]);
		char startColour='R';
		char stopColour='B';
		if(rand()&1){
			startColour='B';
			stopColour='R';
		}
		rep(i,0,N){
			start[i]=startColour;
			stop[i]=stopColour;
			swap(startColour, stopColour);
		}
		print();
    	}
}

set<int> generateRegions(int N, int R, char* s){
	set<int> S;
	rep(i,0,R){
		while(true){
			int j=(193LL*rand()+rand())%N;
			if(S.count(j))
				continue;
			S.insert(j);
			break;
		}
	}
	int p=0;
	char c=rand()%2?'R':'B';
	for(auto it=S.begin(); it != S.end(); ++it){
		while(p < *it){
			s[p++]=c;
		}
		if(c == 'R')
			c='B';
		else
			c='R';
	}
	while(p < N){
		s[p++]=c;
	}
	return S;
}

void regionNumber(int argc, char ** argv){
    	if(argc < 6) fprintf(stderr, "not enough arguments\n");
    	else {
      		int seed = atoi(argv[2]);
      		srand(seed);
      		N = atoi(argv[3]);
		int startR = atoi(argv[4]);
		int stopR = atoi(argv[5]);
		while(true){
			set<int> startPos = generateRegions(N, startR, start);
			set<int> stopPos = generateRegions(N, stopR, stop);
			bool different = false;
			rep(i,0,N){
				if(start[i] != stop[i])
					different=true;
			}
			if(different)
				break;
		}
		print();
    	}
}

int main(int argc, char **argv){
  if(argc == 1) fprintf(stderr, "no method\n");
  else if(!strcmp(argv[1], "random")){
	  random(argc, argv);
  }else if(!strcmp(argv[1], "monoColoured")){
	  monoColoured(argc, argv);
  }else if(!strcmp(argv[1], "everyOther")){
	  everyOther(argc, argv);
  }else if(!strcmp(argv[1], "regionNumber")){
	  regionNumber(argc, argv);
  } else {
  	fprintf(stderr, "invalid method\n");
  }
}


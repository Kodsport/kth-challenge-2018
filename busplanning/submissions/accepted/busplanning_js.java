import java.util.*;

public class busplanning_js {

	public static void main(String... args){
		new busplanning_js().solve();
	}

	int N, K, C;
	public static final int max_kids = 17;
	Map<String, Integer> ids = new HashMap();
	Map<Integer, String> names = new HashMap();
	
	int[] enemies = new int[max_kids];
	boolean[] valid = new boolean[1<<max_kids];
	int[] dp = new int[1<<max_kids];
	
	void solve(){
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		K = sc.nextInt();
		C = sc.nextInt();
		for(int i = 0; i<N; i++){
			String name = sc.next();
			ids.put(name, i);
			names.put(i, name);
		}
		for(int i = 0; i<K; i++){
			String a = sc.next(), b = sc.next();
			int an = ids.get(a);
			int bn = ids.get(b);
			enemies[an] |= 1<<bn;
			enemies[bn] |= 1<<an;
		}
		for(int i = 0; i<1<<N; i++){
			int bsForbidden = 0;
			int bsIncluded = 0;
			for(int j = 0; j<N; j++){
				if((i & 1<<j) != 0){
					bsForbidden |= enemies[j];
					bsIncluded |= 1<<j;
				}
			}
			valid[i] = Long.bitCount(i) <= C && (bsForbidden&bsIncluded) == 0;
		}
		Arrays.fill(dp, 10000);
		dp[0] = 0;
		for(int i = 1; i<1<<N; i++){
			int min = dp[i];
			for(int j = i; j > 0; j=(j-1)&i){
				if(valid[j]){
					min = Math.min(min, 1+dp[i^j]);
				}
			}
			dp[i] = min;
		}
		int need = dp[(1<<N)-1];
		int left = (1<<N)-1;
		System.out.println(need);
		for(int i = need-1; i >= 0; i--){
			for(int j = left; j>0; j=(j-1)&left){
				if(dp[left^j] == i && valid[j]){
					left ^= j;
					int count = Long.bitCount(j);
					for(int k = 0; k<N; k++){
						if(((1<<k)&j) != 0){
							System.out.print(names.get(k)+(--count == 0 ? "" : " "));
						}
					}
					System.out.println();
					break;	
				}
			}
		}
	}
	
}

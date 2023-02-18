import java.util.Scanner;

public class fran_codes2 {

	public static void main(String[] args) {
		Scanner reader = new Scanner(System.in);
		int n = reader.nextInt();
		int k = reader.nextInt();
		int[] P = new int[k];
		for(int i = 0; i < k; i++) {
			P[i] = reader.nextInt();
		}
		greedy(n, P);
		reader.close();
	}


	static int next(int v) {
		int t = (v | (v - 1)) + 1;  
		int w = t | ((((t & -t) / (v & -v)) >> 1) - 1);  
		return w;
	}

	static String bin(int v, int n) {
		StringBuilder sb = new StringBuilder();
		for(int i = 0; i < n; i++) {
			if(((v >> i) & 1) == 1) {
				sb.append('1');
			} else {
				sb.append('0');
			}
		}
		return sb.reverse().toString();
	}

	static void greedy(int n, int[] P) {
		int[] code = new int[1 << n];
		boolean[] used = new boolean[1 << n];
		used[0] = true;
		for(int i = 1; i < code.length; i++) {
			boolean found = false;
			for(int p : P) {
				int cur = (1 << p) - 1;
				while(cur < (1 << n)) {
					int candidate = code[i - 1] ^ cur;
					if(!used[candidate]) {
						code[i] = candidate;
						used[candidate] = true;
						found = true;
					}
					cur = next(cur);
					if(found) break;
				}
				if(found) break;
			}
			if(!found) {
				System.out.println("impossible");
				System.exit(0);
			}
		}
		StringBuilder sb = new StringBuilder();
		for(int i = 0; i < code.length; i++) {
			sb.append(bin(code[i], n) + '\n');
		}
		System.out.print(sb.toString());
	}

}

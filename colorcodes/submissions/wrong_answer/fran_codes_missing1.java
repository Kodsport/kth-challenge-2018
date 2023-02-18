import java.util.BitSet;
import java.util.LinkedList;
import java.util.Scanner;

public class fran_codes_missing1 {

	static boolean debug = false;

	public static void main(String[] args) {
		Scanner reader = new Scanner(System.in);
		int n = reader.nextInt();
		int k = reader.nextInt();
		int minOdd = Integer.MAX_VALUE;
		LinkedList<Integer> P = new LinkedList<>();
		for(int i = 0; i < k; i++) {
			int p = reader.nextInt();
			if(p % 2 == 1) minOdd = Math.min(minOdd, p);
			else P.add(p);
		}
		if(minOdd == Integer.MAX_VALUE) {
			System.out.println("impossible");
		} else {
			P.add(minOdd);
			if(P.size() == 1 && P.getFirst() == n) {
				System.out.println("impossible");		
			} else {
				greedy(n, P);				
			}
		}
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

	static boolean check(int[] code, int n, int[] P) {
		BitSet S = new BitSet();
		for(int p : P) S.set(p);
		for(int i = 1; i < code.length; i++) {
			if(!S.get(Integer.bitCount(code[i - 1] ^ code[i]))) {
				return false;
			}
		}
		S = new BitSet();
		for(int c : code) S.set(c);
		return S.cardinality() == (1 << n);
	}

	static void greedy(int n, LinkedList<Integer> P) {
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
						break;
					}
					cur = next(cur);
				}
				if(found) break;
			}
		}
		StringBuilder sb = new StringBuilder();
		for(int i = 0; i < code.length; i++) {
			sb.append(bin(code[i], n) + '\n');
		}
		System.out.print(sb.toString());

	}


	static void greedy(int n, int[] P) {
		int[] code = new int[1 << n];
		boolean[] used = new boolean[1 << n];
		used[0] = true;
		for(int i = 1; i < code.length; i++) {
			if(debug) {
				for(int j = 0; j < i; j++) {
					System.out.print(Integer.toBinaryString(code[j]) + " ");
				}
				System.out.println();
			}
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
			if(debug && !found) {
				System.out.println("not found");
			}
		}
		System.out.println(check(code, n, P));
		StringBuilder sb = new StringBuilder();
		for(int i = 0; i < code.length; i++) {
			sb.append(bin(code[i], n) + '\n');
		}
		System.out.print(sb.toString());
	}

}

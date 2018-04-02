import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class InverseBWT {
    class FastScanner {
        StringTokenizer tok = new StringTokenizer("");
        BufferedReader in;

        FastScanner() {
            in = new BufferedReader(new InputStreamReader(System.in));
        }

        String next() throws IOException {
            while (!tok.hasMoreElements())
                tok = new StringTokenizer(in.readLine());
            return tok.nextToken();
        }

        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
    }

    private void PreprocessBWT(String bwt, Map<Character, Integer> starts, Map<Character, int[]> occ_counts_before) {
        // Implement this function yourself
	char[] bwt_arr = bwt.toCharArray();
	Arrays.sort(bwt_arr);
	String first = new String(bwt_arr);

	int startIndex = 1;

	starts.put('$',0);

	for (int i = 1; i < first.length(); i++) {
		if (first.charAt(i) != first.charAt(i-1))
			starts.put(first.charAt(i),i);
	}

	int[] pos = new int[bwt.length()];

	occ_counts_before.put('A',pos);
	occ_counts_before.put('C',pos);
	occ_counts_before.put('G',pos);
	occ_counts_before.put('T',pos);

	Map<Character, Integer> occ_counts = new HashMap<>();

	occ_counts.put('A',0);
	occ_counts.put('C',0);
	occ_counts.put('G',0);
	occ_counts.put('T',0);

	for (int i = 0; i < bwt.length(); i++) {
		if (bwt.charAt(i) == '$')
			continue;
		int prev_count = occ_counts.get(bwt.charAt(i));

		int[] temp = occ_counts_before.get(bwt.charAt(i));
		temp[i] = prev_count+1;
		occ_counts_before.put(bwt.charAt(i), temp);
		occ_counts.put(bwt.charAt(i), prev_count+1);
	}
    }


    String inverseBWT(String bwt) {
        StringBuilder result = new StringBuilder();
        // write your code here
	char[] bwt_arr = bwt.toCharArray();
	Arrays.sort(bwt_arr);
	String first = new String(bwt_arr);

	result.append('$');

	Map<Character, Integer> starts = new HashMap<>();
	Map<Character, int[]> occ_counts_before = new HashMap<>();

	PreprocessBWT(bwt, starts, occ_counts_before);

	int next_index = 0;

	while (bwt.charAt(next_index) != '$') {
		result.append(bwt.charAt(next_index));
		int[] pos_arr = occ_counts_before.get(bwt.charAt(next_index));
		next_index = starts.get(bwt.charAt(next_index))+pos_arr[next_index]-1;
	}

        return result.reverse().toString();
    }

    static public void main(String[] args) throws IOException {
        new InverseBWT().run();
    }

    public void run() throws IOException {
        FastScanner scanner = new FastScanner();
        String bwt = scanner.next();
        System.out.println(inverseBWT(bwt));
    }
}

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class BWMatching {
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

    // Preprocess the Burrows-Wheeler Transform bwt of some text
    // and compute as a result:
    //   * starts - for each character C in bwt, starts[C] is the first position
    //       of this character in the sorted array of
    //       all characters of the text.
    //   * occ_count_before - for each character C in bwt and each position P in bwt,
    //       occ_count_before[C][P] is the number of occurrences of character C in bwt
    //       from position 0 to position P inclusive.
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

    // Compute the number of occurrences of string pattern in the text
    // given only Burrows-Wheeler Transform bwt of the text and additional
    // information we get from the preprocessing stage - starts and occ_counts_before.
    int CountOccurrences(String pattern, String bwt, Map<Character, Integer> starts, Map<Character, int[]> occ_counts_before) {
        // Implement this function yourself
	int top = 0;
	int bottom = bwt.length()-1;
	int patternIndex = pattern.length()-1;

	while (top < bottom) {
		if (patternIndex >= 0) {
			char symbol = pattern.charAt(patternIndex);
			int[] pos_arr = occ_counts_before.get(symbol);

			int topIndex = -1;
			int bottomIndex = -1;

			for (int j = top; j <= bottom; j++) {
				if (bwt.charAt(j) == symbol) {
					topIndex = j;
					break;
				}
			}

			for (int j = bottom; j >= top; j--) {
				if (bwt.charAt(j) == symbol) {
					bottomIndex = j;
					break;
				}
			}
			
			if (topIndex == -1)
				return 0;
	
			//System.out.println("topIndex:"+topIndex);
			//System.out.println("bottomIndex:"+bottomIndex);

			top = starts.get(symbol)+pos_arr[topIndex]-1;
			bottom = starts.get(symbol)+pos_arr[bottomIndex]-1;

			//System.out.println("top:"+top);
			//System.out.println("bottom:"+bottom);
		} else {
			return bottom-top+1;
		}			
		patternIndex--;
	}

	return 0;
    }

    static public void main(String[] args) throws IOException {
        new BWMatching().run();
    }

    public void print(int[] x) {
        for (int a : x) {
            System.out.print(a + " ");
        }
        System.out.println();
    }

    public void run() throws IOException {
        FastScanner scanner = new FastScanner();
        String bwt = scanner.next();
        // Start of each character in the sorted list of characters of bwt,
        // see the description in the comment about function PreprocessBWT
        Map<Character, Integer> starts = new HashMap<Character, Integer>();
        // Occurrence counts for each character and each position in bwt,
        // see the description in the comment about function PreprocessBWT
        Map<Character, int[]> occ_counts_before = new HashMap<Character, int[]>();
        // Preprocess the BWT once to get starts and occ_count_before.
        // For each pattern, we will then use these precomputed values and
        // spend only O(|pattern|) to find all occurrences of the pattern
        // in the text instead of O(|pattern| + |text|).
        PreprocessBWT(bwt, starts, occ_counts_before);
        int patternCount = scanner.nextInt();
        String[] patterns = new String[patternCount];
        int[] result = new int[patternCount];
        for (int i = 0; i < patternCount; ++i) {
            patterns[i] = scanner.next();
            result[i] = CountOccurrences(patterns[i], bwt, starts, occ_counts_before);
        }
        print(result);
    }
}

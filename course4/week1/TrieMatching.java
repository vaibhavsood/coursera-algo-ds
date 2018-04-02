import java.io.*;
import java.util.*;

class Node
{
	public static final int Letters =  4;
	public static final int NA      = -1;
	public int next [];

	Node ()
	{
		next = new int [Letters];
		Arrays.fill (next, NA);
	}
}

public class TrieMatching implements Runnable {
	int letterToIndex (char letter)
	{
		switch (letter)
		{
			case 'A': return 0;
			case 'C': return 1;
			case 'G': return 2;
			case 'T': return 3;
			default: assert (false); return Node.NA;
		}
	}

	List<Map<Character, Integer>> buildTrie(List <String> patterns) {
		List<Map<Character, Integer>> trie = new ArrayList<Map<Character, Integer>>();
		// write your code here
		trie.add(new HashMap<Character, Integer>());
		int node_count = 0;
		for (int i = 0; i < patterns.size(); i++) {
			String pattern = patterns.get(i);
			int curr_node = 0;
			for (int j = 0; j < pattern.length(); j++) {
				Map<Character, Integer> m = trie.get(curr_node);
				if (m.get(pattern.charAt(j)) == null) {
					trie.add(new HashMap<Character, Integer>());
					m.put(pattern.charAt(j), ++node_count);
					curr_node = node_count;
				} else {
					curr_node = m.get(pattern.charAt(j));	
				}	
			}
		} 

		return trie;
	}

    public void print(List<Map<Character, Integer>> trie) {
        for (int i = 0; i < trie.size(); ++i) {
            Map<Character, Integer> node = trie.get(i);
            for (Map.Entry<Character, Integer> entry : node.entrySet()) {
                System.out.println(i + "->" + entry.getValue() + ":" + entry.getKey());
            }
        }
    }

	List <Integer> solve (String text, int n, List <String> patterns) {
		List <Integer> result = new ArrayList <Integer> ();
		// write your code here
		List<Map<Character, Integer>> trie = buildTrie(patterns);
		//print(trie);		
		int curr_index = 0;

		for (int i = 0; i < text.length(); i++) {
			int curr_node = 0;
			curr_index = i;
			int j = 0;

			for (j = i; j < text.length(); j++) {
				Map<Character, Integer> m = trie.get(curr_node);
				if (m.size() == 0) {
					result.add(curr_index);
					break;
				} else if (m.get(text.charAt(j)) == null) {
					break;	
				} else {
					curr_node = m.get(text.charAt(j));	
				}	
			}
			
			if (j == text.length()) {
				Map<Character, Integer> m = trie.get(curr_node);
				if (m.size() == 0) {
					result.add(curr_index);
				}
			}
		}

		return result;
	}

	public void run () {
		try {
			BufferedReader in = new BufferedReader (new InputStreamReader (System.in));
			String text = in.readLine ();
		 	int n = Integer.parseInt (in.readLine ());
		 	List <String> patterns = new ArrayList <String> ();
			for (int i = 0; i < n; i++) {
				patterns.add (in.readLine ());
			}

			List <Integer> ans = solve (text, n, patterns);

			for (int j = 0; j < ans.size (); j++) {
				System.out.print ("" + ans.get (j));
				System.out.print (j + 1 < ans.size () ? " " : "\n");
			}
		}
		catch (Throwable e) {
			e.printStackTrace ();
			System.exit (1);
		}
	}

	public static void main (String [] args) {
		new Thread (new TrieMatching ()).start ();
	}
}

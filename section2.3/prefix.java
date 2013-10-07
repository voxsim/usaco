/*
SECTION: 2.3
NUMBER: 1
ID: voxsim2
PROG: prefix
LANG: JAVA
 */
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedList;

public class prefix {
	private HashMap<Character, Node> nodes;
	private int maxP;

	public class Node {
		private char primitive;
		private boolean end;
		private HashMap<Character, Node> children;

		public Node(char primitive, boolean end) {
			this.primitive = primitive;
			this.end = end;
			this.children = new HashMap<Character, Node>();
		}

		public char getPrimitive() {
			return primitive;
		}

		public boolean isEnd() {
			return end;
		}

		public void setEnd(boolean end) {
			this.end = end;
		}

		public Node addChild(Node child) {
			if (this.children.get(child.getPrimitive()) == null) {
				this.children.put(child.getPrimitive(), child);
			}
			
			return this.children.get(child.getPrimitive());
		}

		public Node getNode(char letter) {
			return this.children.get(letter);
		}

		public String toString() {
			return "{" + primitive + "," + end + ",[" + children + "]}";
		}
	}

	public prefix() {
		nodes = new HashMap<Character, Node>();
		maxP = 0;
	}

	public void fillNodes(String primitive) {
		Node oldNode = null;
		for (int i = 0; i < primitive.length(); i++) {
			char letter = primitive.charAt(primitive.length() - i - 1);
			Node node = new Node(letter, false);
			if (i == 0) {
				if (nodes.get(letter) == null) {
					nodes.put(letter, node);
					oldNode = node;
				} else {
					oldNode = nodes.get(letter);
				}
			} else {
				node = oldNode.addChild(node);
				oldNode = node;
			}
		}
		oldNode.setEnd(true);
	}

	public int solve(String[] primitives, String sequence) {
		int[] result = new int[sequence.length() + 1];

		for (String primitive : primitives) {
			fillNodes(primitive);

			if (primitive.length() > maxP)
				maxP = primitive.length();
		}

		int loose = 0;
		int end = -1;

		LinkedList<Character> buffer = new LinkedList<Character>();
		for (int i = 0; i < maxP; i++) {
			buffer.add(null);
		}

		for (int i = 0; i < sequence.length() && end == -1; i++) { // S
			char letter = sequence.charAt(i);
			
			buffer.removeFirst();
			buffer.add(letter);
			
			Node oldNode = null;
			int maxGain = 0;
			int bestChoose = 0;
			for (int j = 0; j < i + 1 && j < maxP; j++) {
				// ("buffer letter: "+buffer.get(maxP-j-1));
				if (j == 0) {
					oldNode = nodes.get(buffer.get(maxP - j - 1));
				} else {
					if (oldNode != null) {
						oldNode = oldNode.getNode(buffer.get(maxP - j - 1));
					} else {
						break;
					}
				}

				if (oldNode != null) {
					bestChoose = j;
					int gain = result[i - j] + (oldNode.isEnd() ? j + 1 : 0);
					if (gain > maxGain) {
						maxGain = gain;
					}
				}
			}
			result[i + 1] = maxGain;
//			("a letter: " + letter + " " + maxGain + " " + i + " " + persi + " " + bestChoose);
			if (result[i + 1] - result[i] == 0) {
				loose += 1;
			} else {
				if (loose <= bestChoose)
					loose = 0;
				else
					end = i - bestChoose;
			}
		}

		if (end == -1)
			end = sequence.length();

		return result[end];
	}

	public static void main(String[] args) throws Exception {
		long timeInMillis0 = System.currentTimeMillis();
		
		BufferedReader brIn = new BufferedReader(new FileReader(new File(
				"prefix.in")));

		String line = null;
		StringBuffer text = new StringBuffer();

		do {
			line = brIn.readLine();
			if (line != null) {
				text.append(" ");
				text.append(line);
			}
		} while (line != null);
		brIn.close();
		
		long timeInMillis1 = System.currentTimeMillis();

		String[] first = text.toString().split("\\.");
		String[] primitives = first[0].trim().split(" ");
		String sequence = first[1].trim().replace(" ", "");

		System.out.println("primitives: " + Arrays.toString(primitives));
		System.out.println("sequence: " + sequence + " " + sequence.length());
		
		long timeInMillis2 = System.currentTimeMillis();

		prefix main = new prefix();
		int result = main.solve(primitives, sequence);
		
		long timeInMillis3 = System.currentTimeMillis();
		
		System.out.println("time: " + (timeInMillis1 - timeInMillis0));
		System.out.println("time: " + (timeInMillis2 - timeInMillis1));
		System.out.println("time: " + (timeInMillis3 - timeInMillis2));
		
		BufferedWriter brOut = new BufferedWriter(new FileWriter(new File(
				"prefix.out")));
		brOut.write(String.valueOf(result) + "\n");
		brOut.close();
	}
}

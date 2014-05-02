/*
SECTION: 2.4
NUMBER: 4
ID: voxsim2
PROG: comehome
LANG: JAVA 
*/
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;
import java.util.ArrayList;
import java.util.Date;
import java.util.Scanner;

public class comehome {
	
	public static void main(String[] args) throws IOException {
		
		Date date0 = new Date();
		
		ArrayList<String> labels = new ArrayList<String>();
		
		int INFINITY = 100000;
		int dist[][] = new int[52][52];
		
		for(int k=0; k<52; k++) {
			for(int j=0; j<52; j++) {
				dist[k][j] = INFINITY;
			}
		}
		
		Scanner input = new Scanner(new File("comehome.in"));
		Writer output = new FileWriter("comehome.out");
		 
		int P = input.nextInt();
		
//		System.out.println("input.next: "+input.next("([^\\s]+)"));
		 
//		input.nextLine();
		
		int barn = 0;
		 
		for(int i=0; i<P; i++) {
//			 String[] line = input.nextLine().split(" ");
//			 if(line.length >= 3) {
				 String a = input.next("([^\\s]+)"); //line[0];
				 String b = input.next("([^\\s]+)"); //line[1];
				 int w = Integer.parseInt(input.next("([^\\s]+)")); //line[2]);
				 
				 if(!labels.contains(a)) {
					 labels.add(a);
					 
					 if(a.equals("Z")) {
						 barn = labels.indexOf(a);
					 }
				 }
				 
				 if(!labels.contains(b)) {
					 labels.add(b);
					 
					 if(b.equals("Z")) {
						 barn = labels.indexOf(b);
					 }
				 }
				 
				 if(a.equals(b))
					 continue;
					 
				 if(w < dist[labels.indexOf(a)][labels.indexOf(b)]) {
					 dist[labels.indexOf(a)][labels.indexOf(b)] = w;
					 dist[labels.indexOf(b)][labels.indexOf(a)] = w;
				 }
//			 }
		}
		
//		System.out.println(labels);
//		System.out.println(barn);
		
		for(int k=0; k<labels.size(); k++) {
			for(int j=0; j<labels.size(); j++) {
				for(int i=0; i<labels.size(); i++) {
					if(k == j || j == i || i == k) 
						continue;
					
					int new_dist = dist[i][k] + dist[k][j];
//					System.out.println(labels.get(i)+" "+labels.get(k)+" "+labels.get(j)+" "+dist[i][k]+" "+dist[k][j]+" "+new_dist+" "+dist[i][j]);
					if(new_dist < dist[i][j]) {
						dist[i][j] = new_dist;
					}
				}
			}
		}
		
		int winner = -1;
		
		for(int k=0; k<labels.size(); k++) {
//			System.out.println(labels.get(k)+" "+labels.get(barn)+" "+dist[k][barn]);
			if(labels.get(k).toUpperCase().equals(labels.get(k)) && winner == -1) {
				winner = k;
			} else if(labels.get(k).toUpperCase().equals(labels.get(k)) && dist[k][barn] < dist[winner][barn]) {
				winner = k;
			}
		}
		
//		System.out.println("winner: "+winner);
		output.write(labels.get(winner)+" "+dist[winner][barn]+"\n");
		
		input.close();
		output.close();
		
		Date date1 = new Date();
		System.out.println("runtime: "+(date1.getTime() - date0.getTime()));
	}
}

import static java.lang.Math.*;

public class Shapely {
	
	private

	int n; 			// Number of players
	int m; 			// Number of coalitions
	int p[];	// hashes for players p[i] = 2^i

	int v[];	// value for coalition
	float sh[];	// shapely value for the grand coalition for a player 
	
	boolean coalitionHasPlayer(int coalition,int i){
		return 0<(p[i] & coalition);
	}
	
	int coalitionSize (int coalition) {
	    int count = 0;
	    while (coalition > 0) {           // until all bits are zero
	        if ((coalition & 1) == 1)     // check lower bit
	            count++;
	        coalition >>= 1;              // shift bits, removing lower bit
	    }
	    return count;
	}
	
	public Shapely(int numPlayers, int[] val) {
		n=numPlayers;
		m=1<<numPlayers;
		// Populate hashes for each player
		p=new int[n];
		for(int i=0;i<n;++i){
			p[i]=1<<i;
		}
		// Populate values for each coalition
		v=new int[m];
		for(int j=0;j<m;++j){
			v[j]=val[j];
		}
		// Populate Shapely-s for each player
		sh=new float[n];
		for(int i=0;i<n;++i){
			sh[i]=-1;
		}

	}
	
	public void printPlayers(){
		for(int i=0;i<n;++i){
			System.out.print("Player "+i+" #"); 
			System.out.println(p[i]); 
		}
	}
	public void printCoalition(int j){
		System.out.print("#"+j+" Players ");
		for(int i=0;i<n;++i){
			if(coalitionHasPlayer(j,i)){
				System.out.print(i+" "); 
			}
		}
		System.out.print(": ");
		System.out.println(v[j]); 
	}
	public void printGame(){
		for(int s=0;s<=n;++s){
			System.out.println("Size "+s+":");
			for(int j=0;j<m;++j){
				if(coalitionSize(j)==s)
					printCoalition(j);
			}
		}
		
	}
	
	/**
	 * φi(N,v) = 1/N! ∑_{S ⊆N \{i}} { |S|!(|N| − |S| − 1)! v(S ∪ {i}) − v(S) }
	 * @param i Player
	 */
	void getShapely(int i){
		int r=sh[i];
		if(r<0)
			calculateShapelyForPlayer(i)
	}
	
	void calculateShapelyForPlayer(int i){
		int diff;
		int s;
		float numerator=0;
		int numerator2=0;
		int denominator=Factorial.getFactorial(n);
		for(int j=0;j<m;++j){
			if( coalitionHasPlayer(j, i) ) continue;
			s = coalitionSize(j);
			diff = v[j|p[i]] - v[j];
			numerator += Factorial.getFactorial(s) * Factorial.getFactorial(n-s-1) * diff;
			numerator2 += Factorial.getFactorial(s) * Factorial.getFactorial(n-s-1) * 1;
		}
		System.out.println("Numerator_ "+numerator2+" Denominator "+denominator);
		System.out.println("Shapely "+numerator/denominator);
		sh[i]=numerator/denominator;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		int[] val={0, 0, 0, 100};
		Shapely s= new Shapely(2, val);
		s.printGame();
		

		int[] val3={0, 0, 0, 100, 0, 100, 100, 100};
		Shapely s3= new Shapely(3, val3);

	}

}

import static java.lang.Math.*;

public class Shapely { 
	
	private

	int n; 			// Number of players
	int m; 			// Number of coalitions
	int p[];		// hashes for players p[i] = 2^i

	int v[];		// value for coalition
	float sh[];		// shapely value for the grand coalition for a player 
	float sh2[][];	// shapely value for a coalition for a player 

	public static final boolean DEBUG = false;

	
	/*
	 * COALITION UTILITY FUNCTIONS
	 */
	
	boolean coalitionHasPlayer(int coalition,int i){
		return 0<(p[i] & coalition);
	}
	int coalitionSize (int j) {
	    int count = 0;
	    while (j > 0) {           // until all bits are zero
	        if ((j & 1) == 1)     // check lower bit
	            count++;
	        j >>= 1;              // shift bits, removing lower bit
	    }
	    return count;
	}
	/** 
	 * c1 is a subset of c2
	 * @param c1
	 * @param c2
	 * @return boolean true if c1 is a subset of c2
	 */
	boolean coalitionIsSubsetOf (int c1, int c2) {
		return c2==(c1|c2);
	}
	
	/**
	 * Constructor
	 * @param numPlayers number of players
	 * @param val value function for each subset of players
	 */
	public Shapely(int numPlayers, int[] val) {
		n=numPlayers;
		m=1<<numPlayers;

		// Populate hashes for each player
		p=new int[n];
		for(int i=0;i<n;++i)
			p[i]=1<<i;

		// Populate values for each coalition
		v=new int[m];
		for(int j=0;j<m;++j)
			v[j]=val[j];

		// Populate null Shapely-s for each player
		sh=new float[n];
		for(int i=0;i<n;++i)
			sh[i]=-1;

		// Populate null Shapely-s for each coalition,player
		sh2=new float[m][n];
		for(int j=0;j<m;++j)
			for(int i=0;i<n;++i)
				sh2[j][i]=-1;
	}
	
	/*
	 * PRINTING UTILITY FUNCTIONS
	 */
	
	public void printAllPlayers(){
		for(int i=0;i<n;++i){
			printPlayer(i);
			System.out.println(); 
		}
	}
	public void printPlayer(int i){
			System.out.print("Player "+i +" : "+ (i) +" (#"+p[i]+")");
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
		System.out.println("All Players:");
		printAllPlayers();
		System.out.println();
		System.out.println("Value function:");
		for(int j=0;j<m;++j)
			System.out.print(v[j]+" ");
		System.out.println();		
		for(int s=0;s<=n;++s){
			System.out.println("Coalitions of Size "+s+":");
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
	float getShapely(int i){
		float r=sh[i];
		if(r<0){
			calculateShapelyForPlayer(i);
			r=sh[i];
		}
		return r;
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

	float getShapelyForCoalitionPlayer(int j, int i){
		float r=sh2[j][i];
		if(r<0){
			calculateShapelyForCoalitionPlayer(j,i);
			r=sh2[j][i];
		}
		return r;
	}

	void printShapelyForCoalition(int j){
		printCoalition(j);
		for(int i=0;i<n;++i){
			if(coalitionHasPlayer(j, i)){
				printPlayer(i);
				System.out.println(getShapelyForCoalitionPlayer(j, i));
			}
		}
	}

	void calculateShapelyForCoalitionPlayer(int coalitionId,int playerId){
		int diff;	// differential variable
		int s;		// coalition size variable
		final int N=coalitionSize(coalitionId);	// size of this coalition 
		float numerator=0;
		int numerator2=0;
		int denominator=Factorial.getFactorial(N);
		for(int j=0;j<m;++j){	// For each coalition
			if( coalitionHasPlayer(j, playerId) ) continue;				// Don't consider coalitions with player i 
			if( !coalitionIsSubsetOf(j, coalitionId) ) continue;		// Consider only coalitions that are subsets
			s = coalitionSize(j);
			diff = v[j|p[playerId]] - v[j];
			numerator += Factorial.getFactorial(s) * Factorial.getFactorial(N-s-1) * diff;
			numerator2 += Factorial.getFactorial(s) * Factorial.getFactorial(N-s-1) * 1;
		}
		if(DEBUG){
			System.out.println("Numerator_ "+numerator2+" Denominator "+denominator);
			System.out.println("Shapely "+numerator/denominator);
		}
		sh2[coalitionId][playerId]=numerator/denominator;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {

		//			0	A	B	AB		C	AC		BC	ABC		D	AD		BD	ABD		CD	ACD		BCD		ABCD
		int[] val3={0,	0,	0,	100,	0,	100,	0,	100};
		int[] val4={0,	0,	0,	100,	0,	100,	0,	100,	0,	100,	0,	100,	0,	100,	100,	100};
		Shapely s3= new Shapely(4, val4);
		s3.printGame();
		
		for(int j=0;j<s3.m;++j){
			System.out.println();
			s3.printShapelyForCoalition(j);
		}

//		System.out.println();
//		s3.printShapelyForCoalition(7);
//
//		System.out.println();
//		s3.printShapelyForCoalition(11);
//		
//		System.out.println();
//		s3.printShapelyForCoalition(13);
//		
//		System.out.println();
//		s3.printShapelyForCoalition(14);
//		
//		System.out.println();
//		s3.printShapelyForCoalition(15);

	}

}

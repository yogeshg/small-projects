public class Grandeville {
	
	private int SIZE=11;
	private int I=1+2*SIZE;
	private int J=1+2*SIZE;
	private int K=SIZE;
	private double corners[][][] = new double[I][J][K];
	
	public double max(double a,double b){
		return a>b?a:b;
	}
	public double mod(double a){
		return a>0?a:-a;
	}
		
	public Grandeville(){
		for(int i=0;i<I;++i)
			for(int j=0;j<J;++j)
				corners[i][j][0]=0;
		corners[SIZE][SIZE][0]=1;
		
		for(int k=1;k<K;++k)
			for(int i=0;i<I;++i)
				for(int j=0;j<J;++j)
					corners[i][j][k]=(double)-0.00001;
	}
	
	// st in -SIZE to SIZE -> i in 0 to 2*SIZE -> s*SIZE+1 elements
	public double getCorner(int st,int av,int tm){
		int i=st+SIZE;
		int j=av+SIZE;
		int k=tm;
		double c;
		
		if(i>=0 && i<I && j>=0 && j<J && k>=0 && k<K){
			c = corners[i][j][k];
			if(c<0){
				c=((double) 0.25)*(
						 getCorner(st-1,av,tm-1)
						+getCorner(st+1,av,tm-1)
						+getCorner(st,av-1,tm-1)
						+getCorner(st,av+1,tm-1)
						);
				corners[i][j][k]=c;
				return c;
			}
			else
				return c;														// If Pre computed
			
		} else
			return 0;															// Probability is 0 otherwise
	}
	
	public void print(){
		double p=0;
		for(int k=0;k<K;++k){
			p=0;
			for(int i=0;i<I;++i){
				for(int j=0;j<J;++j){
					System.out.print(corners[i][j][k]);
					p+=max(corners[i][j][k],(double)0);
					System.out.print("\t");
				}
				System.out.println();
			}
			System.out.println("###");
			System.out.println("P("+k+")="+p);
			System.out.println("###");
		}
	}
	
	// atleast x blocks away at tm time
	public double q1(int x,int tm){
		double p=0;
		for(int av=-SIZE;av<=SIZE;++av){
			for(int st=-SIZE;st<=SIZE;++st){
				if(mod(av)+mod(st)<x){
					System.err.println("("+av+","+st+")@"+tm);
					p+=this.getCorner(av,st,tm);
				}
			}
			
		}
		return 1-p;
	}
	public double q1_2(int x,int tm){
		double p=0;
		for(int av=-SIZE;av<=SIZE;++av){
			for(int st=-SIZE;st<=SIZE;++st){
				if(mod(av)+mod(st)>=x){
					System.err.println("("+av+","+st+")@"+tm);
					p+=this.getCorner(av,st,tm);
				}
			}
			
		}
		return p;
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("Hello World!!!");
		Grandeville gv= new Grandeville();

		System.out.println("q1: P="+gv.q1(3, 10));
		System.out.println("q1_2: P="+gv.q1_2(3, 10));
		gv.print();
		
	}

}
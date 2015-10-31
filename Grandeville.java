import static java.lang.Math.*;

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
	public double manhattanDist(double st,double av){
		return mod(st)+mod(av);
	}
	public double crowDist(double st,double av){
//		return max(mod(st),mod(av));
		return Math.sqrt(st*st + av*av);
	}
	public String locstr(double st,double av,double tm){
		return "("+st+","+av+")@"+tm;
	}
		
	public Grandeville(){
		this.init();
	}
	public void init(){
		for(int i=0;i<I;++i)
			for(int j=0;j<J;++j)
				corners[i][j][0]=0;
		corners[SIZE][SIZE][0]=1;
		
		for(int k=1;k<K;++k)
			for(int i=0;i<I;++i)
				for(int j=0;j<J;++j)
					corners[i][j][k]=(double)-0.0001;
	}
	
	public void setCorner(int st,int av,int tm,double v){
		corners[st+SIZE][av+SIZE][tm]=v;
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
			
		} else {
//			System.err.println("Attempt to access("+st+","+av+")@"+tm);
			return 0;															// Probability is 0 otherwise			
		}
	}
	
	public void print(){
		double p=0;
		for(int k=0;k<K;++k){
			p=0;
			for(int i=0;i<I;++i){
				for(int j=0;j<J;++j){
//					System.out.print(corners[i][j][k]>=0?corners[i][j][k]:" ");
					p+=max(corners[i][j][k],(double)0);
//					System.out.print("\t");
				}
//				System.out.println();
			}
//			System.out.println("###");
//			System.out.println("P("+k+")="+p);
//			System.out.println("###");
		}
	}
	
	// atleast x blocks away at tm time
	public double q1(int x,int tm){
		double p=0;
		for(int st=-SIZE;st<=SIZE;++st){
			for(int av=-SIZE;av<=SIZE;++av){
				if(crowDist(st,av)<x){
//					System.err.println("("+st+","+av+")@"+tm);
					p+=this.getCorner(st,av,tm);
				}
			}
			
		}
		return 1-p;
	}
	public void clearAfterBlocks(int x,int tm){
		for(int st=-SIZE;st<=SIZE;++st){
			for(int av=-SIZE;av<=SIZE;++av){
				if(crowDist(st,av)>=x){
					this.setCorner(st, av, tm,0);
//					System.err.println("Clearing"+locstr(st,av,tm));
				}
			}
		}
	}
	// atleast x within tm moves
	public double q2(int x,int tm){
		double p=0;
		for(int t=1;t<=tm;++t){
			p+=q1(x,t);
			System.err.println("p_"+t+"="+p);
			this.clearAfterBlocks(x,t);
		}
		this.print();
		return p;
	}

	public double q3(int tm){
		double p=0;
		double q=0;
		int st;
		int av;
		for(int t=1;t<=tm;++t){
			this.init();
			q=0;
			for(st=-SIZE;st<=SIZE;++st) {
				for(av=-SIZE;av<=SIZE;++av) {
					if(-1==av){
						q+=this.getCorner(st, av, t);
					} else {
						this.setCorner(st, av, t, 0);
					}
				}
			}
			System.err.println("q_"+t+"="+q);
			q=0;
			for(st=-SIZE;st<=SIZE;++st) {
				for(av=1;av<=SIZE;++av) {
					q+=this.getCorner(st, av, tm);
				}
			}
			System.err.println("q_"+t+"="+q);
			p+=q;
			
			this.print();
//			System.out.println("step "+t);
//			System.out.println("####");

		}
		return p;
	}
	
	public static void main(String[] args) {
		System.out.println("Hello World!!!");
		Grandeville gv= new Grandeville();

		System.out.println("q1: P="+gv.q1(3, 10));

		System.out.println("q2: P="+gv.q2(5, 10));
		
		System.out.println("q3: P="+gv.q3(10));
		
		
	}

}
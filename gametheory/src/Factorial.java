
public class Factorial {
	static final int INIT=8;
	static int num=INIT;
	static int v[];

	static {
		v=new int[INIT];
		v[0]=1;
	}
	
	static int getFactorial(int n){
		int r=-1;
		if(n>num)
			return r;
		r=v[n];
		if(r<=0) {
			// Tail recursion?
			return r=v[n]=n*getFactorial(n-1);
		}
		return r;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println (Factorial.getFactorial(0));
		System.out.println (Factorial.getFactorial(10));
		System.out.println (Factorial.getFactorial(4));
		System.out.println (Factorial.getFactorial(5));
		System.out.println (Factorial.getFactorial(1));

		
	}

}

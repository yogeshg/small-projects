import java.util.Stack;

public class Printer {
	
	private class Context {
		String start;
		String end;
		String indent;
		public Context(String s,String e,String i){
			start=s;
			end=e;
			indent=i;
		}
		public Context(int n,String c){
			indent=end=start="";
			String indentchar=" ";
			for(;n>0;--n){
				indent+=c;
			}
		}
	}

	private Stack<Context> contexts;
	private final Context DEFAULTCONTEXT=new Context(0," ");
	
	public Printer(){
		contexts = new Stack<Context>();
		contexts.push(DEFAULTCONTEXT);
	}
	
	public void println(Object o){
		System.out.print(contexts.peek().indent);
		System.out.println(o);
	}
	
	public void indent(){
		contexts.push(new Context(1+contexts.peek().indent.length()," ") );
		System.out.println(contexts.peek().start);
	}
	public void dindent(){
		System.out.println(contexts.peek().end);
		contexts.pop();
	}
	public void h(int i,String s){
		String buff="";
		while(!contexts.empty()){
			contexts.pop();
		}
		contexts.push(DEFAULTCONTEXT);
		for(int idx=s.length();idx>0;--idx){
			buff+="-";
		}
		contexts.push(new Context("",buff,""));
		System.out.println(contexts.peek().start);
		System.out.print(contexts.peek().indent);
		System.out.println(s);
		System.out.println(contexts.peek().end);
		
		
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Printer p=new Printer();
		p.println("Ssup");
		p.h(1, "woot");
		p.indent();
		p.println("Ssup1");
		p.println("Ssup2");
		p.dindent();
		p.println("Ssup3");

	}

}

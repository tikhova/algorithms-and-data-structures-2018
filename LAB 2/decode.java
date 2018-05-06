import java.io.*;
import java.util.*;
import java.lang.*;
 
public class decode {
 
 
    public static void main(String[] args) {
        try {
            Scanner in = new Scanner(new File("decode.in"));
            FileWriter out = new FileWriter("decode.out");
            Stack<Character> d = new Stack<Character>();
            String s = in.nextLine();
            for (int i = 0; i < s.length(); i++) {
                if (!d.empty() && s.charAt(i) == d.peek()) {
                    d.pop();
                } else {
                    d.push(s.charAt(i));
                }
            }
            char[] a = new char[d.size()];
            for (int i = a.length - 1; i >= 0; i--) {
                a[i] = d.pop();
            }
            out.write(String.valueOf(a));
 
            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

import java.io.*;
import java.util.*;
import java.lang.*;
 
public class postfix {
 
 
    public static void main(String[] args) {
        try {
            Scanner in = new Scanner(new File("postfix.in"));
            FileWriter out = new FileWriter("postfix.out");
            Stack<Integer> d = new Stack<Integer>();
            String s = in.nextLine();
            for (int i = 0; i < s.length(); i++) {
                if (Character.isDigit(s.charAt(i))) {
                    d.push(s.charAt(i)-'0');
                } else {
                    switch (s.charAt(i)) {
                        case '+':
                            d.push(Integer.valueOf(d.pop()) + Integer.valueOf(d.pop()));
                            break;
                        case '-':
                            d.push(- Integer.valueOf(d.pop()) + Integer.valueOf(d.pop()));
                            break;
                        case '*':
                            d.push(Integer.valueOf(d.pop()) * Integer.valueOf(d.pop()));
                            break;
                    }
                }
            }
            out.write(String.valueOf(d.pop()));
 
 
            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

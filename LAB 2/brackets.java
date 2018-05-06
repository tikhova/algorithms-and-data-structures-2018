import java.io.;
import java.util.;
import java.lang.;
 
public class brackets {
 
 
    public static void main(String[] args) {
        try {
            Scanner in = new Scanner(new File(brackets.in));
            FileWriter out = new FileWriter(brackets.out);
            StackCharacter d = new StackCharacter();
            String s = in.nextLine();
            for (int i = 0; i  s.length(); i++) {
                if (!d.empty() && (s.charAt(i) == ')' && d.peek()=='('  s.charAt(i) == '}' && d.peek()=='{'
                     s.charAt(i) == ']' && d.peek()=='[')) {
                    d.pop();
                } else {
                    d.push(s.charAt(i));
                }
            }
            if (d.empty()) {
                out.write(YES);
            } else {
                out.write(NO);
            }
 
            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

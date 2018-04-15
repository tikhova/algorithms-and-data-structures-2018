import java.io.*;
import java.util.*;
import java.lang.*;

public class garland {


    public static void main(String[] args) {
        try {
            Scanner in = new Scanner(new File("garland.in"));
            FileWriter out = new FileWriter("garland.out");

            in.useLocale(new Locale("en_US"));

            int n;
            double a;
            n = in.nextInt();
            a = in.nextDouble();
            double[] g = new double[n];
            g[0] = a;
            double left = 0, right = a;
            double mid;
            boolean above = true;
            while (true) {
                mid = (left + right) / 2;
                if (left == mid || right == mid) {
                    break;
                }
                above = true;
                g[1] = mid;
                for (int i = 2; i < n; i++) {
                    g[i] = 2 * g[i - 1] + 2 - g[i - 2];
                    if (g[i] < 0) {
                        above = false;
                        break;
                    }
                }
                if (above) {
                    right = mid;
                } else {
                    left = mid;
                }
            }
            out.write(String.format("%.2f", g[n - 1]).replace(",", "."));
            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

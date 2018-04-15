import java.io.*;
import java.util.Scanner;

public class antiQS {
    public static void main(String[] args) {
        int n, k;
        Scanner in = new Scanner("");
        try {
            in = new Scanner(new File("antiqs.in"));
        } catch (IOException e) {
            e.printStackTrace();
        }

        n = in.nextInt();
        int[] a = new int[n];

        for (int i = 0; i < n; i++) {
            a[i] = i + 1;
            int t = a[i / 2];
            a[i / 2] = a[i];
            a[i] = t;
        }

        try {
            FileWriter out = new FileWriter("antiqs.out");
            for (int i = 0; i < n; i++) {
                out.write(String.valueOf(a[i]) + " ");
            }
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        in.close();
    }
}

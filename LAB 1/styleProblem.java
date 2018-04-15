import java.io.*;
import java.util.Scanner;
import java.lang.Integer;

public class styleProblem {
    public static void main(String[] args) {

        Scanner in = new Scanner("");
        try {
            in = new Scanner(new File("style.in"));
        } catch (IOException e) {
            e.printStackTrace();
        }

        int n = in.nextInt();
        int[] a = new int[n];

        for (int i = 0; i < n; i++) {
            a[i] = in.nextInt();
        }

        int k = in.nextInt();
        int[] b = new int[k];

        for (int i = 0; i < k; i++) {
            b[i] = in.nextInt();
        }

        int i = 0, j = 0, p = 0;
        int mini = 0, minj = 0, min = Integer.MAX_VALUE;
        while (i < n && j < k) {
            while (i < n && a[i] < b[j]) {
                i++;
            }
            if (i < n) {
                p = a[i] - b[j];
                if (p < 0) p *= -1;
                if (min > p) {
                    min = p;
                    mini = a[i];
                    minj = b[j];
                }
            }
            if (i > 0) {
                p = a[i - 1] - b[j];
                if (p < 0) p *= -1;
                if (min > p) {
                    min = p;
                    mini = a[i - 1];
                    minj = b[j];
                }
            }

            j++;
        }

        try {
            FileWriter out = new FileWriter("style.out");
            out.write(String.valueOf(mini) + " " + String.valueOf(minj));
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        in.close();
    }
}

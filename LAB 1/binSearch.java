import java.io.*;
import java.util.Scanner;

public class binSearch {

    public static int rightsideBS(int[] a, int key) {
        int l = -1;
        int r = a.length;
        int m;
        while (l < r - 1) {
            m = (l + r) / 2;
            if (a[m] <= key) {
                l = m;
            } else {
                r = m;
            }
        }
        return l;
    }

    public static int leftsideBS(int[] a, int key) {
        int l = -1;
        int r = a.length;
        int m;
        while (l < r - 1) {
            m = (l + r) / 2;
            if (a[m] >= key) {
                r = m;
            } else {
                l = m;
            }
        }
        return r;
    }

    public static void main(String[] args) {

        try {
            int n, k, l, r, key;
            Scanner in = new Scanner(new File("binsearch.in"));
            FileWriter out = new FileWriter("binsearch.out");

            n = in.nextInt();
            int[] a = new int[n];

            for (int i = 0; i < n; i++) {
                a[i] = in.nextInt();
            }

            k = in.nextInt();

            for (int i = 0; i < k; i++) {
                key = in.nextInt();
                l = leftsideBS(a, key);
                r = rightsideBS(a, key);
                if (l > -1 && l < n && a[l] == key) {
                    out.write(String.valueOf(l + 1) + " " + String.valueOf(r + 1) + "\r\n");
                } else {
                    out.write("-1 -1\r\n");
                }
            }

            out.close();
            in.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

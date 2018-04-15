import java.io.*;
import java.util.Scanner;

public class kth {
    public static int split(int[] a, int l, int r) {
        int i = l, j = r - 1, t;
        int key = a[(l + r) / 2];
        while (i <= j) {
            while (a[i] < key) {
                i++;
            }
            while (key < a[j]) {
                j--;
            }
            if (i <= j) {
                t = a[i];
                a[i] = a[j];
                a[j] = t;
                i++;
                j--;
            }
        }
        return j + 1;
    }

    public static int find(int[] a, int l, int r, int k) {
        int m = split(a, l, r);
        if (m == k) return a[m];
        if (k < m) {
            return find(a, l, m, k);
        } else {
            return find(a, m, r, k);
        }
    }

    public static void main(String[] args) {
        int n, k, a, b, c;
        Scanner in = new Scanner("");
        try {
            in = new Scanner(new File("kth.in"));
        } catch (IOException e) {
            e.printStackTrace();
        }

        n = in.nextInt();
        k = in.nextInt();
        a = in.nextInt();
        b = in.nextInt();
        c = in.nextInt();
        int[] m = new int[n];
        m[0] = in.nextInt();
        m[1] = in.nextInt();

        for (int i = 2; i < n; i++) {
            m[i] = a * m[i - 2] + b * m[i - 1] + c;
        }

        try {
            FileWriter out = new FileWriter("kth.out");
            out.write(String.valueOf(find(m, 0, n, k - 1)));
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        in.close();
    }
}

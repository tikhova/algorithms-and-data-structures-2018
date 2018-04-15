import java.io.*;
import java.util.Scanner;
import java.lang.Integer;

public class styleProblem2 {
    public static void quicksort(int[] a, int l, int r) {
        int i = l, j = r, t;
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
        if (l < j) quicksort(a, l, j);
        if (i < r) quicksort(a, i, r);
    }

    public static void main(String[] args) {

        Scanner in = new Scanner("");
        try {
            in = new Scanner(new File("style.in"));
        } catch (IOException e) {
            e.printStackTrace();
        }

        int[][] a = new int[4][];
        for (int i = 0; i < 4; i++) {
            a[i] = new int[in.nextInt()];

            for (int j = 0; j < a[i].length; j++) {
                a[i][j] = in.nextInt();
            }

            quicksort(a[i], 0, a[i].length - 1);
        }

        int[] i = new int[4];
        int[] mini = new int[4];
        int min = Integer.MAX_VALUE;

        while (true) {
            int l = 0, r = 0;

            for (int j = 1; j < 4; j++) {
                if (a[j][i[j]] < a[l][i[l]]) {
                    l = j;
                }
                if (a[j][i[j]] > a[r][i[r]]) {
                    r = j;
                }
            }
            if (a[r][i[r]] - a[l][i[l]] < min) {
                min = a[r][i[r]] - a[l][i[l]];
                for (int j = 0; j < 4; j++) {
                    mini[j] = a[j][i[j]];
                }
            }
            i[l]++;
            if (min == 0 || i[l] == a[l].length) break;


        }

        try {
            FileWriter out = new FileWriter("style.out");
            for (int j = 0; j < 4; j++) {
                out.write(String.valueOf(mini[j]) + " ");
            }
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        in.close();
    }
}

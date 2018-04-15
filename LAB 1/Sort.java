import java.io.*;
import java.lang.String;
import java.util.Scanner;


public class Sort {

    public static int[] merge(int[] a, int[] b, int n, int m) {
        int[] c = new int[n + m];
        int i = 0, j = 0;

        while (i < n || j < m) {
            if (j == m || (i < n && a[i] < b[j])) {
                c[i + j] = a[i++];
            } else {
                c[i + j] = b[j++];
            }
        }
        return c;
    }

    public static int[] mergeSort(int[] a, int n) {
        if (n < 2) {
            return a;
        }
        int m = n / 2;
        int[] leftArray = new int[m];
        int[] rightArray = new int[n - m];
        int i, j;

        for (i = 0; i < m; i++) {
            leftArray[i] = a[i];
        }
        for (i = 0, j = m; j < n; i++, j++) {
            rightArray[i] = a[j];
        }

        return merge(mergeSort(leftArray, m), mergeSort(rightArray, n - m), m, n - m);
    }

    public static void main(String[] args) {
        Scanner in = new Scanner("");

        try {
            in = new Scanner(new File("sort.in"));
        } catch (IOException e) {
            e.printStackTrace();
        }

        int arraySize = in.nextInt();
        int[] array = new int[arraySize];
        for (int i = 0; i < arraySize; i++) {
            array[i] = in.nextInt();
        }

        array = mergeSort(array, arraySize);

        try {
            FileWriter out = new FileWriter("sort.out");

            for (int i = 0; i < arraySize; i++) {
                out.write(String.valueOf(array[i]) + " ");
            }

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        in.close();

    }
}

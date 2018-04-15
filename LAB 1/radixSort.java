import java.io.*;
import java.lang.String;
import java.util.Scanner;


public class radixSort {

    public static String[] merge(String[] a, String[] b, int n, int m, int ind) {
        String[] c = new String[n + m];
        int i = 0, j = 0;

        while (i < n || j < m) {
            if (j == m || (i < n && a[i].charAt(ind) <= b[j].charAt(ind))) {
                c[i + j] = a[i++];
            } else {
                c[i + j] = b[j++];
            }
        }
        return c;
    }

    public static String[] mergeSort(String[] a, int n, int ind) {
        if (n < 2) {
            return a;
        }
        int m = n / 2;
        String[] rightArray = new String[n - m];
        int i, k;

        for (i = 0, k = m; k < n; i++, k++) {
            rightArray[i] = a[k];
        }

        return merge(mergeSort(a, m, ind), mergeSort(rightArray, n - m, ind), m, n - m, ind);
    }

    public static void main(String[] args) {
        Scanner in = new Scanner("");

        try {
            in = new Scanner(new File("radixsort.in"));
        } catch (IOException e) {
            e.printStackTrace();
        }

        int arraySize = in.nextInt();
        int arrayLength = in.nextInt();
        int iNumber = in.nextInt();
        in.nextLine();
        String[] array = new String[arraySize];

        for (int i = 0; i < arraySize; i++) {
            array[i] = in.nextLine();
        }

        for (int i = 0; i < iNumber; i++) {
            array = mergeSort(array, arraySize, arrayLength - 1 - i);
        }


        try {
            FileWriter out = new FileWriter("radixsort.out");

            for (int i = 0; i < arraySize; i++) {
                out.write(array[i]);
                out.write("\r\n");
            }

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        in.close();

    }
}

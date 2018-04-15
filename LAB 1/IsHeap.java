import java.io.*;
import java.util.Scanner;


public class IsHeap {

    public static void main(String[] args) {
        int binTreeSize = 0;
        boolean heap = true;
        Scanner in = new Scanner("");

        try {
            in = new Scanner(new File("isheap.in"));
        } catch (IOException e) {
            e.printStackTrace();
        }

        binTreeSize = in.nextInt();
        int[] binTree = new int[binTreeSize];
        for (int i = 0; i < binTreeSize; i++) {
            binTree[i] = in.nextInt();
        }

        for (int i = 0; i < binTreeSize; i++) {
            if (2 * i + 1 < binTreeSize && binTree[i] > binTree[2 * i + 1]) {
                heap = false;
                break;
            }
            if (2 * i + 2 < binTreeSize && binTree[i] > binTree[2 * i + 2]) {
                heap = false;
                break;
            }
        }

        try {
            FileWriter out = new FileWriter("isheap.out");
            if (heap) {
                out.write("YES");
            } else {
                out.write("NO");
            }
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        in.close();

    }
}

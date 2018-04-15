import java.io.*;
import java.util.Scanner;
import java.util.ArrayList;
import java.lang.*;

public class priorityqueue {

    public static void siftUp(ArrayList<Integer> heap, int k) {
        int p = (k - 1) / 2, t;
        while (heap.get(p) > heap.get(k)) {
            t = heap.get(p);
            heap.set(p, heap.get(k));
            heap.set(k, t);
            k = p;
            p = (k - 1) / 2;
        }

    }

    public static void siftDown(ArrayList<Integer> heap, int k) {
        int c1 = 2 * k + 1;
        int c2 = 2 * k + 2;
        if (c1 >= heap.size()) {
            return;
        }
        if (c2 >= heap.size()) {
            c2 = c1;
        }
        if (heap.get(k) <= heap.get(c1) && heap.get(k) <= heap.get(c2)) {
            return;
        }
        int min = c1;
        if (heap.get(c1) > heap.get(c2)) {
            min = c2;
        }
        int t = heap.get(min);
        heap.set(min, heap.get(k));
        heap.set(k, t);
        siftDown(heap, min);
    }

    public static void add(ArrayList<Integer> heap, int x) {
        heap.add(x);
        siftUp(heap, heap.size() - 1);
    }

    public static String extractMin(ArrayList<Integer> heap) {
        if (heap.size() == 0) {
            return "*";
        } else {
            int res = heap.get(0);
            heap.set(0, heap.get(heap.size() - 1));
            heap.remove(heap.size() - 1);
            siftDown(heap, 0);
            return String.valueOf(res);
        }
    }

    public static void change(ArrayList<Integer> heap, int key, int value) {
        int i = 0;
        for (i = 0; i < heap.size(); i++) {
            if (heap.get(i) == key) {
                break;
            }
        }

        heap.set(i, value);
        siftUp(heap, i);
    }

    public static void main(String[] args) {
        try {
            Scanner in = new Scanner(new File("priorityqueue.in"));
            FileWriter out = new FileWriter("priorityqueue.out");

            String s;
            ArrayList<Integer> a = new ArrayList<>();
            ArrayList<Integer> q = new ArrayList<>();
            while (in.hasNextLine()) {
                s = in.nextLine();
                String[] request = s.split(" ");
                q.add(-1);
                switch (request[0]) {
                    case "push":
                        add(a, Integer.valueOf(request[1]));
                        q.set(q.size() - 1, Integer.valueOf(request[1]));
                        break;
                    case "extract-min":
                        out.write(extractMin(a) + "\r\n");
                        break;
                    case "decrease-key":
                        change(a, q.get(Integer.valueOf(request[1]) - 1), Integer.valueOf(request[2]));
                        q.set(Integer.valueOf(request[1]) - 1, Integer.valueOf(request[2]));
                        break;

                }
            }
            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

import java.util.Scanner;
import java.util.*;

public class ConnectingPoints {
    static class Point {
        int x, y;
        int index;
    }

    static class Edge {
        Point p1, p2;
        double distance;
    }

    static class UnionFind {
        int[] parent;
        UnionFind(int n) {
              parent = new int[n];
              for (int i = 0; i < n; i++)
                parent[i] = -1;
        }

        void Union(int index1, int index2) {
              int p1 = Find(index1);
              int p2 = Find(index2);
              parent[p1] = p2;
        }

        int Find(int index) {
              if (parent[index] == -1)
                  return index;
              return Find(parent[index]);
        }
    }

    static class CompareEdge implements Comparator<Edge> {
        @Override
        public int compare(Edge e1, Edge e2) {
              double diff = e1.distance - e2.distance;
              if (diff < 0)
                 return -1;
              else if (diff > 0)
                 return 1;
              else
                 return 0;
              //return (int)Math.ceil(e1.distance - e2.distance);
        }
    }

    private static double minimumDistance(int[] x, int[] y) {
        double result = 0.;
        //write your code here
        int n = x.length;
        List<Edge> edges = new ArrayList<Edge>();

        Point[] p = new Point[n];

        for (int i = 0; i < n; i++) {
              p[i] = new Point();
              p[i].x = x[i];
              p[i].y = y[i];
              p[i].index = i;
        }
 
        for (int i =0; i < n; i++) {
           for (int j = i+1; j < n; j++) {
              Edge e = new Edge();
              e.p1 = p[i];
              e.p2 = p[j];
              e.distance = (double)Math.sqrt(Math.pow((p[i].x - p[j].x), 2) +
							Math.pow((p[i].y - p[j].y), 2));
              edges.add(e);
              //System.out.println("dist:" + e.distance);
           } 
        }

        Collections.sort(edges, new CompareEdge());

        UnionFind uf = new UnionFind(n);

        for (int i = 0; i < (n*(n-1)/2); i++) {
              if (uf.Find(edges.get(i).p1.index) != uf.Find(edges.get(i).p2.index)) {
                    result += edges.get(i).distance;
                    uf.Union(edges.get(i).p1.index, edges.get(i).p2.index);
              }
        }

        return result;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int[] x = new int[n];
        int[] y = new int[n];
        for (int i = 0; i < n; i++) {
            x[i] = scanner.nextInt();
            y[i] = scanner.nextInt();
        }
        System.out.println(minimumDistance(x, y));
    }
}


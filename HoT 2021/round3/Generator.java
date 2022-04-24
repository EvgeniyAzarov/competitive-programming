import java.util.Random;
import java.util.Stack;
import java.io.FileWriter;
import java.io.File;
import java.io.IOException;



public class Generator {
    private static final int MIN_N = 47;
    private static final int MAX_N = 200;
    private static int MAX_K = 5;
    private static final int[] Ks = {3, 3, 14, 14, 14};
    private static Random rng;

    private static double rand(double low, double hi)
    {
        return rng.nextDouble() * (hi - low) + low;
    }

    private static int get_k(int max_k)
    {
        max_k = Math.min(max_k, MAX_K);
        int sum = 0;
        for (int i = 0; i < max_k; i++)
        {
            sum += Ks[i];
        }

        int v = rng.nextInt(sum);
        for (int i = 0; i < max_k; i++)
        {
            if (Ks[i] > v) return i + 1;
            v -= Ks[i];
        }

        return max_k;
    }

	public static void main(String[] args) {
		for(int i = 0; i < 20; i++) {
			String graph = generate(i);
			File file = new File("tests/test" + i);
			FileWriter fr = null;
			try {
				fr = new FileWriter(file);
				fr.write(graph);
			} catch (IOException e) {
				e.printStackTrace();
			} finally{
				try {
					fr.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}		
	}

    public static String generate(int sd){
        rng = new Random(sd);

        int n = rng.nextInt(MAX_N - MIN_N + 1) + MIN_N;
        int hi, mid, low;

        hi = (int)(n * rand(0.05, 0.25));
        low = (int)(n * rand(0.05, 0.25));
        mid = n - hi - low;

        double hi_hi, hi_mid, hi_low, mid_mid, mid_low, low_low;

        do
        {
            double lim = rand(0.25, 0.5);
            hi_hi = rand(0, lim);
            hi_mid = rand(0, lim);
            hi_low = rand(0, lim);
            mid_mid = rand(0, lim);
            mid_low = rand(0, lim);
            low_low = rand(0, lim);
        } while(!check_params(hi_hi, hi_mid, hi_low, mid_mid, mid_low, low_low));

        int[][] graph = new int[n][n];
        graph_generate(graph, hi, mid, low, hi_hi, hi_mid, hi_low, mid_mid, mid_low, low_low);
        while (!test_connection(graph)) // Make sure graph generated is connected
            graph_generate(graph, hi, mid, low, hi_hi, hi_mid, hi_low, mid_mid, mid_low, low_low);

        int m = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                m += graph[i][j];

        int max_k = n * (n - 1) / 2 - m;
        int k = get_k(max_k);

		String s = "";
        //System.out.println(n + " " + m + " " + k);
		s += (n + " " + m + " " + k + "\n");
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (graph[i][j] == 1)
                    //System.out.println((i + 1) + " " + (j + 1));
					s += ((i + 1) + " " + (j + 1) + "\n");

		return s;
    }

    private static Boolean check_params(double hi_hi, double hi_mid, double hi_low, double mid_mid, double mid_low, double low_low)
    {
        if (hi_hi <= hi_mid) return false;
        if (hi_mid <= hi_low) return false;

        if (hi_mid <= mid_mid) return false;
        if (mid_mid <= mid_low) return false;

        if (hi_low <= mid_low) return false;
        if (mid_low <= low_low) return false;

        return true;
    }

    private static void graph_generate(int[][] graph, int v1, int v2, int v3, double d11, double d12, double d13, double d22, double d23, double d33){
        int size = v1 + v2 + v3;
        for (int i = 0; i < size; i++){
            graph[i][i] = 1;
            for (int j = i + 1; j < size; j++){
                if (i < v1 && j < v1) {
                    if (rng.nextDouble() < d11) {
                        graph[i][j] = 1;
                        graph[j][i] = 1;
                    } else {
                        graph[i][j] = 0;
                        graph[j][i] = 0;
                    }
                }
                else if (i < v1 && j < v1 + v2) {
                    if (rng.nextDouble() < d12) {
                        graph[i][j] = 1;
                        graph[j][i] = 1;
                    } else {
                        graph[i][j] = 0;
                        graph[j][i] = 0;
                    }
                }
                else if (i < v1) {
                    if (rng.nextDouble() < d13) {
                        graph[i][j] = 1;
                        graph[j][i] = 1;
                    } else {
                        graph[i][j] = 0;
                        graph[j][i] = 0;
                    }
                }
                else if (i < v1 + v2 && j < v1 + v2) {
                    if (rng.nextDouble() < d22) {
                        graph[i][j] = 1;
                        graph[j][i] = 1;
                    } else {
                        graph[i][j] = 0;
                        graph[j][i] = 0;
                    }
                }
                else if (i < v1 + v2) {
                    if (rng.nextDouble() < d23) {
                        graph[i][j] = 1;
                        graph[j][i] = 1;
                    } else {
                        graph[i][j] = 0;
                        graph[j][i] = 0;
                    }
                }
                else {
                    if (rng.nextDouble() < d33) {
                        graph[i][j] = 1;
                        graph[j][i] = 1;
                    } else {
                        graph[i][j] = 0;
                        graph[j][i] = 0;
                    }
                }
            }
        }
    }

    static private boolean test_connection(int[][] graph){
        //BFS search
        int size = graph.length;
        Stack stack = new Stack();
        int[] checked = new int[size];
        int[] connected = new int[size];
        for (int i = 0; i < size; i++){
            checked[i] = 0;
            connected[i] = 0;
        }
        checked[0] = 1;

        for (int i = 0; i < size; i++){
            if (graph[0][i] == 1){
                connected[i] = 1;
                if (checked[i] == 0){
                    checked[i] = 1;
                    stack.push(i);
                }
            }
        }

        while (!stack.empty()){
            int next = (int) stack.pop();
            for (int i = 0; i < size; i++){
                if (graph[next][i] == 1){
                    connected[i] = 1;
                    if (checked[i] == 0){
                        checked[i] = 1;
                        stack.push(i);
                    }
                }
            }
        }

        for (int i = 0; i < size; i++){
            if (connected[i] == 0)
                return false;
        }

        return true;
    }
}






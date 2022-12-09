import java.util.*;
import java.lang.Math;
import java.security.SecureRandom;
import java.util.Locale;

public class generator {
    private final int MIN_UE_N = 20;
    private final int MAX_UE_N = 200;
    private final double ROOM_SZ = 20;
    private final double C_NS = 0.299792458;
    private final double TOA_OFFSET = 200;

    private int n;
    private double[][] bs;
    private double[][] ue;
    private double[][] toa;

    private Random random;

    private int randomInt(int lower, int upper) {
        return lower + random.nextInt(upper - lower + 1);
    }

    private double randomDouble(double lower, double upper) {
        return lower + random.nextDouble() * (upper - lower);
    }

    private void generate(Long seed) {
        random = seed != null ? new Random(seed) : new SecureRandom();
        n = randomInt(MIN_UE_N, MAX_UE_N);

        double nlos_prob = randomDouble(0, 0.5);
        double nlos_err_max = randomDouble(5, 50);
        double toa_std = randomDouble(0, 5);

        bs = new double[4][];

        bs[0] = new double[2];
        bs[0][0] = (randomDouble(0, 1) - 1.0) * ROOM_SZ / 2;
        bs[0][1] = (randomDouble(0, 1) - 1.0) * ROOM_SZ / 2;

        bs[1] = new double[2];
        bs[1][0] = randomDouble(0, 1) * ROOM_SZ / 2;
        bs[1][1] = (randomDouble(0, 1) - 1.0) * ROOM_SZ / 2;

        bs[2] = new double[2];
        bs[2][0] = (randomDouble(0, 1) - 1.0) * ROOM_SZ / 2;
        bs[2][1] = randomDouble(0, 1) * ROOM_SZ / 2;

        bs[3] = new double[2];
        bs[3][0] = randomDouble(0, 1) * ROOM_SZ / 2;
        bs[3][1] = randomDouble(0, 1) * ROOM_SZ / 2;

        ue = new double[n][];

        for (int i = 0; i < n; ++i) {
            ue[i] = new double[2];
            ue[i][0] = (randomDouble(0, 1) - 0.5) * ROOM_SZ;
            ue[i][1] = (randomDouble(0, 1) - 0.5) * ROOM_SZ;
        }

        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 2; ++j)
                bs[i][j] = Math.round(bs[i][j] * 1000.0) / 1000.0;

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < 2; ++j)
                ue[i][j] = Math.round(ue[i][j] * 1000.0) / 1000.0;

        toa = new double[n][];

        for (int i = 0; i < n; ++i) {
            toa[i] = new double[4];
            double toa_offset = randomDouble(0, TOA_OFFSET);

            for (int j = 0; j < 4; ++j) {
                toa[i][j] = Math.sqrt((ue[i][0]-bs[j][0])*(ue[i][0]-bs[j][0]) + (ue[i][1]-bs[j][1])*(ue[i][1]-bs[j][1])) / C_NS;
                toa[i][j] += toa_offset;

                if (randomDouble(0, 1) < nlos_prob) {
                    toa[i][j] += randomDouble(0, nlos_err_max);
                }

                toa[i][j] += randomDouble(0, toa_std);
            }
        }
    }

    private void printInput() {
        System.out.println(n);

        System.out.printf("%.3f %.3f\n", bs[0][0], bs[0][1]);
        System.out.printf("%.3f %.3f\n", bs[1][0], bs[1][1]);

        for (int i = 0; i < n; i++)
            System.out.printf("%.3f %.3f %.3f %.3f\n", toa[i][0], toa[i][1], toa[i][2], toa[i][3]);
    }

    private void printActual() {
        System.out.printf("%.3f %.3f\n", bs[0][0], bs[0][1]);
        System.out.printf("%.3f %.3f\n", bs[1][0], bs[1][1]);
        System.out.printf("%.3f %.3f\n", bs[2][0], bs[2][1]);
        System.out.printf("%.3f %.3f\n", bs[3][0], bs[3][1]);

        for (int i = 0; i < n; i++)
            System.out.printf("%.3f %.3f\n", ue[i][0], ue[i][1]);
    }

    public static void main(String args[]) {
		Locale.setDefault(Locale.US);
        Long seed = null;
        if (args.length > 0) {
            seed = Long.parseLong(args[0]);
        }

        generator g = new generator();
        g.generate(seed);
        g.printInput();
        g.printActual();
    }
}

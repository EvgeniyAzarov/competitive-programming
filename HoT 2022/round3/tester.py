import numpy as np
import subprocess
import sys

N0 = 0
N = 43

# base_res_python = np.array([3309032, 1842330, 1986190, 1624784, 1591330, 2683263, 3082627, 2163746, 2642664, 1502907, 3639992, 2101003, 3488277, 1855511, 2317784, 2564443, 1680580, 1627162, 3007379, 2173897, 1263419, 2171042, 2544317, 2049030, 2281700, 1466924, 1602624, 1907637, 2584243, 1682099, 2386177, 2433291, 1799758, 2272879, 1639365, 2321291, 1883047, 2531336, 1636862, 1528525, 1889434, 2994755, 2724741, 2942033])
# base_res = np.array([2869995, 3965239, 2456853, 1619436, 1837072, 2297109, 3072914, 2625200, 2472107, 1668780, 2213402, 2458618, 3376163, 3933765, 2506789, 3454182, 4210693, 1829373, 3519199, 1935264, 1391076, 2159094, 2505036, 3644158, 2499327, 1358812, 3868378, 2271338, 2924615, 4755259, 2716931, 2908113, 3716938, 2411185, 1737890, 2945728, 2161114, 3016230, 1599838, 1461811, 2720132, 4168550, 3740828, 2810098])
base_res = np.array([2338508, 4353528, 4476436, 1656934, 1600241, 3172215, 3970671, 3843878, 4781321, 2725784, 3248539, 1890568, 3333220, 3541775, 3294938, 4047854, 2345307, 1696212, 3341094, 2516462, 1274717, 1758157, 4151480, 3448410, 2798093, 2618193, 4032992, 2825206, 3573217, 4216713, 2586080, 2338947, 3380098, 3011478, 1626409, 3971552, 2556548, 4013026, 1565478, 3414780, 2113546, 3970384, 3729826, 3271305, 2371128, 2373623, 2628903, 3394636, 4325562, 3203609, 1931926])


if __name__ == '__main__':
    solution = sys.argv[1]
    if solution.split(".")[-1] == 'py':
        run_args = [sys.executable, solution]
    else:
        run_args = [f"./{solution}"]

    if len(sys.argv) > 2:
        N = int(sys.argv[2])
    if len(sys.argv) > 3:
        N0 = int(sys.argv[2])
        N = int(sys.argv[3])

    tests_res = []

    for i in range(N0, N+1):
        print(f"=== TEST {i} ===")
        with open(f"tests/{i}.test", "r") as file:
            data = file.read()

        lines = data.split("\n")
        n = int(lines[0])
        input_data = "\n".join(lines[:n+3])
        output_data = lines[n+3:]

        completed_process = subprocess.run(run_args,
                                           input=input_data,
                                           capture_output=True, 
                                           text=True)
        print(completed_process.stderr)

        solution_output_lines = completed_process.stdout.split("\n")[:-1]

        # for verification of test 0, should be 2918539
        #  solution_ouput_lines = """
        #  -0.657574772 2.202897216
        #  9.612727847 7.184456177
        #  6.052894344 -3.230646577
        #  -6.258069892 -5.628141926
        #  -7.630356154 8.287634824
        #  0.906085783 0.813700552
        #  5.519233285 -2.995729624
        #  3.011525986 8.822308221
        #  -0.400688838 -7.997504188""".split("\n")[1:]

        output_data_real = output_data[2:-1]

        bs_pos_real = np.zeros((2, 2))
        bs_pos_real[0, :] = np.asarray(output_data_real[0].split(" "), dtype=float)
        bs_pos_real[1, :] = np.asarray(output_data_real[1].split(" "), dtype=float)

        bs_pos_sol = np.zeros((2, 2))
        bs_pos_sol[0, :] = np.asarray(solution_output_lines[0].strip().split(" "), dtype=float)
        bs_pos_sol[1, :] = np.asarray(solution_output_lines[1].strip().split(" "), dtype=float)

        Dbs = np.sqrt(np.mean(np.sum((bs_pos_sol - bs_pos_real) ** 2, axis=1), axis=0))
        #  print(bs_pos_sol)
        #  print(bs_pos_real)

        ue_pos_real = np.zeros((n, 2))
        ue_pos_sol = np.zeros((n, 2))
        for j in range(n):
            ue_pos_real[j, :] = np.asarray(output_data_real[j+2].split(" "), dtype=float)
            ue_pos_sol[j, :] = np.asarray(solution_output_lines[j + 2].strip().split(" "), dtype=float)

        #  print(ue_pos_sol)
        #  print(ue_pos_real)

        Due = np.sqrt(np.mean(np.sum((ue_pos_real - ue_pos_sol) ** 2, axis=1)))

        res = round((1 / (1 + Dbs) + 1 / (1 + Due)) * 5 * 10 ** 6)
        tests_res.append(res)

        print(f"Res: {res}")
        print(f"Base: {base_res[i]}")
        print(f"Diff with base: {res - base_res[i]}")
        print()

    # print(list(tests_res))

    res_sum = np.array(tests_res).sum()
    sum_base = base_res[N0:N+1].sum()
    print(f"Sum: {res_sum}")
    print(f"Base: {sum_base}")
    print(f"diff with base: {res_sum - sum_base}")
    print(f"Improvement: {(res_sum / sum_base - 1) * 100:.2f}%")


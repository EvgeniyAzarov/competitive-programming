import numpy as np
import subprocess
import sys


if __name__ == '__main__':

    for seed in range(1, 51):
        run_args = ['java', 'generator', str(seed)]

        with open(f'../tests/{seed}.test', 'w') as file:
            completed_process = subprocess.run(run_args,
                                           text=True,
                                           stdout=file)


import numpy as np
from collections import defaultdict


for i in range(1, 51):
    print(f"=== TEST {i} ===")

    with open(f'tests/{i}.test', 'r') as file:
        data = file.read()

    lines = data.split('\n')
    n, m, c = list(map(int, lines[0].split(" ")))

    messages = defaultdict(list) 
    messages_bytype = defaultdict(list)
    for line in lines[1:-1]:
        m_type, m_user, m_time, m_deadline = list(map(int, line.split(" ")))
        messages[m_user].append(m_type)
        messages_bytype[m_type].append(m_user)

    msgs_numbers = [len(msgs) for msgs in messages.values()]

    print(f"Messages: {n}")
    print(f"Users: {len(messages)}")
    print(f"Msg types: {len(messages_bytype)}")
    print(f"Users / Types: {len(messages) / len(messages_bytype)}")
    print(f"Avg messages: {np.mean(msgs_numbers)}")
    print()

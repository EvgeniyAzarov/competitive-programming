import numpy as np

max_iter_num = 10
max_iter_ue = 50
room_size = 20
c_ns = 0.299792458

np.random.seed(47)

ue_num = int(input())

bs_pos_1 = np.asarray(input().split(" "), dtype=float)
bs_pos_2 = np.asarray(input().split(" "), dtype=float)

data_input = np.zeros([ue_num, 4], float)
for i in range(ue_num):
    data_input[i] = np.asarray(input().split(" "), dtype=float)

toa_all = data_input

bs_pos = np.zeros((4, 2))
bs_pos[0, :] = bs_pos_1
bs_pos[1, :] = bs_pos_2
bs_pos[2, :] = np.array([-1, 1]) * 5
bs_pos[3, :] = np.array([1, 1]) * 5
bs_num = bs_pos.shape[0]

ue_pos_est = np.zeros((ue_num, 2), dtype=float)
bs_pos_est = bs_pos.copy()

min_loss = np.inf
tdoa_measured = toa_all[:, 1:] - toa_all[:, 0:1]
ue_pos_best = ue_pos_est.copy()
bs_pos_best = bs_pos_est.copy()

for iter in range(max_iter_num):
    bs_pos_est[2, 0] = (np.random.rand() - 1) * room_size / 2
    bs_pos_est[3, 0] = (np.random.rand()) * room_size / 2
    bs_pos_est[2, 1] = (np.random.rand()) * room_size / 2
    bs_pos_est[3, 1] = (np.random.rand()) * room_size / 2

    loss_tdoa = 0
    for ue_i in range(ue_num):
        min_loss_ue = np.inf
        for iter_ue in range(max_iter_ue):
            ue_pos_est_i = (np.random.rand(2) - 0.5) * room_size
            toa_est_i = (
                np.sqrt(
                    (bs_pos_est[:, 0] - ue_pos_est_i[0]) ** 2
                    + (bs_pos_est[:, 1] - ue_pos_est_i[1]) ** 2
                )
                / c_ns
            )
            tdoa_est_i = toa_est_i[1:] - toa_est_i[0:1]
            loss_tdoa_i = np.sum((tdoa_est_i - tdoa_measured[ue_i, :]) ** 2)

            if loss_tdoa_i < min_loss_ue:
                ue_pos_est[ue_i, :] = ue_pos_est_i.copy()
                min_loss_ue = loss_tdoa_i

        loss_tdoa += min_loss_ue

    if loss_tdoa < min_loss:
        ue_pos_best = ue_pos_est.copy()
        bs_pos_best = bs_pos_est.copy()
        min_loss = loss_tdoa

ue_pos_est = ue_pos_best
bs_pos_est = bs_pos_best

output_data_line_1 = np.array([[bs_pos_est[2, 0], bs_pos_est[2, 1]]])
output_data_line_2 = np.array([[bs_pos_est[3, 0], bs_pos_est[3, 1]]])
output_data = ue_pos_est

print(bs_pos_est[2, 0], bs_pos_est[2, 1])
print(bs_pos_est[3, 0], bs_pos_est[3, 1])

for row in output_data:
    print(*row)


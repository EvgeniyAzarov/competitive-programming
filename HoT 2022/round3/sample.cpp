#include "bits/stdc++.h"

using namespace std;

const double SZ = 10.0;
const int MAX_N = 200;
const int INF = 1e+9;
const int IT = 1000;
const int IT_UE = 100;
const double C_NS = 0.299792458;

int n;
double bs[4][2];
double ue[MAX_N][2];
double t[MAX_N][4];
double bs_best[4][2];
double ue_best[MAX_N][2];
double toa[4];

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution < > dis(0, 1);

double get_rand(double x = 1) {
	return dis(gen) * x;
}

int main() {
	cin >> n;

	cin >> bs[0][0] >> bs[0][1];
	cin >> bs[1][0] >> bs[1][1];

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < 4; ++j)
			cin >> t[i][j];

	double min_loss = INF;

	for (int i = 0; i < IT; ++i) {
		bs[2][0] = -get_rand() * SZ;
		bs[2][1] = get_rand() * SZ;
		bs[3][0] = get_rand() * SZ;
		bs[3][1] = get_rand() * SZ;

		double loss_tdoa = 0;

		for (int j = 0; j < n; ++j) {
			double min_loss_ue = INF;

			for (int k = 0; k < IT_UE; ++k) {
				double ue_x = (get_rand(2) - 1) * SZ;
				double ue_y = (get_rand(2) - 1) * SZ;

				for (int l = 0; l < 4; ++l)
					toa[l] = sqrt((ue_x - bs[l][0]) * (ue_x - bs[l][0]) + (ue_y - bs[l][1]) * (ue_y - bs[l][1])) / C_NS;

				double loss = 0;
				for (int l = 1; l < 4; ++l)
					loss += ((toa[l] - toa[0]) - (t[j][l] - t[j][0])) * ((toa[l] - toa[0]) - (t[j][l] - t[j][0]));

				if (loss < min_loss_ue) {
					min_loss_ue = loss;
					ue[j][0] = ue_x;
					ue[j][1] = ue_y;
				}
			}

			loss_tdoa += min_loss_ue;
		}

		if (loss_tdoa < min_loss) {
			min_loss = loss_tdoa;

			for (int j = 0; j < 4; ++j) {
				bs_best[j][0] = bs[j][0];
				bs_best[j][1] = bs[j][1];
			}

			for (int j = 0; j < n; ++j) {
				ue_best[j][0] = ue[j][0];
				ue_best[j][1] = ue[j][1];
			}
		}
	}

	for (int i = 2; i < 4; ++i)
		printf("%0.9f %0.9f\n", bs_best[i][0], bs_best[i][1]);

	for (int i = 0; i < n; ++i)
		printf("%0.9f %0.9f\n", ue_best[i][0], ue_best[i][1]);

	return 0;
}


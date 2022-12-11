#include "bits/stdc++.h"

using namespace std;

const double SZ = 10.0;
const int MAX_N = 200;
const int INF = 1e+9;
int IT = 1000;
int IT_UE = 100;
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
std::normal_distribution < > ndis(0, 1);

double get_rand(double x = 1) {
	return dis(gen) * x;
}

double get_nrand(double x = 1) {
	return ndis(gen) * x;
}

double norm(double x[]) {
	return sqrt(pow(x[0], 2) + pow(x[1], 2));
}

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

int main() {
	cin >> n;

	cin >> bs[0][0] >> bs[0][1];
	cin >> bs[1][0] >> bs[1][1];

	double M[2];
	M[0] = (bs[0][0] + bs[1][0]) / 2;
	M[1] = (bs[0][1] + bs[1][1]) / 2;

	double R[2];
	R[0] = bs[0][0] - M[0];
	R[1] = bs[0][1] - M[1];
	double Rnorm = norm(R); 

	double Q[2][2];
	Q[0][0] = R[0] / Rnorm; Q[0][1] = -R[1] / Rnorm;
	Q[1][0] = R[1] / Rnorm; Q[1][1] = R[0] / Rnorm;

	// Idea3: detect nLoS noise and ignore UEs with it

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < 4; ++j)
			cin >> t[i][j];

	// creating hyperbolas
	bool total_random[n];
	vector< vector<double> > hx(n);
	vector< vector<double> > hy(n);
	double c = sqrt(pow(bs[0][0] - bs[1][0], 2) + pow(bs[0][1] - bs[1][1], 2)) / 2;
	for (int i = 0; i < n; i++) {
		double d = (t[i][0] - t[i][1]) * C_NS;
		double a = abs(d) / 2;  

		if (a > c) {
			total_random[i] = true;
		} else {
			// cout << a << endl;
			total_random[i] = false;

			double b = sqrt(c * c - a * a);
			double tmax = max(acosh(2 * SZ / a), asinh(2 * SZ / b));
			
			double step = 1.0 / IT_UE;
			for (double t = -1; t < 1; t+=step) {
				// double ts = sgn(t) * pow(abs(t), 0.5) * tmax;
				double ts = sgn(t) * log(1 + abs(t)) * tmax / log(2);

				double x = -sgn(d) * a * cosh(ts);
				double y = b * sinh(ts);

				double xx = Q[0][0] * x + Q[0][1] * y + M[0];
				double yy = Q[1][0] * x + Q[1][1] * y + M[1];

				if (-SZ < xx && xx < SZ && -SZ < yy && yy < SZ) {
					hx[i].push_back(xx);
					hy[i].push_back(yy);
				}
			}
		}

		// if (!total_random[i]) {
		// 	cout << i << endl;
		// 	for (int j = 0; j < int(hx[i].size()); j++) {
		// 		cout << hx[i][j] << ", ";
		// 	}
		// 	cout << endl;

		// 	for (int j = 0; j < int(hy[i].size()); j++) {
		// 		cout << hy[i][j] << ", ";
		// 	}
		// 	cout << endl;
		// }
	}

	bs[2][0] = -get_rand() * SZ;
	bs[2][1] = get_rand() * SZ;
	bs[3][0] = get_rand() * SZ;
	bs[3][1] = get_rand() * SZ;


	double min_loss = INF;
	bool third_bs = true;
	for (int i = 0; i < IT; ++i) {
		// Idea4: adjust positions of 3 and 4 BS iteratively, instead of random sampling each time. 
		// Idea5: Use information of estimated UE positions. Probably this will produce some convergance
		if (i % 2 == 0) {
		// if (third_bs){
			bs[2][0] = -get_rand() * SZ;
			bs[2][1] = get_rand() * SZ;
			bs[3][0] = bs_best[3][0];
			bs[3][1] = bs_best[3][1]; 

		} else {
			bs[2][0] = bs_best[2][0];
			bs[2][1] = bs_best[2][1]; 
			bs[3][0] = get_rand() * SZ;
			bs[3][1] = get_rand() * SZ;
		}

		double loss_tdoa = 0;

		for (int j = 0; j < n; ++j) {
			double min_loss_ue = INF;

			for (int k = 0; k < IT_UE; ++k) {
				double ue_x, ue_y;
				if (!total_random[j] && n < 100) {
					int random_index = rand() % hx[j].size();
					// ue_x = hx[j][random_index];
					// ue_y = hy[j][random_index];
					if (k > hx[j].size()){
						break;
					}
					ue_x = hx[j][k];
					ue_y = hy[j][k];
				} else {
					ue_x = (get_rand(2) - 1) * SZ;
					ue_y = (get_rand(2) - 1) * SZ;
				}

				for (int l = 0; l < 4; ++l)
					toa[l] = sqrt(pow(ue_x - bs[l][0], 2) + pow(ue_y - bs[l][1], 2)) / C_NS;

				double loss0 = 0, loss1 = 0;
				double weights[4] = {1, 1, 0.5, 0.5};
				for (int l = 1; l < 4; ++l) {
					// loss += weights[l] * ((toa[l] - toa[0]) - (t[j][l] - t[j][0])) * ((toa[l] - toa[0]) - (t[j][l] - t[j][0]));
					loss0 += weights[l] * abs((toa[l] - toa[0]) - (t[j][l] - t[j][0]));
					loss1 += weights[l] * abs((toa[l] - toa[1]) - (t[j][l] - t[j][1]));
				}
				
				// double loss = loss0 + loss1;
				double loss = max(loss0, loss1);

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
			third_bs = 1 - third_bs;

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


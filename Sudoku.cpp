/**
  **************************************************************
  * @file 		Sudoku.cpp
  * @author 	高明飞
  * @version 	V1.0
  * @date 		2017-06-07
  *
  * @brief 		任意N阶数独求解程序
  *				http://gaomf.cn/2017/06/07/Sudoku/
  * @details 
  * @verbatim
  * 本程序可求解任意N阶数独，并可选择是否加入对角线及分块约束。
  * 
  *
  * 修改记录：
  * 2017-06-07 :
  *   - File Created.
  *
  * @endverbatim
  ***************************************************************
  */

#include <iostream>
#include <vector>
#include <cstdlib>

//#define FIXEDORDER 5
//#define FIXEDDIAGONAL 0
//#define FIXEDPARTITION 1

using namespace std;

bool printSolution;
bool diagonal;
bool partition;
int order;

int NofSolutions;

vector<vector<unsigned char>> NumberBlank;
vector<vector<int>> Number;

/*
 * Print current result
 */
void PrintSudoku() {
	cout << "---------------------------------" << endl;
	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			cout << Number[i][j] << " ";
		}
		cout << endl;
	}
	cout << "---------------------------------" << endl;
}

/*
 * Find next blank positon 
 * i = 0 && j = -1 for first call
 */
bool FindNextBlank(int & i, int & j) {
	while (i < order) {
		while (++j < order) {
			if (NumberBlank[i][j]) {
				return true;
			}
		}
		j = -1, i++;
	}

	// Not Found
	return false;
}

/*
 * Find previous blank position
 * i = order - 1 && j = order for first call
 */
bool FindPreviousBlank(int & i, int & j) {
	while (i >= 0) {
		while (--j >= 0) {
			if (NumberBlank[i][j]) {
				return true;
			}
		}
		j = order, i--;
	}

	// Not Found
	return false;
}

/*
 * Check validity
 */
bool CheckValid(int i, int j) {
	// Row
	for (int tj = 0; tj < j; tj++) {
		if (Number[i][tj] == Number[i][j]) {
			return false;
		}
	}
	for (int tj = j + 1; tj < order; tj++) {
		if (Number[i][tj] == Number[i][j]) {
			return false;
		}
	}

	// Column
	for (int ti = 0; ti < i; ti++) {
		if (Number[ti][j] == Number[i][j]) {
			return false;
		}
	}
	for (int ti = i + 1; ti < order; ti++) {
		if (Number[ti][j] == Number[i][j]) {
			return false;
		}
	}

	// Diag
	if (diagonal) {
		if (i == j) {
			for (int t = 0; t < i; t++) {
				if (Number[t][t] == Number[i][j]) {
					return false;
				}
			}
			for (int t = i + 1; t < order; t++) {
				if (Number[t][t] == Number[i][j]) {
					return false;
				}
			}
		}
		else if (i + j == order - 1) {
			for (int t = 0; t < i; t++) {
				if (Number[t][order - t - 1] == Number[i][j]) {
					return false;
				}
			}
			for (int t = i + 1; t < order - 1; t++) {
				if (Number[t][order - t - 1] == Number[i][j]) {
					return false;
				}
			}
		}
	}

	// Partition
	if (partition) {
		int tmp = sqrt(order);
		int m = i / tmp;
		int n = j / tmp;

		for (int ti = m * tmp; ti < (m + 1) * tmp; ti++) {
			for (int tj = n * tmp; tj < (n + 1) * tmp; tj++) {
				if (ti == i && tj == j)
					continue;
				if (Number[ti][tj] == Number[i][j])
					return false;
			}
		}
	}

	return true;
}

void Solve() {
	int i = 0, j = -1;
	if (!FindNextBlank(i, j))
		return;

	while (true) {
		Number[i][j]++;
		// Recall
		if (Number[i][j] > order) {
			// Clear this positon first
			Number[i][j] = 0;
			if (!FindPreviousBlank(i, j)) {
				// Stop
				return;
			}
			continue;
		}

		if (!CheckValid(i, j))
			continue;

		// Valid!!

		// Found a solution
		if (!FindNextBlank(i, j)) {
			NofSolutions++;
			if (printSolution) {
				PrintSudoku();
			}
			
			// Find next solution
			i = order - 1, j = order;
			FindPreviousBlank(i, j);
		}
		// else find next blank positon
	}
}

int main() {
	cout << "是否要输出解(1: 是； 0: 否，只输出解的数量)： ";
	cin >> printSolution;
	cout << endl;
	while (true) {
		NofSolutions = 0;
		cout << "#############################" << endl;
		cout << "\n请输入数独阶数： ";
#ifndef FIXEDORDER
		cin >> order;
#else
		order = FIXEDORDER;
		cout << order << endl;
#endif
		cout << endl;

		cout << "是否考虑对角线(1: 考虑； 0: 不考虑)： ";
#ifndef FIXEDDIAGONAL
		cin >> diagonal;
#else
		diagonal = FIXEDDIAGONAL;
		cout << diagonal << endl;
#endif
		cout << endl;

		int tmp = sqrt(order);
		// Partition only for perfect square order
		if (tmp * tmp == order) {
			cout << "是否考虑分块(如正常九阶数独中的小九宫内不能重复)(1: 考虑； 0: 不考虑)： ";
#ifndef FIXEDPARTITION
			cin >> partition;
#else
			partition = FIXEDPARTITION;
			cout << partition << endl;
#endif
			cout << endl;
		}
		else {
			partition = false;
		}

		NumberBlank.resize(order);
		Number.resize(order);
		cout << "依次输入每一行，数字间用空格分隔，待填数字用 0 表示\n" << endl;
		for (int i = 0; i < order; i++) {
			Number[i].resize(order);
			NumberBlank[i].resize(order);
			cout << "请输入第" << i + 1 << "行： ";
			for (int j = 0; j < order; j++) {
				cin >> Number[i][j];
				if (Number[i][j] == 0) {
					NumberBlank[i][j] = 1;
				}
				else {
					NumberBlank[i][j] = 0;
				}
			}
			// Check input data validity
			for (int j = 0; j < order; j++) {
				if (Number[i][j] < 0 || Number[i][j] > order) {
					cout << "输入数据有误，请重新输入" << endl;
					i--;
					break;
				}
			}
			
			cout << endl;
		}

		bool valid = true;
		for (int i = 0; i < order; i++) {
			for (int j = 0; j < order; j++) {
				if (NumberBlank[i][j])
					continue;
				valid = CheckValid(i, j);
				if (!valid)
					break;
			}
			if (!valid)
				break;
		}
		if (!valid) {
			cout << "输入数据自身矛盾！" << endl;
		}
		else {
			Solve();
			cout << "解的数量： " << NofSolutions << endl;
		}
	}
	return 0;
}
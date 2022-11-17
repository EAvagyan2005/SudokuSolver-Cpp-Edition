#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <map>
#include <chrono>
#include <thread>
using namespace std;
//	DECLARATIONS
void start();
void get_input();
void get_nulls();
void get_possible();
bool check(vector<vector<int>> mat, int x, int y, int value);
void tryVariant(vector<vector<int>> mat, int k);
vector<vector<int>> matrix;
vector<pair<int, int>> null_list;
vector<vector<int>> probable_list;
bool Debugging = true;
bool toend = false;
int COUNT = 0;
int PRINT_PER_COUNT = 1000;
ofstream fout;
ifstream fin;
void check1() {
	if (!Debugging)
		return;
	for (int i = 0; i < 9; i++) {

		for (int j = 0; j < 9; j++)
			cout << matrix[i][j] << ' ';
		cout << endl;
	}
	for (int i = 0; i < null_list.size(); i++) {

		cout << null_list[i].first <<' '<< null_list[i].second << ' ';
	}
	cout << "################" << endl;
	for (int i = 0; i < probable_list[0].size(); i++)
		cout << probable_list[0][i] << ' ';
}

bool check(vector<vector<int>> mat, int x, int y, int value) {

	// Horizontal && Vertical
	for (int i = 0; i < 9; i++) {
		if (mat[i][y] == value)
			return false;
		if (mat[x][i] == value)
			return false;
	}

	// Square blocks
	int reqSectionX = int(x / 3);
	int reqSectionY = int(y / 3);
	int startX = reqSectionX * 3;
	int startY = reqSectionY * 3;
	for (int i = startX; i < startX + 3; i++) {
		for (int j = startY; j < startY + 3; j++) {
			if (mat[i][j] == value)
				return false;
		}
	}

	return true;
}

void get_possible() {
	int currX, currY;
	for (int i = 0; i < null_list.size(); i++) {
		currX = null_list[i].first;
		currY = null_list[i].second;
		for (int val = 1; val <= 9; val++)
			if (check(matrix, currX, currY, val))
				probable_list[i].push_back(val);
	}
}


void get_nulls() {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (matrix[i][j] == 0)
				null_list.push_back(make_pair(i, j));
}


void get_input() {
	fin.open("sudoku.txt", ios::in);
	char x;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			fin >> x;
			matrix[i][j] = int(x) - 48;
		}
	}
}


void print_vec(vector<vector<int>>& mat)
{
	system("cls");
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++) {
			cout << mat[i][j] << ' ';
			fout << mat[i][j] << ' ';
		}
		cout << endl;
		fout << endl;
	}
	cout << endl;
	fout << endl;
	cout << COUNT << endl;
	fout << COUNT << endl;
}
void tryVariant(vector<vector<int>> mat, int k) {
	if (toend)
	{
		print_vec(mat);
		return;
	}
	vector<vector<int>> nMat;
	if (k >= null_list.size()) {
		toend = true;
		print_vec(mat);
		return;
	}
	int currX = null_list[k].first;
	int currY = null_list[k].second;
	for (int i = 0; i < probable_list[k].size(); i++) {
		if (check(mat, currX, currY, probable_list[k][i]) and !toend) {
			nMat = mat;
			nMat[currX][currY] = probable_list[k][i];
			COUNT += 1;
			if (!(COUNT%PRINT_PER_COUNT)) {

				print_vec(nMat);
			}
			tryVariant(nMat, k + 1);
		}
	}
}



void start() {
	vector<vector<int>> nMat;
	matrix.resize(10);
	for (int i = 0; i < 10; i++)
		matrix[i].resize(10);
	fout.open("results.txt", ios::out);
	get_input();
	get_nulls();
	probable_list.resize(null_list.size());
	get_possible();
	int currX = null_list[0].first;
	int currY = null_list[0].second;
	for (int i = 0; i < probable_list[0].size(); i++) {
		if (toend)
			return;
		nMat = matrix;
		nMat[currX][currY] = probable_list[0][i];
		tryVariant(nMat, 1);
	}
}

int main() {
	start();
	int x;
	cin >> x;
	return 0;
}
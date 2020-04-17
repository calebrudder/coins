// Optimal Coin Game
// Caleb Rudder

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void main() {
	ifstream fin("coins.in");
	if (fin.is_open()) {
		ofstream fout("coins.out");

		int numberOfCoins;
		int coinValue;
		int answer;
		fin >> numberOfCoins;
		
		while (numberOfCoins > 0) {
			vector<vector<int>> coins(numberOfCoins, vector<int>(numberOfCoins, 0));
			vector<int> values;
			answer = 0;

			for (int row = 0; row < numberOfCoins; row++) {
				fin >> coinValue;
				values.push_back(coinValue);
				coins[row][row] = coinValue;
			}
			for (int diagonal = 0; diagonal <= numberOfCoins - 1; diagonal++) {
				for (int row = 0; row <= (numberOfCoins - (diagonal + 1)); row++) {

					if (diagonal == 0) {
						coins[row][row] = values[row];
					}
					if (diagonal == 1) {
						coins[row][row + 1] = max(values[row], values[row + 1]);
					}
					if (diagonal > 1) {
						int column = row + diagonal;
						int option1 = coins[row + 1][column - 1];
						int option2 = coins[row + 2][column];

						int choice1 = values[row] + min(option1, option2);
						
						option1 = coins[row][column - 2];
						option2 = coins[row + 1][column - 1];

						int choice2 = values[column] + min(option1, option2);

						coins[row][column] = max(choice1, choice2);

					}

				}
			}

			answer = coins[0][numberOfCoins - 1];
			fout << answer << endl;

			values.empty();
			coins.empty();
			fin >> numberOfCoins;
		}
		fout.close();
		fin.close();
	}
	else {
		cout << "Input file not found." << endl;
	}
}
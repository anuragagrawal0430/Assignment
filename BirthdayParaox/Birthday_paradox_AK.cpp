//============================================================================
// Name        : Birthday_paradox.cpp
// Author      : Akash Pateria
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<math.h>
using namespace std;

int main() {
	cout
			<< "\n\n=================================BIRTHDAY PARADOX=======================================\n\n";
	int n, N, choice;
	float noOfPairs;
	float oppChances, oppGroupChances, final;
	do {
		cout << "\nEnter number of people in room ::";
		cin >> n;

		cout << "\nEnter number of days in year ::";
		cin >> N;

		cout << "\nTotal number of possible pairs of " << n << " people ::";
		noOfPairs = (float) (n * (n - 1)) / 2;
		cout << noOfPairs << endl;

		cout << "\nChances of two people having different birthdays ::";
		oppChances = (1 - (float) (1.0 / N));
		cout << oppChances;

		cout << "\n\nPossibilty of different birthdays in consecutive " << n
				<< " people ::";
		oppGroupChances = pow(oppChances, noOfPairs);
		cout << oppGroupChances;

		cout << "\n\nFinal probability of Birthday Paradox ::";
		final = 1 - oppGroupChances;
		cout << final;

		cout << "\n\n\nWanna try again..???" << endl << "1. Yes\n2. No" << endl
				<< "Your Choice ::";
		cin >> choice;

		if (choice != 1 && choice != 2) {
			cout << "\n\nInvalid Choice";
			break;
		}
	} while (choice == 1);

	return 0;
}

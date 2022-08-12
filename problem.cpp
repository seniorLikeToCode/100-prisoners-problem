
// username: seniorBOTx (Abhishek Gupta [AKGEC,CSIT,2nd year])


/*
Problem Statement:

The 100 prisoners problem has different renditions in the literature. The following version is by Philippe Flajolet and Robert Sedgewick.


The director of a prison offers 100 death row prisoners, who are numbered from 1 to 100, a last chance. A room contains a cupboard with 100 drawers.
The director randomly puts one prisoner's number in each closed drawer. The prisoners enter the room, one after another. Each prisoner may open and
look into 50 drawers in any order. The drawers are closed again afterwards. If, during this search, every prisoner finds their number in one of the
drawers, all prisoners are pardoned. If just one prisoner does not find their number, all prisoners die. Before the first prisoner enters the room,
the prisoners may discuss strategy — but may not communicate once the first prisoner enters to look in the drawers. What is the prisoners' best strategy?

If every prisoner selects 50 drawers at random, the probability that a single prisoner finds their number is 50%. Therefore, the probability that all
prisoners find their numbers is the product of the single probabilities,
which is (1/2)^100 ≈ 0.0000000000000000000000000000008, a vanishingly small number. The situation appears hopeless.

Solution:

Surprisingly, there is a strategy that provides a survival probability of more than 30%. The key to success is that the prisoners do not have to decide
beforehand which drawers to open. Each prisoner can use the information gained from the contents of every drawer they already opened to decide which one
to open next. Another important observation is that this way the success of one prisoner is not independent of the success of the other prisoners,
because they all depend on the way the numbers are distributed.

To describe the strategy, not only the prisoners, but also the drawers, are numbered from 1 to 100; for example,
row by row starting with the top left drawer. The strategy is now as follows:

1. Each prisoner first opens the drawer labeled with their own number.
2. If this drawer contains their number, they are done and were successful.
3. Otherwise, the drawer contains the number of another prisoner, and they next open the drawer labeled with this number.
4. The prisoner repeats steps 2 and 3 until they find their own number, or fail because the number is not found in the first fifty opened drawers.


By starting with their own number, the prisoner guarantees they are on the unique permutation cycle (see below) of drawers containing their number.
The only question is whether this cycle is longer than fifty drawers.

*/
#include <bits/stdc++.h>
using namespace std;

const int N = 100;     // Number of prisoner

/*This function is populate the prisioner number and box number in random order*/
vector<int> populate() {
	vector<int> p(N + 1), freq(N + 1);
	for (int j = 1; j <= N; j++) {
		int x = abs(rand() * 999999937)  % N + 1;
		while (freq[x]) {
			if (x == N) x = 0;
			x++;
		}
		freq[x] = true;
		p[j] = x;
	}
	return p;
}

/*This function perform same as our logic in solutio section above [line:21] */
bool dfs(int root, vector<int>& box) {
	int mov = root;
	vector<int> freq(N + 1);
	for (int i = 1; i <= N / 2; i++) {
		freq[mov]++;
		if (freq[mov] > 1) {
			for (int i = 1; i <= N; i++) if (freq[i] == 0) mov = i;
		}
		if (root == box[mov]) return true;
		else mov = box[mov];
	}
	return false;
}

/*	This functions return probability
	p = favourable Case / Total case       */
double probability(double a, double b) {return a / b;}

void solve() {
	int tests = 100;     // Number of time experiment is perform
	int hit = 0;
	for (int test = 0; test < tests; test++) {
		vector<int> prisoner = populate();		// Populating Prisoner
		vector<int> box = populate();			// Populating Box

		vector<bool> pass(N, 0);
		for (int i = 0; i < N; i++) {
			pass[i] = dfs(i + 1, box);
		}
		if (count(pass.begin(), pass.end() , true) == N) hit++;
	}

	cout << probability(hit , tests) << endl;
}

/* This is Starting of our code */
int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cout.precision(5); cout << fixed;

	solve();
}

/*
Time Complexity: O(TotalExperiement * N);
*/

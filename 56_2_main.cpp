#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <random>

using namespace std;

class Person {
private:
	int state = 0;
public:
	string status_string() {
		if (state == 0) {
			return "susceptible";
		}
		else if (state == -1) {
			return "recovered";
		}
		else if (state == -2) {
			return "vaccinated";
		}
		else if (state > 0) {
			return "sick";
		}
	}

	void update() {
		if (state > 0) {
			state = state - 1;
			if (state == 0) {
				state = -1;
			}
		}
	}

	void infect(int n) {
		if (state == 0) {
			state = n;
		}
	}

	bool is_stable() {
		return state == -1;
	}

	void vaccinate() {
		if (state == 0) {
			state = -2;
		}
	}
};

class Population {
private:
	vector<Person> population;
	int n = 5;
public:
	Population(int npeople) {
		population = vector<Person>(npeople);
	}

	void random_infection() {
		int infected = round(((float)rand() / (float)RAND_MAX) * (population.size() - 1));
		population.at(infected).infect(n);
	}

	int count_infected() {
		int num = 0;
		for (int i = 0; i < population.size(); i++) {
			if (population.at(i).status_string() == "sick") {
				num++;
			}
		}
		return num;
	}

	void update() {
		for (int i = 0; i < population.size(); i++) {
			population.at(i).update();
		}
	}

	void display() {
		for (int i = 0; i < population.size(); i++) {
			if (population.at(i).status_string() == "sick") {
				cout << "+ ";
			}
			else if (population.at(i).status_string() == "susceptible") {
				cout << "? ";
			}
			else if (population.at(i).status_string() == "recovered") {
				cout << "- ";
			}
			else if (population.at(i).status_string() == "vaccinated") {
				cout << "v ";
			}
		}
		cout << endl;
	}
};

int main() {
	int npeople, step = 1;
	float p, v;
	srand(time(NULL));

	cout << "size of population?" << endl;
	cin >> npeople;

	Population test = Population(npeople);
	test.random_infection();

	while (test.count_infected() != 0) {
		cout << "day " << step << " number infected : " << test.count_infected() << endl;
		test.display();
		test.update();
		step++;
		if (test.count_infected() == 0) {
			cout << "day " << step << " number infected : " << test.count_infected() << endl;
			test.display();
			cout << "Disease ran for " << step << " days";
		}
	}
	return 0;
}
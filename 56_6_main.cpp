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

	float count_infected() {
		float num = 0;
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

	void random_transfer_probability(float p) {
		for (int i = 0; i < population.size(); i++) {
			int ri = 6;
			if (population.at(i).status_string() == "sick") {
				while (ri != 0) {
					int rand_per = round(((float)rand() / (float)RAND_MAX) * (population.size() - 1));
					if (population.at(rand_per).status_string() == "susceptible" && (float)rand() / (float)RAND_MAX < p) {
						population.at(rand_per).infect(n);
					}
					ri--;
				}
			}
		}
	}

	void vaccination_probability(float v) {
		for (int i = 0; i < population.size(); i++) {
			if ((float)rand() / (float)RAND_MAX < v) {
				population.at(i).vaccinate();
			}
		}
	}

	float count_susceptible() {
		float num = 0;
		for (int i = 0; i < population.size(); i++) {
			if (population.at(i).status_string() == "susceptible") {
				num++;
			}
		}
		return num;
	}
};

int main() {
	int npeople = 100000, step = 1;
	float p = 0, v = 0, totalSus, herd, herdProb;
	srand(time(NULL));

	/*cout << "size of population?" << endl;
	cin >> npeople;

	cout << "probability of transfer? (between 0 and 1)" << endl;
	cin >> p;

	cout << "probability of vaccination? (between 0 and 1)" << endl;
	cin >> v;*/

	for (p; p <= 1; p = p + .1) {
		v = 0;
		cout << "For probability of transmission " << p << endl;
		while (v <= 1) {
			step = 1;

			Population test = Population(npeople);
			test.random_infection();
			test.vaccination_probability(v);
			totalSus = test.count_susceptible();

			while (test.count_infected() != 0) {
				//cout << "day " << step << " number infected : " << test.count_infected() << endl;
				//test.display();
				test.random_transfer_probability(p);
				test.update();
				step++;
				if (test.count_infected() == 0) {
					//cout << "day " << step << " number infected : " << test.count_infected() << endl;
					//test.display();
					herd = test.count_susceptible();
					herdProb = herd / totalSus;
					cout << "Disease ran for " << step << " days at vaccination probability " << v << " herd prob "<< herdProb;
					if (herdProb > .95) {
						cout << " true herd" << endl;
					}
					else {
						cout << " no herd" << endl;
					}
				}
			}

			v = v + .1;
		}
		
	}
	return 0;
}
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

int main() {
	Person joe;
	int step = 1;
	for (; ; step++) {
		joe.update();
		joe.infect(5);
		cout << "On day " << step << ", Joe is "
			<< joe.status_string() << endl;
		if (joe.is_stable())
			break;
	}
	return 0;
}
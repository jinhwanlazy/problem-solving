#include <bits/stdc++.h> 
using namespace std;

class Sudoku {
public:
	bool isEmpty(int i) {
		return data_[i] == 0;
	}

	bool test(int i, int x) {
		int r = i / 9;
		int c = i % 9;
		for (int i = 0; i < 9; ++i) {
			if (data_[9*r+i] == x) {
				return false;
			}
			if (data_[9*i+c] == x) {
				return false;
			}
		}
		int br = 3 * (r / 3);
		int bc = 3 * (c / 3);
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				if (data_[(br+i)*9 + (bc+j)] == x) {
					return false;
				}
			}
		}
		return true;
	}

	int next_empty() const {
		for (int i = cursor_; i < 81; ++i) {
			if (data_[i] == 0)
			{
				return i;
			}
		}
		return -1;
	}
	
	void set(int i, int x) {
		//cout << "set: " << i << ", " << x << "\n";
		data_[i] = x;
		cursor_ = i;
	}

	int cursor() const {
		return cursor_;
	}

	friend istream& operator>>(istream& is, Sudoku& rhs) {
		for (int i = 0; i < 81; ++i) {
			is >> rhs.data_[i];
		}
		return is;
	}

	friend ostream& operator<<(ostream& os, const Sudoku& rhs) {
		for (int i = 0; i < 81; ++i) {
			os << rhs.data_[i];
			if (i % 9 == 8) {
				os << "\n";
			}
			else {
				os << " ";
			}
		}
		return os;
	}

private:
	int data_[81] = {0};
	int cursor_ = 0;
};

int solution() 
{
	return 0;
}

int main()
{
	Sudoku state;
	cin >> state;

	vector<Sudoku> stack = {state};
	while (!stack.empty()) {
		state = stack.back();
		stack.pop_back();
		
		int i = state.next_empty();
		if (i < 0) {
			break;
		}
		for (int x = 1; x <= 9; ++x) {
			if (state.test(i, x)) {
				state.set(i, x);
				stack.push_back(state);
			}
		}
	}
	cout << state << "\n";
	return 0;
}

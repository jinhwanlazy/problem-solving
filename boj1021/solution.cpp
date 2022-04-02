#include <bits/stdc++.h> 
using namespace std;

class JiminsQueue
{
public:
	JiminsQueue(int size) : Q_(size), op_count_(0) {
		for (int i = 0; i < size; ++i) {
			Q_[i] = i+1;
		}
	}

	void op1() {
		Q_.pop_front();
	}

	void op2() {
		Q_.push_back(Q_.front());
		Q_.pop_front();
		op_count_++;
	}

	void op3() {
		Q_.push_front(Q_.back());
		Q_.pop_back();
		op_count_++;
	}

	int find(int value) {
		if (Q_.front() == value) {
			return 0;
		}
		for (size_t i = 1; i < Q_.size(); ++i) {
			if (Q_[i] == value) {
				return i;
			}
			if (Q_[Q_.size()-i] == value) {
				return -i;
			}
		}
		throw;
	}

	int opCount() { return op_count_; }

private:
	std::deque<int> Q_;
	int op_count_;
};



int main()
{
	int N, M;
	cin >> N >> M;
	
	JiminsQueue Q(N);

	for (int i = 0; i < M; ++i) {
		int v;
		cin >> v;
		int distance = Q.find(v);
		while (distance > 0) {
			Q.op2();
			distance--;
		}
		while (distance < 0) {
			Q.op3();
			distance++;
		}
		Q.op1();
	}
	cout << Q.opCount() << "\n";
	return 0;
}

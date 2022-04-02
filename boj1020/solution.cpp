#include <bits/stdc++.h> 
using namespace std;

int SEGMENT_COUNT[10] = {
	6,
	2,
	5,
	5,
	4,
	5,
	6,
	3,
	7,
	5,
};

int count_seg(string s) {
	int res = 0;
	for (const auto& c : s) {
		res += SEGMENT_COUNT[c - '0'];
	}
	return res;
}

string solution(string input) {
	
	for (string candidate = input; candidate.back() < '9'; candidate.back() += 1) {
		if (SEGMENT_COUNT[candidate.back() + 1 - '0'] == SEGMENT_COUNT[input.back()-'0']) {
			candidate.back() += 1;
			return candidate;
		}
	}

	int N = input.size();
	vector<map<int, string>> memo(N);

	for (int j = 0; j < 10; ++j) {
		int seg_count = SEGMENT_COUNT[j];
		auto it = memo[0].find(seg_count);
		if (it == memo[0].end()) {
			memo[0].insert({seg_count, to_string(j)});
		}
	}

	for (int digit = 1; digit < N; ++digit) {
		for (uint64_t j = 0; j < 10; ++j) {
			uint64_t seg_count_this = SEGMENT_COUNT[j];
			for (const auto& prev : memo[digit-1]) {
				uint64_t seg_count_prev = prev.first;
				const string& n = prev.second;
				uint64_t seg_count = seg_count_this + seg_count_prev;
				auto it = memo[digit].find(seg_count);
				if (it == memo[digit].end()) {
					memo[digit].insert({seg_count, to_string(j) + n});
				}
			}
		}
	}

	uint64_t target_seg_count = count_seg(input);
	for (int digit = 0; digit < N; ++digit) {
		for (string input_before_digit = input.substr(0, N-digit-1);
				!input_before_digit.empty() && input_before_digit.back() <= '9';
				(!input_before_digit.empty() && input_before_digit.back()++)) {
			string input_after_digit = input.substr(N-digit-1, digit+1);
			int seg_count_before_digit = count_seg(input_before_digit);
			int seg_count_residual = target_seg_count - seg_count_before_digit;
			if (seg_count_residual <= 0) {
				continue;
			}
			auto it = memo[digit].find(seg_count_residual);
			if (it == memo[digit].end()) {
				continue;
			}
			string candidate(input_before_digit + it->second);
			if (candidate > input) {
				return candidate;
			}
		} 
	}

	auto it = memo[N-1].find(target_seg_count);
	if (it->second == input) {
		return "1" + input;
	}
	else {
		return "1" + it->second;
	}
}

int main()
{
	string input;
	cin >> input;

	string ans = solution(input);
	cout << stoull(ans) - stoull(input) << "\n";

	return 0;
}

#include <algorithm>
#include <iostream>
#include <string>

bool divisible(const std::string &number, int k) {
    int sum = 0;
    for (char c : number) sum += c - '0';
    int last = number.back() - '0';
    int tail = 0;
    int start = std::max(0, static_cast<int>(number.size()) - 3);
    for (int i = start; i < static_cast<int>(number.size()); ++i)
        tail = tail * 10 + number[i] - '0';
    switch (k) {
        case 1: return true;
        case 2: return last % 2 == 0;
        case 3: return sum % 3 == 0;
        case 4: return (tail % 100) % 4 == 0;
        case 5: return last == 0 || last == 5;
        case 6: return last % 2 == 0 && sum % 3 == 0;
        case 7: {
            // 1000 == -1 (mod 7): alternating sum of groups of three digits.
            int alternating = 0, sign = 1;
            int end = static_cast<int>(number.size());
            while (end > 0) {
                int begin = std::max(0, end - 3), group = 0;
                for (int i = begin; i < end; ++i) group = group * 10 + number[i] - '0';
                alternating += sign * group;
                sign = -sign;
                end = begin;
            }
            return alternating % 7 == 0;
        }
        case 8: return tail % 8 == 0;
        case 9: return sum % 9 == 0;
    }
    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int k;
    std::string s;
    std::cin >> k >> s;
    int answer = 0;
    const std::string digits = "0123456789";
    std::size_t begin = s.find_first_of(digits);
    while (begin != std::string::npos) {
        std::size_t end = s.find_first_not_of(digits, begin);
        if (end == std::string::npos) end = s.size();
        std::string number = s.substr(begin, end - begin);
        if (divisible(number, k)) answer = std::max(answer, static_cast<int>(number.size()));
        begin = s.find_first_of(digits, end);
    }
    std::cout << answer << '\n';
}

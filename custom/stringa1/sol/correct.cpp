#include <algorithm>
#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int k;
    std::string s;
    std::cin >> k >> s;
    int answer = static_cast<int>(s.size()) + 1;
    int length = 0, remainder = 0;
    for (std::size_t i = 0; i <= s.size(); ++i) {
        char c = i < s.size() ? s[i] : 'a';
        if ('0' <= c && c <= '9') {
            ++length;
            remainder = (remainder * 10 + c - '0') % k;
        } else {
            if (length > 0 && remainder == 0) answer = std::min(answer, length);
            length = 0;
            remainder = 0;
        }
    }
    std::cout << (answer > static_cast<int>(s.size()) ? 0 : answer) << '\n';
}

#include <iostream>
int main() {
    std::cout << 9900 << '\n';
    for (int n = 2; n <= 100; ++n)
        for (int s = 1; s <= 100; ++s)
            std::cout << n << ' ' << s << '\n';
}

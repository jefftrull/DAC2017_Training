#include <iostream>
#include <cstdint>

// A famous example of UB (or failure to handle it, rather)

// https://randomascii.wordpress.com/2014/04/17/buggy-security-guidance-from-apple/
// slightly tweaked to make it more obvious
void apple(int m, int n) {
    if (n <= 0 || m <= 0)
        return;                // not UB, just pointless to allocate
    size_t bytes = n * m;      // UB activated, potentially

    if (SIZE_MAX/n >= m) {     // the check - too late! gcc removes at -O2 and higher
        /* allocate "bytes" space */
        std::cout << "all good\n";
    } else {
        // this entire message disappears from the generated code
        std::cerr << "rejecting allocation of excessive size\n";
    }
}

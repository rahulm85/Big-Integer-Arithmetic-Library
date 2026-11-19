#define BIGINT_TEST_BUILD
#include <cassert>
#include <iostream>
#include "BigInt.cpp"

int main() {
    assert((BigInt("999") + BigInt("1")).toString() == "1000");
    assert((BigInt("-25") + BigInt("10")).toString() == "-15");
    assert((BigInt("-25") + BigInt("25")).toString() == "0");
    assert((BigInt("10") - BigInt("25")).toString() == "-15");
    assert((BigInt("-10") - BigInt("-25")).toString() == "15");
    assert((BigInt("123456789") * BigInt("987654321")).toString()
           == "121932631112635269");
    assert((BigInt("-12") * BigInt("13")).toString() == "-156");
    assert((BigInt("-12") * BigInt("-13")).toString() == "156");
    assert((BigInt("0000") * BigInt("-99")).toString() == "0");

    bool rejected = false;
    try { BigInt invalid("12x"); }
    catch (const std::invalid_argument&) { rejected = true; }
    assert(rejected);

    std::cout << "All BigInt tests passed.\n";
    return 0;
}

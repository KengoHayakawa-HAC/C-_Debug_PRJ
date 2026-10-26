#include "cases.hpp"
#include <string>

int main(int argc, char** argv) {
    console::setup();
    if (argc != 2) return 2;
    const std::string group = argv[1];
    if (group == "transfer") return run_transfer();
    if (group == "data") return run_data();
    return 2;
}

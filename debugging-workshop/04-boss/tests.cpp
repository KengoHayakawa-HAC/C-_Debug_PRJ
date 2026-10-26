#include "cases.hpp"
#include <string>

int main(int argc, char** argv) {
    console::setup();
    if (argc != 2) return 2;
    const std::string group = argv[1];
    if (group == "storage") return run_storage();
    if (group == "initialization") return run_initialization();
    return 2;
}

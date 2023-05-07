#include <iostream>
#include <flow/program_options.hpp>

int main(int argc, char* argv[]) {
    auto [desc, vm] = flow::program_options::parse(argc, argv);

    if (vm.count("help")) {
        std::cout << desc;
        return 0;
    }

    flow::program_options::process(vm);

    return 0;
}

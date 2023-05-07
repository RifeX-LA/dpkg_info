#pragma once

#include <fstream>
#include <boost/program_options.hpp>
#include <flow/program_options/detail/args_processing.hpp>

namespace flow::program_options {

    [[nodiscard]] auto parse(int argc, char* argv[]) {
        namespace po = boost::program_options;

        po::options_description desc("Options");
        desc.add_options()
                ("help,h", "Show help")
                ("ban,b", po::value<std::vector<std::string>>(), "Don't show packages of given publishers")
                ("output,o", po::value<std::string>(), "Write packages info to the given file");

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
        po::notify(vm);

        return std::pair(std::move(desc), std::move(vm));
    }

    template <typename R>
    void print_packages(const boost::program_options::variables_map& vm, R&& packages) {
        if (vm.count("output")) {
            auto path = vm["output"].as<std::string>();
            std::ofstream fout(path);
            detail::print_packages(fout, packages);
        }
        else {
            detail::print_packages(std::cout, packages);
        }
    }

    void process(const boost::program_options::variables_map& vm) {
        std::vector<std::string> banned_publishers;
        std::function<bool(std::string_view)> is_banned = [](std::string_view){return false;};

        if (vm.count("ban")) {
            banned_publishers = vm["ban"].as<std::vector<std::string>>();
            is_banned = [&](std::string_view publisher){
                return std::ranges::find(banned_publishers, dpkg::publisher_name(publisher)) != banned_publishers.end();
            };
        }
        const auto not_banned_publishers = [&](auto&& pair){return !is_banned(pair.first);};

        auto packages = dpkg::installed_packages();
        auto sorted_filtered_packages = detail::sorted_packages(packages) | std::views::filter(not_banned_publishers);
        print_packages(vm, sorted_filtered_packages);
    }

} // namespace flow::program_options

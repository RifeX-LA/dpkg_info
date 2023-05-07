#pragma once

#include <numeric>
#include <iostream>
#include <flow/dpkg.hpp>

namespace flow::program_options::detail {

    std::uintmax_t package_list_size(const dpkg::package_list& pkg_list) {
        static constexpr auto binary_op = [](auto&& init, auto&& pkg){return init + pkg.size;};
        return std::accumulate(pkg_list.begin(), pkg_list.end(), std::uintmax_t{}, binary_op);
    }

    auto sorted_packages(dpkg::packages& packages)  {
        static constexpr auto packages_number = [](auto&& pair){return pair.second.size();};

        std::vector<std::pair<std::string_view, dpkg::package_list>> v;
        v.reserve(packages.size());
        for (auto&& [key, value]: packages) {
            v.emplace_back(key, std::move(value));
        }
        std::ranges::sort(v, std::greater<>{}, packages_number);

        return v;
    }

    template <typename R>
    void print_packages(std::ostream& os, R&& packages) {
        for (auto&& [publisher, package_list] : packages) {
            os << fmt::format("Publisher: {} [{}]\n", publisher, package_list.size());
            os << fmt::format("Total packages size: {}\n\n", package_list_size(package_list));
            os << fmt::format("{}", fmt::join(package_list, "\n\n"));
            os << fmt::format("\n{:-<30}\n", "");
        }
    }

} // namespace flow::program_options::detail

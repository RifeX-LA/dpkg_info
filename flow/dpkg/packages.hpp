#pragma once

#include <map>
#include <ranges>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <boost/process.hpp>
#include <flow/dpkg/detail/packages.hpp>

namespace flow::dpkg {

    struct package {
        std::uintmax_t size;
        std::string name;

        package() noexcept : size(0), name() {}
        package(std::uintmax_t size, std::string name) : size(size), name(std::move(name)) {}

        friend std::ostream& operator<<(std::ostream& os, const package& pkg) {
            return os << fmt::format("Name: {}\nSize: {}", pkg.name, pkg.size);
        }
    };

    using package_list = std::vector<package>;
    using packages = std::unordered_map<std::string, package_list>;

    packages get_packages(std::string_view raw_packages_info) {
        static constexpr std::string_view delim = "\n\n";
        static constexpr auto not_empty = [](auto&& view){return !view.empty();};

        packages packages;
        auto packages_view = std::views::split(raw_packages_info, delim) | std::views::filter(not_empty);

        const auto add_package = [&](auto&& raw_package_info){
            auto [publisher, size, name] = detail::package_info(raw_package_info);
            packages[std::move(publisher)].emplace_back(size, std::move(name));
        };

        std::ranges::for_each(packages_view, add_package);

        return packages;
    }

    std::string publisher_name(std::string_view publisher) {
        auto name = detail::extract_value<detail::publisher_name_regex>(publisher);
        return name ? name.value() : std::string(publisher);
    }

    packages installed_packages() {
        std::future<std::string> output;
        boost::process::system("dpkg-query -s", boost::process::std_out > output);
        return get_packages(output.get());
    }

} // namespace flow::dpkg

template <>
struct fmt::formatter<flow::dpkg::package> : fmt::ostream_formatter {};

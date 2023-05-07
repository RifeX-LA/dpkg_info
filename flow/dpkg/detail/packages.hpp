#pragma once

#include <boost/lexical_cast.hpp>
#include <flow/dpkg/detail/regex.hpp>

namespace flow::dpkg::detail {

    template <typename R>
    auto package_info(R&& r) {
        auto name = extract_value<package_name_regex>(r).value_or("unknown");
        auto size = extract_value<package_size_regex>(r).value_or("0");
        auto publisher = extract_value<package_publisher_regex>(r).value_or("unknown");

        return std::tuple(std::move(publisher), boost::lexical_cast<std::uintmax_t>(size), std::move(name));
    }

} // namespace flow::dpkg::detail

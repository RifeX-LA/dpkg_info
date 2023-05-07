#pragma once

#include <optional>
#include <ctre.hpp>

namespace flow::dpkg::detail {

    template <CTRE_REGEX_INPUT_TYPE Regex, typename R>
    std::optional<std::string> extract_value(R&& r) noexcept {
        if (auto [match, value] = ctre::multiline_search<Regex>(std::forward<R>(r)); match) {
            return value.str();
        }
        return std::nullopt;
    }

    inline constexpr CTRE_REGEX_INPUT_TYPE package_name_regex = "^Package:\\s*(.+)$";
    inline constexpr CTRE_REGEX_INPUT_TYPE package_size_regex = "^Installed-Size:\\s*(.+)$";
    inline constexpr CTRE_REGEX_INPUT_TYPE package_publisher_regex = "^Original-Maintainer:\\s*(.+)$";
    inline constexpr CTRE_REGEX_INPUT_TYPE publisher_name_regex = "(.*)\\s+<.*>";

} // flow::dpkg::detail

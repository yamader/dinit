#pragma once

#include "context.hh"
#include "libs/argparse.hh"
#include "libs/nullstream.hh"
#include "libs/ranges.hh"
#include "libs/logger.hh"

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
// #include <format>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#include <sys/types.h>
#include <unistd.h>
#include <utility>
#include <vector>

using namespace std::literals;
using namespace yamad;

constexpr inline auto dinit_v_major{0};
constexpr inline auto dinit_v_minor{1};
constexpr inline auto dinit_v_patch{0};
// formatはよ〜
// constexpr inline std::string_view dinit_v_str{std::format("v{:d}.{:d}.{:d}",
//                                                           dinit_v_major,
//                                                           dinit_v_minor,
//                                                           dinit_v_patch)};
constexpr inline auto dinit_v_str{"v0.1.0"sv};

//

auto inittab(Context& ctx) -> void;

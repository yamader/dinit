#pragma once

#include "libs/argparse.hh"
#include "libs/nullstream.hh"
#include "libs/ranges.hh"

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
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

constexpr inline auto dinit_v_str = "v0.1.0"sv;

struct Context {
  bool debugging = false;
  bool has_color = true;
  bool is_init;

  // inittab
  std::filesystem::path inittab_path = "/etc/inittab";
};

// 💢💢💢💢
#include "libs/logger.hh"

auto inittab(Context& ctx) -> void;

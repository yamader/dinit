#pragma once

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

using namespace std::string_literals;

inline std::string dinit_v_str{"0.1.0"s};

// Basic data structure

struct Context {
  bool has_color;
  bool debugging;
};

// inittab

auto inittab(Context& ctx) -> void;

// Logger

auto c_err(Context& ctx, std::string msg) {
  if(ctx.has_color) {
    return "\e[1;31m" + msg + "\e[0m";
  } else {
    return msg;
  }
}

class Logger {
  std::ostream& out;
  std::stringstream ss;

 public:
  Logger(std::ostream& out): out{out} {
    *this << "dinit: "s;
  }
  ~Logger() { out << ss.str() << '\n'; }

  template<typename T>
  auto operator<<(T&& val) -> Logger& {
    ss << std::forward<T>(val);
    return *this;
  }
};

class Log {
  Context& ctx;
  Logger logger;

 public:
  Log(Context& ctx): ctx{ctx}, logger{std::cout} {}

  template<typename T>
  auto operator<<(T&& val) -> Log& {
    logger << std::forward<T>(val);
    return *this;
  }
};

class Err {
  Context& ctx;
  Logger logger;

 public:
  Err(Context& ctx): ctx{ctx}, logger{std::cerr} {
    *this << c_err(ctx, "error: "s);
  }

  template<typename T>
  auto operator<<(T&& val) -> Err& {
    logger << std::forward<T>(val);
    return *this;
  }
};

class Fatal {
  Context& ctx;
  Logger logger;

 public:
  Fatal(Context& ctx): ctx{ctx}, logger{std::cerr} {
    *this << c_err(ctx, "fatal: "s);
  }
  [[noreturn]] ~Fatal() {
    logger.~Logger();
    exit(1);
  }

  template<typename T>
  auto operator<<(T&& val) -> Fatal& {
    logger << std::forward<T>(val);
    return *this;
  }
};

class Debug {
  Context& ctx;
  Logger logger;

 public:
  Debug(Context& ctx): ctx{ctx}, logger{std::cout} {
    if(ctx.debugging) *this << "debug: "s;
  }

  template<typename T>
  auto operator<<(T&& val) -> Debug& {
    if(ctx.debugging) logger << std::forward<T>(val);
    return *this;
  }
};

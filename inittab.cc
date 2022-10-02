#include "dinit.hh"
#include "ranges.hh"

inline std::filesystem::path inittab_path{"/etc/inittab"s};

auto inittab(Context& ctx) -> void {
  if(!std::filesystem::exists(inittab_path)) {
    Err(ctx) << "/etc/inittab: no such file or directory"s;
    return;
  }

  Debug(ctx) << "parsing inittab"s;
  std::ifstream fs{inittab_path};
  std::string buf;

  while(std::getline(fs, buf)) {
    if(buf.empty() || buf.front() == '#') continue;
    if(std::count(buf.begin(), buf.end(), ':') < 3) {
      Err(ctx) << "invalid inittab row: "s << buf;
    }

    auto&& [id, runlevel, action, process] = [&]{
      auto split = buf | std::views::split(':');
      auto head = split | std::views::take(3) | std::views::transform(sv2sv) | to<std::vector>();
      auto tail = split | std::views::drop(3) | join_with(':') | to<std::vector>();
      return {head[0], head[1], head[2], tail};
    }();
  }
}

#include "common.hh"

auto inittab(Context& ctx) -> void {
  if(!std::filesystem::exists(ctx.inittab_path)) {
    Err(ctx) << "no such file or directory: " << ctx.inittab_path;
    return;
  }

  Debug(ctx) << "parsing inittab";
  std::ifstream fs{ctx.inittab_path};
  std::string buf;

  while(std::getline(fs, buf)) {
    if(buf.empty() || buf.front() == '#') continue;
    auto rng = buf | std::views::split(':');
    auto row = std::vector<std::string_view>(rng.begin(), rng.end());
    if(row.size() < 4) {
      Err(ctx) << "invalid inittab row: " << buf;
      continue;
    }

    id = row[0]
  }
}

#include "dinit.hh"

auto argparse(int argc, char** argv) -> Context {
  std::vector<std::string> args(argv, argv + argc);
  Context ctx;
  ctx.has_color = true;
  ctx.debugging = false;
  return ctx;
}

auto ver() -> void {
  std::cout << "v" + dinit_v_str << '\n';
}

auto help() -> void {
  ver();
  std::cout <<
    "\n"
    "Usage:\n"
    "  dinit [options]\n"
    "\n"
    "Options:\n"
    "  -h: show this help\n"
    "  -v: show version\n"
    "\n";
}

auto main(int argc, char** argv) -> int {
  Context ctx = argparse(argc, argv);

  Log(ctx) << "v" + dinit_v_str;

  bool isInit = getpid() == 1;
  if(isInit)  Log(ctx) << "running as init"s;
  else        Log(ctx) << "running NOT as init"s;

  inittab(ctx);

  Fatal(ctx) << "Oops!"s;
}

#include "common.hh"

auto disp_ver() -> void {
  std::cout << dinit_v_str << '\n';
}

auto disp_help() -> void {
  disp_ver();
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

auto argparse(Args& args) -> Context {
  Context ctx;
  if(args["verbose"].flag()) ctx.debugging = true;
  return ctx;
}

auto main(int argc, char* argv[]) -> int {
  Args args{argc, argv};
  args.def_flag("help", "--help", "-h");
  args.def_flag("ver", "--version", "-v");
  args.def_flag("verbose", "--verbose", "-V");
  args.parse();

  if(args["help"].flag()) {
    disp_help();
    return 0;
  }
  if(args["ver"].flag()) {
    disp_ver();
    return 0;
  }

  auto ctx = argparse(args);
  ctx.is_init = getpid() == 1;

  Log(ctx) << dinit_v_str;
  if(ctx.is_init) Log(ctx) << "running as init";
  else            Log(ctx) << "running NOT as init";

  inittab(ctx);

  Fatal(ctx) << "Oops!";
}

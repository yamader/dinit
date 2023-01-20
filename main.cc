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

auto context_factory(Args& args) -> Context {
  Context ctx;
  if(args["verbose"].flag()) ctx.debugging = true;
  ctx.is_init = getpid() == 1;
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

  auto ctx = context_factory(args); // NRVO
  if(ctx.is_init) Debug(ctx) << "running as init";
  else            Debug(ctx) << "running NOT as init";

  inittab(ctx);

  Fatal(ctx) << "Oops!";
}

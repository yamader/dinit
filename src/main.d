module dinit.main;

import std;
import core.sys.posix.unistd;

import dinit.inittab;
import dinit.utils;

enum helpMsg =
`USAGE: dinit [opts]

OPTS:
  -v, --verbose                 be verbose

      --inittab <path>          select inittab

  -h, --help                    show this help
  -V, --version                 show version`;

enum dinitVer = import("VERSION").strip;

auto main(string[] args) {
  bool verbose, showHelp, showVersion;
  string inittabPath = "/etc/inittab";

  try {
    getopt(args,
      std.getopt.config.caseSensitive,
      std.getopt.config.bundling,
      "verbose|v",  &verbose,
      "inittab",    &inittabPath,
      "help|h",     &showHelp,
      "version|V",  &showVersion);
  } catch(GetOptException e) {
    error(e.message);
    stderr.writeln('\n', helpMsg, '\n');
    return 1;
  }

  if(showHelp) {
    helpMsg.writeln;
    return 0;
  }
  if(showVersion) {
    dinitVer.writeln;
    return 0;
  }

  globalLogLevel(verbose ? LogLevel.all : LogLevel.warning);

  const pid = getpid;
  info("running as pid: ", pid);

  if(pid == 1) {
    info("executing inittab: ", inittabPath);
    inittab(inittabPath);
  }

  return 0;
}

module dinit.inittab;

import std;

auto inittab(string path) {
  auto f = File(path);
  scope(exit) f.close;

  string line;
  for(size_t i = 1; (line = f.readln.chomp) !is null; i++) {
    if(line.startsWith("#") || !line.strip.length) continue;

    const a = line.split(':');
    if(a.length < 4) {
      error("invalid inittab row: %s #%d".format(path, i));
      continue;
    }

    // 分割代入が欲しい……
    string id         = a[0];
    string runlevels  = a[1];
    string action     = a[2];
    string process    = a[3..$].join(':');

  }
}

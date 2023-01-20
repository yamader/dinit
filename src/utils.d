module dinit.utils;

import std;

// todo: ログの見た目をよくする

auto gray(string s) => "\33[1;30m" ~ s ~ "\33[0m";
auto red(string s) => "\33[1;31m" ~ s ~ "\33[0m";

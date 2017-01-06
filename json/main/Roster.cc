#include <iostream>
#include "gflags/gflags.h"
#include "json.hpp"

DEFINE_string(search, "", "Search the roster");

int main(int argc, char** argv) {
  gflags::SetUsageMessage("Roster of Heroes and Villains");
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  nlohmann::json roster;
  roster["heroes"] = { "Batman", "Robin" };
  roster["villains"] = { "Catwoman", "Joker", "Penguin" };

  if (FLAGS_search.length() > 0) {

    // search the heroes
    auto hero = std::find(std::begin(roster["heroes"]), std::end(roster["heroes"]), FLAGS_search);
    if (hero != std::end(roster["heroes"])) {
      std::cout << "hero found!" << std::endl;
      return 0;
    }

    // search the villains
    auto villain = std::find(std::begin(roster["villains"]), std::end(roster["villains"]), FLAGS_search);
    if (villain != std::end(roster["villains"])) {
      std::cout << "villain found!" << std::endl;
      return 0;
    }

    std::cout << FLAGS_search << " not found!" << std::endl;

  } else {
    std::cout << roster.dump(4) << std::endl;
  }

  return 0;
}

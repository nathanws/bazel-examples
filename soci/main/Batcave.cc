#include <iostream>
#include <string>
#include "gflags/gflags.h"
#include "soci/soci.h"
#include "soci/sqlite3/soci-sqlite3.h"

DEFINE_string(detain, "", "The villain to detain");
DEFINE_bool(list, false, "List detained villains");

int main(int argc, char** argv) {
  gflags::SetUsageMessage("Detain villains!");
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  // Create the SOCI session and set the database. The created database will be
  // located in the directory where the binary is ran.
  soci::session sql;
  sql.open(soci::sqlite3, "batcave.db");

  sql << "CREATE TABLE IF NOT EXISTS villains(name CHAR(50) PRIMARY KEY NOT NULL);";

  if (FLAGS_list) {
    soci::rowset<std::string> names = (sql.prepare << "SELECT * FROM villains;");

    // Keep track of how many villains there are so a "no villain" message can be displayed if needed
    int villainCount = 0;

    for (soci::rowset<std::string>::const_iterator it = names.begin(); it != names.end(); ++it) {
      std::cout << *it << std::endl;
      villainCount++;
    }

    if (villainCount == 0) {
      std::cout << "No villains detained in the Batcave" << std::endl;
    }

    return 0;
  }

  if (FLAGS_detain.length() > 0) {
    sql << "INSERT INTO villains(name) VALUES (:name);", soci::use(FLAGS_detain);

    int villainCount;
    sql << "SELECT COUNT(*) FROM villains;", soci::into(villainCount);

    std::cout << "There are " << villainCount << " villain(s) detained in the Batcave" << std::endl;
  }

  return 0;
}

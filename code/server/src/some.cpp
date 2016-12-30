#include "Logs/Logger.hh"

int main(void) {
  logs::getLogger().registerBasicsLogLevel();

  logs::getLogger()[logs::DEBUG] << "test";

  return 0;
}

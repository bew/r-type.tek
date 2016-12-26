#include "Logs/Logger.hh"

int main(void) {
  logs::logger.registerBasicsLogLevel();

  logs::logger[logs::DEBUG] << "test";

  return 0;
}

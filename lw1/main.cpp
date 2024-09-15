#include <iostream>

#define BOOST_TIMER_ENABLE_DEPRECATED
#include <boost/timer.hpp>
#include "libs/files-handler.h"


int main() {
  boost::timer timer;

  timer.restart();
  files::reverse_file_strings("../tests/WarAndPeace.txt");
  const double duration = timer.elapsed();

  std::cout << "Время: " << duration << std::endl;
  return 0;
}

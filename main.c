#include "program.h"
#include "tests.h"

#define MODE PRODUCTION
// mode can be production or release

int main(void) {
#if MODE == PRODUCTION
  (void)run_tests();
#endif
  //(void)exec();
  return 0;
}
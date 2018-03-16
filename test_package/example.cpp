#include <iostream>
#include <sstream>
#include <xmscore/misc/XmConst.h>

int main() {
  std::stringstream ss;

  ss << "Lowest XM UINT: " << xms::XM_UINT_LOWEST << std::endl;
  ss << "Highest XM UINT: " << xms::XM_UINT_HIGHEST << std::endl;
  ss << "Middlest XM UINT: " << xms::XM_UINT_HIGHEST / 2 << std::endl;

  std::cout << ss.str() << std::endl;
}

#include "xwapplication.hh"
#include "xwcontext.hh"

using namespace xw;

application::application() {}

application::~application() {}

specification application::parse() {
  specification methods;
  rpc_parse_context ctx(&methods);
  std::string err;

  try {
    picojson::_parse(ctx, std::istream_iterator<char>(std::cin),
                     std::istream_iterator<char>(), &err);
  } catch (std::runtime_error const& e) {
    std::cerr << "parse error: " << e.what() << std::endl;
  }

  if (!err.empty()) {
    std::cerr << err << std::endl;
  }

  return methods;
}

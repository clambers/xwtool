/**
 * Copyright (C) 2015 Chris Lamberson <clamberson@gmail.com>.
 *
 * This file is part of XWtool.
 *
 * XWtool is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XWtool is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with XWtool. If not, see <http://www.gnu.org/licenses/>.
 */

#include "xwutil.hh"
#include <iostream>

using namespace xw;

formatter::formatter(std::ostream& o) : out(o.rdbuf()) {}

formatter::~formatter() {}

js_globals::js_globals(std::ostream& o) : formatter(o) {
  out
    << "var callbacks = {" << std::endl
    << "  nextId: 0," << std::endl
    << "  handlers: {}," << std::endl
    << "  key: \"id\"," << std::endl
    << "  setup: function(cb) {" << std::endl
    << "    var id = ++this.nextId;" << std::endl
    << "    this.handlers[id] = cb;" << std::endl
    << "    return id;" << std::endl
    << "  }," << std::endl
    << "  dispatch: function(response) {" << std::endl
    << "    var id = response[this.key];" << std::endl
    << "    var handler = this.handlers[id];" << std::endl
    << "    handler(response.result);" << std::endl
    << "  }" << std::endl
    << "};" << std::endl
    << "function postMessage(id, msg) {" << std::endl
    << "  msg.jsonrpc = \"2.0\";" << std::endl
    << "  if (id !== undefined && id !== null) {" << std::endl
    << "    msg[callbacks.key] = id;" << std::endl
    << "  }" << std::endl
    << "  extension.postMessage(JSON.stringify(msg));" << std::endl
    << "}" << std::endl
    << "extension.setMessageListener(function(msg) {" << std::endl
    << "  var res = JSON.parse(msg)" << std::endl
    << "  callbacks.dispatch(res);" << std::endl
    << "});" << std::endl
    << std::endl;
}

js_globals::~js_globals() {}

js_methods::js_methods(std::ostream& o, specification const& s)
  : formatter(o) {
  for (auto spec : s) {
    spec.dump(out);
  }
}

js_methods::~js_methods() {}

include_guard::include_guard(std::ostream& o, std::string const& s)
  : formatter(o) {
  out
    << "#ifndef " << s << std::endl
    << "#define " << s << std::endl
    << std::endl;
}

include_guard::~include_guard() {
  out << "#endif" << std::endl;
}

comment::comment(std::ostream& o, std::initializer_list<std::string> cs)
  : formatter(o) {
  out << "/**" << std::endl;
  for (auto c : cs) {
    out << " * " << c << std::endl;
  }
  out << " */" << std::endl << std::endl;
}

comment::~comment() {}

cpp_include::cpp_include(std::ostream& o,
                         std::initializer_list<std::string> il)
  : formatter(o) {
  for (auto s : il) {
    out << "#include <" << s << ">" << std::endl;
  }
  out << std::endl;
}

cpp_include::~cpp_include() {}

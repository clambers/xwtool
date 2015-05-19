#ifndef XW_UTIL_HH
#define XW_UTIL_HH

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

#include "xwspec.hh"
#include "picojson.h"
#include <string>
#include <initializer_list>
#include <ostream>
#include <iterator>

namespace xw {
  template<typename> struct typestr {
    static char const* js();
  };

#define IS(x,y)                                 \
  template<> struct typestr<x> {                \
    static char const* js() { return #y; }      \
  };
  IS(picojson::array, Array)
  IS(picojson::object, Object)
  IS(double, Number)
  IS(bool, Boolean)
  IS(std::string, String)
#undef IS

  template <class T, class charT=char, class traits=std::char_traits<charT> >
  class signature_maker
    : public std::iterator<std::output_iterator_tag, void, void, void, void> {
  private:
    std::basic_ostream<charT,traits> *os;
    charT const* delimiter;
    bool first_elem;

  public:
    typedef charT char_type;
    typedef traits traits_type;
    typedef std::basic_ostream<charT, traits> ostream_type;

    signature_maker(ostream_type& s)
      : os(&s), delimiter(0), first_elem(true) {}

    signature_maker(ostream_type& s, charT const *d)
      : os(&s), delimiter(d), first_elem(true) {}

    signature_maker<T, charT, traits>& operator=(T const &item) {
      if (!first_elem && delimiter != 0)
        *os << delimiter;
      *os << item.first;
      first_elem = false;
      return *this;
    }

    signature_maker<T, charT, traits>& operator*() {
      return *this;
    }

    signature_maker<T, charT, traits>& operator++() {
      return *this;
    }

    signature_maker<T, charT, traits>& operator++(int) {
      return *this;
    }
  };

  template <class T, class charT=char, class traits=std::char_traits<charT> >
  class params_builder
    : public std::iterator<std::output_iterator_tag, void, void, void, void> {
  private:
    std::basic_ostream<charT,traits> *os;
    charT const* delimiter;
    bool first_elem;

  public:
    typedef charT char_type;
    typedef traits traits_type;
    typedef std::basic_ostream<charT, traits> ostream_type;

    params_builder(ostream_type& s)
      : os(&s), delimiter(0), first_elem(true) {}

    params_builder(ostream_type& s, charT const *d)
      : os(&s), delimiter(d), first_elem(true) {}

    params_builder<T, charT, traits>& operator=(T const &item) {
      if (!first_elem && delimiter != 0)
        *os << delimiter;
      *os << item.first << ": " << item.first << "," << std::endl;
      first_elem = false;
      return *this;
    }

    params_builder<T, charT, traits>& operator*() {
      return *this;
    }

    params_builder<T, charT, traits>& operator++() {
      return *this;
    }

    params_builder<T, charT, traits>& operator++(int) {
      return *this;
    }
  };

  class formatter {
  public:
    formatter(std::ostream&);
    virtual ~formatter();

  protected:
    std::ostream out;
  };

  struct js_globals : public formatter {
    js_globals(std::ostream&);
    virtual ~js_globals();
  };

  struct js_methods : public formatter {
    js_methods(std::ostream&, specification const&);
    virtual ~js_methods();
  };

  struct include_guard : public formatter {
    include_guard(std::ostream&, std::string const&);
    virtual ~include_guard();
  };

  struct comment : public formatter {
    comment(std::ostream&, std::initializer_list<std::string>);
    virtual ~comment();
  };

  struct cpp_include : public formatter {
    cpp_include(std::ostream&, std::initializer_list<std::string>);
    virtual ~cpp_include();
  };
}

#endif

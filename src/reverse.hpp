//
// Created by master on 7/2/19.
//

#ifndef MP3_GUI_REVERSE_HPP
#define MP3_GUI_REVERSE_HPP

#include <iterator>

template <typename T>
struct reversion_wrapper { T& iterable; };

template <typename T>
auto begin (reversion_wrapper<T> w) { return std::rbegin(w.iterable); }

template <typename T>
auto end (reversion_wrapper<T> w) { return std::rend(w.iterable); }

template <typename T>
reversion_wrapper<T> reverse (T&& iterable) { return { iterable }; }

#endif //MP3_GUI_REVERSE_HPP

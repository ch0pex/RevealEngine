
/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file bi_map.hpp
 * @version 1.0
 * @date 6/23/2025
 * @brief Short description
 *
 * Longer description
 */
#pragma once

#include "engine/core/data_types/primitive_types.hpp"

#include <iterator>
#include <ranges>
#include <span>
#include <stdexcept>
#include <type_traits>
#include <vector>


namespace rflect3d::core {

namespace detail {

/**
 * Iterates over a list of indices
 */
template<std::ranges::view InputView, std::integral IndexType>
  requires std::ranges::common_range<InputView>
class IndicesIterator {
public:
  // --- Type traits ---
  using value_type        = std::ranges::range_value_t<InputView>;
  using difference_type   = std::ranges::range_difference_t<InputView>;
  using reference         = std::ranges::range_reference_t<InputView>;
  using base_iterator     = std::ranges::iterator_t<InputView>;
  using iterator_category = std::input_iterator_tag;
  using iterator_concept  = std::input_iterator_tag;
  using indices_type      = std::span<IndexType>;

  IndicesIterator() = default;

  IndicesIterator(base_iterator begin, base_iterator end, indices_type const indices, std::size_t const counter) :
    begin(begin), end(end), indices(indices), counter(counter) { }

  reference operator*() const {
    auto offset = begin + indices[counter];
    if (offset > end) {
      throw std::invalid_argument("Indices must be in range");
    }
    return *(offset);
  }

  IndicesIterator& operator++() {
    ++counter;
    return *this;
  }

  IndicesIterator operator++(int) {
    auto tmp = *this;
    ++(*this);
    return tmp;
  }

  friend bool operator==(IndicesIterator const& lhs, IndicesIterator const& rhs) { return lhs.counter == rhs.counter; }

private:
  base_iterator begin;
  base_iterator end;
  indices_type indices;
  std::size_t counter;
};

template<std::ranges::view InputView, std::integral IndexType>
  requires std::ranges::common_range<InputView>
class FilterIndicesView : std::ranges::view_interface<FilterIndicesView<InputView, IndexType>> {
public:
  using iterator     = IndicesIterator<InputView, IndexType>;
  using indices_type = std::span<IndexType>;

  FilterIndicesView() = default;

  constexpr FilterIndicesView(InputView input_range, indices_type const indices) :
    input_range(input_range), indices(indices) { }


  [[nodiscard]] constexpr iterator begin() const {
    return iterator {std::ranges::begin(input_range), std::ranges::end(input_range), indices, 0};
  }


  [[nodiscard]] constexpr iterator end() const {
    return iterator {std::ranges::end(input_range), std::ranges::end(input_range), indices, indices.size()};
  }

private:
  InputView input_range;
  indices_type indices;
};

template<typename R, typename Indices>
FilterIndicesView(R&&, std::span<Indices> const) -> FilterIndicesView<std::views::all_t<R>, Indices>;


template<std::ranges::contiguous_range Indices>
struct FilterIndicesClosure : std::ranges::range_adaptor_closure<FilterIndicesClosure<Indices>> {
  constexpr explicit FilterIndicesClosure(Indices const& indices) : indices(indices) { }

  template<std::ranges::viewable_range R>
  constexpr auto operator()(R&& r) const {
    return FilterIndicesView {std::forward<R>(r), std::span {indices}};
  }

  Indices const& indices;
};

struct FilterIndices {
  template<std::ranges::contiguous_range Indices>
  constexpr FilterIndicesClosure<Indices> operator()(Indices const& indices) const {
    return FilterIndicesClosure(indices);
  }
};

} // namespace detail

inline constexpr detail::FilterIndices filter_indices = detail::FilterIndices {};


} // namespace rflect3d::core

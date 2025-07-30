/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file common.h
 * @version 1.0
 * @date 21/06/2024
 * @brief Short description
 *
 * Generation and index identifiers
 *
 *  |----------------------32 bits ---------------------|
 *  |-----8 bits-----|-------------24 bits--------------|
 *  -----------------------------------------------------
 *  |  Generation    |              Index               |
 *  -----------------------------------------------------
 *
 *  Invalid Value: 0xFFFFFFFF
 *
 */

#pragma once


#include "engine/core/core.hpp"

#include <cassert>
#include <deque>
#include <limits>
#include <vector>


namespace rflect3d {


enum class generation_t : u8 { };
enum class id_t : u32 { };
enum class index_t : u32 { };

namespace id {

using underlying_type = u32;

constexpr id_t operator<<(id_t const id, u32 const integral) {
  return id_t {static_cast<underlying_type>(id) << integral};
}

constexpr id_t operator>>(id_t const id, u32 const integral) {
  return id_t {static_cast<underlying_type>(id) >> integral};
}

constexpr id_t operator~(id_t const id) { return id_t {~static_cast<underlying_type>(id)}; }

constexpr id_t operator&(id_t const lhs, id_t const rhs) {
  return id_t {static_cast<underlying_type>(lhs) & static_cast<underlying_type>(rhs)};
}

constexpr id_t operator-(id_t const lhs, id_t const rhs) {
  return id_t {static_cast<underlying_type>(lhs) - static_cast<underlying_type>(rhs)};
}

constexpr generation_t operator+(generation_t const lhs, generation_t const rhs) {
  return static_cast<generation_t>(static_cast<u8>(lhs) + static_cast<u8>(rhs));
}

constexpr generation_t operator-(generation_t const lhs, generation_t const rhs) {
  return static_cast<generation_t>(static_cast<u8>(lhs) + static_cast<u8>(rhs));
}

constexpr index_t operator+(index_t const lhs, index_t const rhs) {
  return static_cast<index_t>(static_cast<underlying_type>(lhs) + static_cast<underlying_type>(rhs));
}

constexpr index_t operator-(index_t const lhs, index_t const rhs) {
  return static_cast<index_t>(static_cast<underlying_type>(lhs) - static_cast<underlying_type>(rhs));
}

constexpr underlying_type generationBits {sizeof(generation_t) * 8};
constexpr underlying_type indexBits {(sizeof(id_t) * 8) - generationBits};
constexpr id_t generationMask {(id_t {1} << generationBits) - id_t {1}};
constexpr id_t indexMask {(id_t {1} << indexBits) - id_t {1}};
constexpr id_t invalid {~id_t {0}};
constexpr underlying_type maxFree {1024};
constexpr generation_t maxGeneration {(std::numeric_limits<generation_t>::max)()};

constexpr bool is_valid(id_t const id) { return id != invalid; }

constexpr index_t index(id_t const id) { return static_cast<index_t>(id & indexMask); }

constexpr generation_t generation(id_t const id) { return static_cast<generation_t>(id >> indexBits & generationMask); }

inline id_t operator|(index_t lhs, id_t id) {
  return id_t {static_cast<underlying_type>(lhs) | static_cast<underlying_type>(id)};
}

constexpr id_t new_generation(id_t const idx) {
  auto const gen = static_cast<id_t>(generation(idx) + generation_t {1});
  return index(idx) | (gen << indexBits);
}

constexpr id_t new_generation(id_t const idx, generation_t generation) {
  auto const gen = static_cast<id_t>(generation);
  return index(idx) | (gen << indexBits);
}

class Factory {
public:
  Factory() = default;

  [[nodiscard]] bool useFree() const { return (free_indices_.size() > id::maxFree); }

  [[nodiscard]] u32 freeCount() const { return free_indices_.size(); }

  index_t back() { return owner_idx_.back(); }

  [[nodiscard]] index_t mapped(id_t const id) const { }

  [[nodiscard]] bool isAlive(id_t const id) const { }

  id_t newId(index_t const index) { }

  void remove(id_t const id) { }

private:
  std::vector<generation_t> generations_;
  std::deque<index_t> free_indices_;
  std::vector<index_t> mapped_idx_; // mappedIdx[componentId] -> component index
  core::vector<index_t> owner_idx_; // ownerIds[dataIndex] -> component index
};

} // namespace id

} // namespace rflect3d

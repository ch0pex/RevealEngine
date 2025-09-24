/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file components.hpp
 * @version 1.0
 * @date 3/14/2025
 * @brief Short description
 *
 * Editor UI components utilities
 */

#include "components.hpp"

namespace rflect3d::ui::utl {

auto open_file_dialog() -> std::optional<std::string> {
#ifdef WIN32
  OPENFILENAME ofn;
  std::array<char, 260> sz_file;
  ZeroMemory(&ofn, sizeof(ofn));
  ofn.lStructSize     = sizeof(ofn);
  ofn.hwndOwner       = nullptr;
  ofn.lpstrFile       = sz_file.data();
  ofn.lpstrFile[0]    = '\0';
  ofn.nMaxFile        = sizeof(sz_file) / sizeof(char);
  ofn.lpstrFilter     = "All\0*.*\0Text\0*.TXT\0";
  ofn.nFilterIndex    = 1;
  ofn.lpstrFileTitle  = nullptr;
  ofn.nMaxFileTitle   = 0;
  ofn.lpstrInitialDir = nullptr;
  ofn.Flags           = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

  // Abre el diálogo de archivo
  if (GetOpenFileName(&ofn) != TRUE) {
    LOG_ERROR("Error opening file: " << ofn.lpstrFile;
    return std::nullopt;
  }

  LOG_INFO("selected file: {}", ofn.lpstrFile);
  return ofn.lpstrFile;
#endif
  // TODO
  return std::nullopt;
}


} // namespace rflect3d::ui::utl

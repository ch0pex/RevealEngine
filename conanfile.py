import os
from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.files import copy

required_conan_version = ">=2.0.15"


class rflect3dConan(ConanFile):
    name = "RevealEngine"
    version = "0.1"
    package_type = "application"

    license = "MIT"
    author = "Álvaro Cabrera Barrio (alvcabre@pa.uc3m.es)"
    url = "https://github.com/ch0pex/RevealEngine"
    topics = ("graphics", "engine", "high performance", "real-time", "generic-programming")

    settings = "os", "arch", "compiler", "build_type"
    exports_sources = "CMakeLists.txt", "src/*"

    default_options = {
        "glew/*:shared": False
    }

    def layout(self):
        cmake_layout(self)
        # os_ = str(self.settings.os).lower()
        # build_type_ = str(self.settings.build_type).lower()
        # self.folders.build = os.path.join("build", f"{os_}-{build_type_}")
        # if os_ == "windows":
        #     self.folders.generators = os.path.join("build", f"{os_}", "generators")
        # else:
        #     self.folders.generators = os.path.join("build", f"{os_}-{build_type_}", "generators")

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

        # copo
        imgui_folder = self.dependencies["imgui/1.91.8-docking"].package_folder
        copy(self, "*", os.path.join(imgui_folder, "res", "bindings"),
             os.path.join(self.source_folder, "src", "engine", "extern", "imgui"))

    def requirements(self):
        self.requires("quill/10.0.1")
        self.requires("imgui/1.91.8-docking")
        self.requires("glfw/3.4")
        self.requires("glew/2.2.0")
        self.requires("vulkan-loader/1.4.309.0")
        self.requires("tomlplusplus/3.4.0")

    def build_requirements(self):
        self.test_requires("doctest/2.4.11")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    # def package(self):
    #     exe_name = "RevealEngine.exe" if self.settings.os == "Windows" else "RevealEngine"
    #     src_bin_dir = os.path.join(self.build_folder, "bin")
    #     dst_bin_dir = os.path.join(self.package_folder, "bin")
    #
    #     copy(self, exe_name, src=src_bin_dir, dst=dst_bin_dir, keep_path=False)
    #
    #     # copy(self, "*.hpp", src=os.path.join(self.source_folder, "src", "include"),
    #     #      dst=os.path.join(self.package_folder, "include"), keep_path=True)
    #
    # def package_info(self):
    #     self.cpp_info.bindirs = ["bin"]
    #     self.cpp_info.libdirs = []  # No hay libs
    #     self.cpp_info.includedirs = []

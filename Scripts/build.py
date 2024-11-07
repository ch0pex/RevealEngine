
import click
import os
import subprocess

@click.command()
@click.option('--build', default='Debug', help='Tipo de build: Debug o Release.')
@click.option('--cmake', default='false', help='Re compile whole project')
@click.option('--run', default='false', help='Run after building')
def build(build, cmake, run):

    build_type = build.lower()

    compiler_path = "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.40.33807/bin/Hostx64/x64/cl.exe"
    compile_command = f'cmake -DCMAKE_BUILD_TYPE={build_type} -DCMAKE_SHARED_LIBRARY_LINK_C_FLAGS="" -DCMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS="" -DCMAKE_CXX_COMPILER="{compiler_path}" -DCMAKE_MAKE_PROGRAM="C:/Program Files/JetBrains/CLion 2024.1.3/bin/ninja/win/x64/ninja.exe" -G Ninja -DIMGUI=1 -S C:/Alvaro/Universidad/RevealEngine -B C:/Alvaro/Universidad/RevealEngine/build/{build_type}'
    compile_command2 = f'cmake --build C:/Alvaro/Universidad/RevealEngine/build/debug --target RevealEngine -j 14'

        

    # Ejecutar el comando de compilación
    try:
        if (cmake):
             subprocess.run(compile_command, check=True, shell=True)
        subprocess.run(compile_command2, check=True, shell=True)
        # click.echo(f'Build completado en modo {build_type}. Output: {output}')
    except subprocess.CalledProcessError as e:
        click.echo(f'Error durante la compilación: {e}')
        exit(1)

if __name__ == '__main__':
    # TODO
    build()

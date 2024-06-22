#!/usr/bin/env python3

################################ CONFIGURATION ################################

# Files that should persist in the template directory (as POSIX-formatted paths)
keep_files = [
    "include/liblvgl/lv_conf.h",
    "include/liblvgl/lv_conf.old.h",
    "include/liblvgl/llemu.h",
    "include/liblvgl/llemu.hpp",
    "include/liblvgl/font/lv_font.h",
    "src/liblvgl/display.c",
    "src/liblvgl/llemu.c",
    "src/liblvgl/llemu.cpp",
    "src/liblvgl/lv_fonts/pros_font_dejavu_mono_10.c",
    "src/liblvgl/lv_fonts/pros_font_dejavu_mono_18.c",
    "src/liblvgl/lv_fonts/pros_font_dejavu_mono_30.c",
    "src/liblvgl/lv_fonts/pros_font_dejavu_mono_40.c",
]

# URI to LVGL's source
lvgl_repo = "https://github.com/lvgl/lvgl.git"

############################# END OF CONFIGURATION #############################

import subprocess
from pathlib import Path
from argparse import ArgumentParser
from os import chmod
import stat
import shutil
import re

WARN_COLOR = "\033[1;33m"
ERR_COLOR = "\033[0;31m"
STEP_COLOR = "\033[1;37m"
MSG_COLOR = "\033[0;37m"
NO_COLOR = "\033[0m"


def warn(message):
    print(f"{WARN_COLOR}WARNING: {MSG_COLOR}{message}{NO_COLOR}")


def error(message):
    print(f"{ERR_COLOR}ERROR: {MSG_COLOR}{message}{NO_COLOR}")


def step(message):
    print(f"{STEP_COLOR}- {message} -{NO_COLOR}")


def onexc_chmod(retry, path, err):
    chmod(path, stat.S_IWUSR)
    try:
        retry(path)
    except Exception as err:
        error(f"Failed to rmtree with exception: {err}")


def clone(branch):
    if Path("lvgl/").exists():
        print("lvgl directory exists, attempting to remove before cloning...")
        shutil.rmtree("lvgl/", onexc=onexc_chmod)

    sub_proc = subprocess.Popen(
        f"git clone -b {branch} {lvgl_repo} --recursive",
        shell=True,
    )
    if sub_proc.wait() != 0:
        error("Clone failed, exiting...")
        exit(1)


def clean_template_dir():
    print("Creating temp directory...")
    Path("temp").mkdir(exist_ok=True)

    print("Copying whitelisted files to temp directory...")
    for file in keep_files:
        if not Path(file).exists():
            warn(f'Whitelisted file "{file}" does not exist')
            keep_files.remove(file)
            continue
        output = Path(f"temp/{file}")
        output.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy(file, output)

    print("Removing template files...")
    shutil.rmtree("include/liblvgl")
    shutil.rmtree("src/liblvgl")

    print("Copying whitelisted files back to template directories...")
    for file in keep_files:
        output = Path(file)
        output.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy(f"temp/{file}", file)

    print("Removing temp directory...")
    shutil.rmtree("temp")


def copy_lvgl_files():
    print("Getting lvgl files...")
    lvgl_src = Path("lvgl/src").resolve()
    header_files = list(lvgl_src.rglob("**/*.h"))
    source_files = list(lvgl_src.rglob("**/*.c"))
    files = header_files + source_files

    print("Copying header and source files to respective directories...")
    for file in files:
        if file in header_files:
            new_loc = Path(f"include/liblvgl/{file.relative_to(lvgl_src)}")
        elif file in source_files:
            new_loc = Path(f"src/liblvgl/{file.relative_to(lvgl_src)}")

        if new_loc.as_posix() in keep_files:
            print(f"Skipped overwriting whitelisted file at {new_loc}")
            continue

        new_loc.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy(file, new_loc)
        fix_includes(new_loc)

    print("Swapping the proxy lvgl.h file with the full file...")
    Path("include/liblvgl/lvgl.h").unlink(missing_ok=True)
    shutil.copy("lvgl/lvgl.h", "include/liblvgl/lvgl.h")
    fix_includes("include/liblvgl/lvgl.h")

    print("Attempting to remove lvgl source...")
    shutil.rmtree("lvgl/", onexc=onexc_chmod)


def fix_includes(file_path):
    def resolve_include_path(match):
        file = Path(file_path)
        include_path = match.group(1)
        resolved_path = file.parent.joinpath(include_path).resolve()

        source_dir = Path.cwd().joinpath("src/")
        include_dir = Path.cwd().joinpath("include/")

        if resolved_path.is_relative_to(source_dir):
            relative_path = resolved_path.relative_to(source_dir)
        elif resolved_path.is_relative_to(include_dir):
            relative_path = resolved_path.relative_to(include_dir)
        else:
            warn(
                f'File "{file}" includes file "{include_path}",'
                + " which is outside of the src or include directory."
                + " Manual editing may be required."
            )
            relative_path = include_path

        return f'#include "{relative_path}"'

    with open(file_path, "r", encoding="utf-8") as file:
        data = file.read()
        data = re.sub(r"#include \"((?:\.\./)+.*\.h)\"", resolve_include_path, data)
        data = re.sub(r"#include \"(src/|lvgl/)", '#include "liblvgl/', data)
        data = re.sub(
            r"(?<!LV_LVGL_H_INCLUDE_SIMPLE\n)(?:^[ \t]*(#include \"lvgl.h\")$)",
            '#include "liblvgl/lvgl.h"',
            data,
            flags=re.M,
        )

    with open(file_path, "w", encoding="utf-8") as file:
        file.write(data)


def main():
    parser = ArgumentParser(
        prog="./update.py",
        description="A script to automatically update liblvgl from lvgl",
    )
    parser.add_argument(
        "branch",
        type=str,
        help="branch to clone from lvgl's git repository",
    )
    parser.add_argument(
        "-y",
        "--yes",
        action="store_true",
        help="ignore initial warning",
    )
    args = parser.parse_args()

    if not args.yes:
        warn(
            "Local changes may be deleted by this script."
            + " If you have made any changes, you should exit this script to"
            + " stash or commit them now."
        )

        print(
            "The following liblvgl files will not be modified:\n  "
            + "\n  ".join(keep_files)
        )

        input("Press any key to continue...")

    step("Clone LVGL")
    clone(args.branch)

    step("Remove old liblvgl files")
    clean_template_dir()

    step("Copy updated files")
    copy_lvgl_files()


if __name__ == "__main__":
    main()

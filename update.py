#!/usr/bin/env python3

import glob
import subprocess
import os
from pathlib import Path
import shutil
import re

# Files that should persist in the template directory
keep_files = [
	"include/liblvgl/lv_conf.h",
	"include/liblvgl/lv_conf.old.h", 
	"include/liblvgl/llemu.h",
	"include/liblvgl/llemu.hpp",
	"src/liblvgl/display.c",
	"src/liblvgl/llemu.c",
	"src/liblvgl/llemu.cpp",
	"src/liblvgl/lv_fonts/pros_font_dejavu_mono_10.c",
	"src/liblvgl/lv_fonts/pros_font_dejavu_mono_18.c",
	"src/liblvgl/lv_fonts/pros_font_dejavu_mono_30.c",
	"src/liblvgl/lv_fonts/pros_font_dejavu_mono_40.c",
]

# TODO: Version checker
# TODO: Includes fixer
# TODO: Better output

def clone(branch):
	if type(branch) != str:
		raise Exception("Parameter 'branch' should be a string!")
	
	sub_proc = subprocess.Popen(f"git clone -b {branch} https://github.com/lvgl/lvgl.git --recursive", 
							 	stdout=subprocess.PIPE, 
							 	stderr=subprocess.PIPE, 
							 	shell=True)
	sub_proc.wait()

def clean_template_dir():
	if not os.path.exists("temp"): 
		os.mkdir("temp")
	
	for file in keep_files:
		output = f"temp/{file}"
		os.makedirs(os.path.dirname(output), exist_ok=True)
		shutil.copy(file, output)

	shutil.rmtree("include/liblvgl")
	shutil.rmtree("src/liblvgl")

	for file in keep_files:
		os.makedirs(os.path.dirname(file), exist_ok=True)
		shutil.copy(f"temp/{file}", file)
	
	shutil.rmtree("temp")

def copy_lvgl_files():
	lvgl_src = Path("lvgl/src").resolve()
	header_files = glob.glob("**/*.h", recursive=True, root_dir=lvgl_src)
	source_files = glob.glob("**/*.c", recursive=True, root_dir=lvgl_src)

	for file in header_files:
		os.makedirs(os.path.dirname(f"include/liblvgl/{file}"), exist_ok=True)
		shutil.move(f"lvgl/src/{file}", f"include/liblvgl/{file}")
		fix_includes(Path(f"include/liblvgl/{file}").resolve())

	for file in source_files:
		os.makedirs(os.path.dirname(f"src/liblvgl/{file}"), exist_ok=True)
		shutil.move(f"lvgl/src/{file}", f"src/liblvgl/{file}")
		fix_includes(Path(f"src/liblvgl/{file}").resolve())
	
	os.remove("include/liblvgl/lvgl.h")
	shutil.move("lvgl/lvgl.h", "include/liblvgl/lvgl.h")
	fix_includes("include/liblvgl/lvgl.h")

	shutil.rmtree("lvgl/")

def fix_includes(file_path):
	def resolve_include_path(match):
		file_dir = Path(file_path).parent
		include_path = match.group(1)
		resolved_path = file_dir.joinpath(include_path).resolve()

		source_dir = Path.cwd().joinpath("src/")
		include_dir = Path.cwd().joinpath("include/")

		# FIXME: Some files break this, aren't relative to either path. How to handle this?
		if resolved_path.is_relative_to(source_dir):
			relative_path = resolved_path.relative_to()
		elif resolved_path.is_relative_to(include_dir):
			relative_path = resolved_path.relative_to(include_dir)

		return f'#include "{relative_path}"'
	

	with open(file_path) as file:
		data = file.read()
		data = re.sub(r"#include \"((?:\.\./)+.*\.h)", resolve_include_path, data)
		data = re.sub(r"#include \"(src/|lvgl/)", "#include \"liblvgl/", data)
	
	with open(file_path, "w") as file:
		file.write(data)

if __name__ == "__main__":
	clone("release/v8.4")
	clean_template_dir()
	copy_lvgl_files()

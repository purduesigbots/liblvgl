#!/usr/bin/env python3

import glob
import sys
import subprocess
import os
from pathlib import Path
import shutil

# Files that should persist in the template directory
keep_files = [
	"include/liblvgl/lv_conf.h",
	"include/liblvgl/lv_conf.old.h", 
	"include/liblvgl/llemu.h",
	"include/liblvgl/llemu.hpp",
	"src/liblvgl/display.c",
	"src/liblvgl/llemu.c",
	"src/liblvgl/llemu.cpp",
]

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

	for file in source_files:
		os.makedirs(os.path.dirname(f"src/liblvgl/{file}"), exist_ok=True)
		shutil.move(f"lvgl/src/{file}", f"src/liblvgl/{file}")

if __name__ == "__main__":
	clone("master")
	copy_lvgl_files()
	#clone("https://github.com/lvgl/lvgl.git", sys.argv[1])
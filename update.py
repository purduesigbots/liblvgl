#!/usr/bin/env python3

import glob
import sys
import subprocess
import os
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

def clone(repo, branch):
	if type(repo) != str:
		raise Exception("Parameter 'repo' should be a string!")
	if type(branch) != str:
		raise Exception("Parameter 'branch' should be a string!")
	
	sub_proc = subprocess.Popen(f"git clone {repo} --recursive", 
							 	stdout=subprocess.PIPE, 
							 	stderr=subprocess.PIPE, 
							 	shell=True)
	sub_proc.communicate("cd lvgl")
	sub_proc.communicate(f"git checkout {branch}")

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

if __name__ == "__main__":
	clean_template_dir()
	#clone("https://github.com/lvgl/lvgl.git", sys.argv[1])
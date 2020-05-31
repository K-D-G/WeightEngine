#This file contains python functions to automate long tasks
#Such as listing all of the files in subdirectories in order to add them to the makefile
import os

def list_files(root, return_arr=False):
    arr=[]
    for path, subdirs, files in os.walk(root):
        for name in files:
            if return_arr:
                arr.append(os.path.join(path, name))
            else:
                print(os.path.join(path, name))
    if return_arr:
        return arr

def make_file_list(root):
    files=list_files(root, return_arr=True)
    new_files=[]
    for i in range(len(files)):
        if (files[i][-2]=="." and files[i][-1]=="h") or (".DS_Store" in files[i]):
            pass
        else:
            new_files.append(files[i])
    for i in range(len(new_files)):
        new_files[i]=new_files[i].replace(".c", ".o")
        new_files[i]=new_files[i].replace(".cpp", ".o")
        new_files[i]=new_files[i].replace("src", "obj")
        print(new_files[i]+" \\")

#Add any function calls here
if __name__=='__main__':
    make_file_list("src/WeightEngine/external_libraries/Freetype/")

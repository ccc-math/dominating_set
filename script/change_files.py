import os
import argparse
import sys
from os.path import isfile, join

def read_graph(file_path):
    line_count = 0
    max_elements = 0
    try:
        with open(file_path, 'r') as file:
            for line in file:
                line_count += 1
                parts = line.strip().split()
                for n in parts:
                    max_elements = max(max_elements, int(n))
    except Exception as e:
        print(f"Error reading file {file_path}: {e}")
    return line_count,max_elements

def write_graph(string, output_path):
    try:
        with open(output_path,'r') as file:
            content=file.read()
        with open(output_path, 'w') as file:
            file.write(string+"\n"+content)
    except Exception as e:
        print(f"Error writing file {output_path}: {e}")


if __name__ == "__main__":
    path = os.path.join("../data/project_instances/")
    onlyfiles = [f for f in os.listdir(path) if isfile(join(path, f))]
    print(path+onlyfiles[0])
    for file in onlyfiles:
        m,n=read_graph(path+file)
        print("Instance :{} , N: {}, M:{}  \n".format(file,n,m))
        s="p ds "+str(n)+" "+str(m)
        write_graph(s,path+file)
        os.rename(path+file,path+"test_"+file)
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

def has_zero(file_path):
    found_zero = False
    count_l = 0
    try: 
        with open(file_path, 'r') as file:
            for line in file:
                count_l += 1
                parts = line.strip().split()
                for n in parts:
                    
                    if(n == "0"):
                        found_zero= True
    except Exception as e:
        print(f"Error reading file {file_path}: {e}")
    return found_zero

def write_graph(string, output_path):
    try:
        with open(output_path,'r') as file:
            content=file.read()
        with open(output_path, 'w') as file:
            file.write(string+"\n"+content)
    except Exception as e:
        print(f"Error writing file {output_path}: {e}")

def modify_all(path):
    onlyfiles = [f for f in os.listdir(path) if isfile(join(path, f))]
    print(path+onlyfiles[0])
    for file in onlyfiles:
        m,n=read_graph(path+file)
        print("Instance :{} , N: {}, M:{}  \n".format(file,n,m))
        s="p ds "+str(n)+" "+str(m)
        write_graph(s,path+file)
        os.rename(path+file,path+"test_"+file)

def off_set(path):
    if(has_zero(path)):
        try:
            # Open the file and read all lines
            with open(path, "r") as file:
                lines = file.readlines()

            # Modify the lines that contain the keyword
            with open(path, "w") as file:
                for line in lines:
                    if "p" in line:
                        replacement_text = ""
                        parts = line.strip().split()
                        
                        for n in range(len(parts)):
                            if(n==2):
                                replacement_text += str(int(parts[n])+1)+" "
                            else:
                                replacement_text += parts[n]+" "
                        
                        file.write(replacement_text + "\n")  # Replace the line
                    else:
                        file.write(line)  # Keep the original line
        except Exception as e:
            print(f"Error writing file {path}: {e}")
    else:
        try:
            # Open the file and read all lines
            with open(path, "r") as file:
                lines = file.readlines()

            # Modify the lines that contain the keyword
            with open(path, "w") as file:
                for line in lines:
                    if not "p" in line:
                        replacement_text = ""
                        parts = line.strip().split()
                        
                        for n in range(len(parts)):
                                replacement_text += str(int(parts[n])-1)+" "
                        file.write(replacement_text + "\n")  # Replace the line
                    else:
                        file.write(line)  # Keep the original line
        except Exception as e:
            print(f"Error writing file {path}: {e}")

if __name__ == "__main__":
    path = os.path.join("../data/")
    onlyfiles = [f for f in os.listdir(path) if isfile(join(path, f))]
    for file in onlyfiles:
        off_set(path+file)
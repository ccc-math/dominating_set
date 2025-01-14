import os
import csv
import argparse
import sys
import datetime
from os.path import isfile, join



def run_command(command):
    print(command)
    status = os.system(command)
    if status != 0:
        sys.exit(1)
    print()



if __name__ == "__main__":
    output_dir = "../benchmark/"
    input_dir = "../data/"
    benchmark_name = "test.csv"
    algorithm = "heap"
    command = "../bin/dom_set_main "
    input_files = [f for f in os.listdir(input_dir) if isfile(join(input_dir, f))]
    for files in input_files:
        with open(output_dir+benchmark_name, mode='r', newline='') as file:
            pass
        run_command(command+"-a "+algorithm+" -i "+input_dir+files+" -o "+output_dir+benchmark_name)

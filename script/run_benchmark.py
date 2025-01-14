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
    

    # Create the parser
    parser = argparse.ArgumentParser(description="A script with multiple arguments")

    # Add arguments
    parser.add_argument('--output_dir', help='Path to the input file',default='../benchmark/')
    parser.add_argument('--input_dir', help='Path to the output file', default='../data/')
    parser.add_argument('--algorithm', help='Algorithm to compute the benchmark', default='heap')
    parser.add_argument('--time-limit', help='Maximum time for computation', default='30')
    # Parse arguments
    args = parser.parse_args()


    output_dir = args.output_dir
    input_dir = args.input_dir
    algorithm = args.algorithm
    time_limit = args.time_limit
    benchmark_name = algorithm+".csv"
    command = "../bin/dom_set_main "
    with open(output_dir+benchmark_name, mode='w') as out_file:
            pass
    input_files = [f for f in os.listdir(input_dir) if isfile(join(input_dir, f))]
    for files in input_files:
        
        run_command(command+"-a "+algorithm+" -i "+input_dir+files+" -o "+output_dir+benchmark_name+" -t "+time_limit)

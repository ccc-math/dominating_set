import os
import csv
import argparse
import sys
import datetime


def run_command(command):
    print(command)
    status = os.system(command)
    if status != 0:
        sys.exit(1)
    print()


dominasting_set_solver = os.path.join(
        "install",
        "bin",
        "dominating_set_solver")

if __name__ == "__main__":

    parser = argparse.ArgumentParser(
            prog='run_benchmarks',
            usage='%(prog)s [options]')
    parser.add_argument(
            '--directory',
            help='benchmark directory',
            default="benchmark_results")
    parser.add_argument('--name', help='output directory', default=None)
    parser.add_argument('--options', help='options', default="")
    args = parser.parse_args()

    benchmark = args.benchmark
    options = args.options
    output_directory = os.path.join(args.directory, benchmark)
    if args.name:
        output_directory = os.path.join(output_directory, args.name)
    else:
        date = datetime.datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
        output_directory = os.path.join(output_directory, date)


        datacsv_path = os.path.join(
                "data",
                "rectangle",
                "data_roadef2018.csv")

        data_dir = os.path.dirname(os.path.realpath(datacsv_path))
        with open(datacsv_path, newline='') as csvfile:
            reader = csv.DictReader(csvfile)
            for row in reader:
                if args.sub and args.sub != row["Dataset"][-1]:
                    continue

                instance_path = os.path.join(
                        data_dir,
                        row["Path"])

                json_output_path = os.path.join(
                        output_directory,
                        row["Path"] + "_output.json")
                if not os.path.exists(os.path.dirname(json_output_path)):
                    os.makedirs(os.path.dirname(json_output_path))

                certificate_path = os.path.join(
                        output_directory,
                        row["Path"] + "_solution.csv")
                if not os.path.exists(os.path.dirname(certificate_path)):
                    os.makedirs(os.path.dirname(certificate_path))

                command = (
                        dom_set_main
                        + "  --input \"" + instance_path + "\""
                        #+ " --time-limit 3600"
                        #+ "  --output \"" + json_output_path + "\""
                        #+ " --certificate \"" + certificate_path + "\"")
                        + "--algorithm \"" )
                run_command(command)


    
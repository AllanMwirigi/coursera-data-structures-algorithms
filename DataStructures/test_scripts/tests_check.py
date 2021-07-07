import os 
import glob
from subprocess import Popen, PIPE, STDOUT
import argparse

def build_code():
    cpp_file = glob.glob("./*.cpp")[0]
    cpp_exe  = cpp_file.replace(".cpp", "")
    os.system("rm {}".format(cpp_exe)) # Build clean
    os.system("g++ -std=c++11 {} -o {}".format(cpp_file, cpp_exe)) # Build
    return cpp_exe

# def test_code(cpp_exe, args):
def test_code(args):
    # if not os.path.exists(cpp_exe):
    #     print("Executable not present")
    #     return
        
    display = args.display
    # tests_dir = "./tests/"
    tests_dir = os.getcwd()+'/test_utils/3_network_simulation/tests'
    tests_out_list = sorted(glob.glob(os.path.join(tests_dir, "*.a")))
    if args.end:
        tests_out_list=tests_out_list[:args.end]
    if args.start:
        tests_out_list=tests_out_list[args.start:]

    tests_inp_list = [f.replace(".a", "") for f in tests_out_list]
    num_files = len(tests_inp_list)

    for inp_file, out_file in zip(tests_inp_list, tests_out_list):
        finp = open(inp_file, 'r') 
        fout = open(out_file, 'r') 

        inp_content = finp.read() 
        out_content = fout.read() 

        # p = Popen(['python3'], stdout=PIPE, stdin=PIPE, stderr=PIPE)
        p = Popen(['python3', inp_file], stdout=PIPE, stdin=PIPE, stderr=PIPE)
        test_input = inp_content
        stdout_data = p.communicate(input=test_input.encode())[0]

        if stdout_data.decode().strip() == out_content.strip():
            if display == '1':
                print('----PASSED----')
                print('Input file : {}'.format(inp_file))
                print('Input:\n{}'.format(test_input.strip()))
                print('Output:\n{}\n'.format(out_content.strip()))
                pass 
        else:
            print('----FAILED----')
            print('Input file : {}'.format(inp_file))
            print('Input:\n{}'.format(test_input.strip()))
            print('Output of program:\n{}'.format(stdout_data.decode().strip()))
            print('Correct answer:\n{}'.format(out_content.strip())) 
            return 

    print('Passed All {} Test Cases.'.format(num_files))

    return

if __name__=='__main__':
    parser = argparse.ArgumentParser(description='Test code')
    # parser.add_argument('-d', '--display', default="0", type=str, help='Display each test case result')
    # parser.add_argument('-s', '--start',  default=None, type=int, help='Starting test case index')
    # parser.add_argument('-e', '--end',  default=None, type=int, help='Last test case index')
    # parser.add_argument('--only_build', action='store_true', help='Only building and no testing')
    parser.add_argument('-d', '--display', default="1", type=str, help='Display each test case result')
    parser.add_argument('-s', '--start',  default=None, type=int, help='Starting test case index')
    parser.add_argument('-e', '--end',  default=None, type=int, help='Last test case index')
    parser.add_argument('--only_build', action='store_true', help='Only building and no testing')

    args = parser.parse_args()

    # cpp_exe = build_code()

    if not args.only_build:
        # test_code(cpp_exe, args)
        test_code(args)
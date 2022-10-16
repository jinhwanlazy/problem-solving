import os
import abc
import json
import argparse
import subprocess
from glob import glob
from datetime import datetime

LANGUAGES = ['auto', 'py', 'cpp']
OUT_TYPES = ['str', 'float']

parser = argparse.ArgumentParser(description='Run tests for problems')
parser.add_argument('--problem', '-p', type=str, help='problem id')
parser.add_argument('--language', '-l', type=str, choices=LANGUAGES, 
        default='auto',
        help='select language to test. set auto to use the last modified one')
parser.add_argument('--output_type', '-o', type=str, choices=OUT_TYPES, 
        default='str', help='the method to compare output and answer')
parser.add_argument('--precision', type=float, default=1e-6)
parser.add_argument('--verbose', '-v', action='store_true')
parser.add_argument('--use_python2', action='store_true')

def make_red(s):
    return '\033[93m' + s + '\033[0m'


def make_green(s):
    return '\033[92m' + s + '\033[0m'

    
class Solution(metaclass=abc.ABCMeta):
    def __init__(self, filepath, *args, **kwargs):
        super().__init__()
        self.filepath = filepath
        self.verbose = kwargs.get('verbose', False)
        
    @abc.abstractmethod
    def build(self):
        raise NotImplementedError

    @abc.abstractmethod
    def execute(self, test_input):
        raise NotImplementedError

    @abc.abstractmethod
    def clean(self):
        raise NotImplementedError


class PySolution(Solution):
    def __init__(self, filepath, *args, **kwargs):
        super().__init__(filepath, *args, **kwargs)
        self.use_python2 = kwargs.get('use_python2', False)

    def build(self):
        pass

    def execute(self, sample):
        if self.use_python2:
            cmd = ['python2', self.filepath]
        else:
            cmd = ['python3', self.filepath]
        proc = subprocess.Popen(cmd, 
                stdin=subprocess.PIPE,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT)
        out, _ = proc.communicate(sample.input())
        return out

    def clean(self):
        None


class CppSolution(Solution):
    def __init__(self, filepath, *args, **kwargs):
        super().__init__(filepath, *args, **kwargs)
        self.exe_filepath = os.path.join(os.path.dirname(self.filepath), 'a.out')

    def build(self):
        start_time = datetime.now()
        cmd = ['g++-12', 
            '-std=c++20',
            '-Wall', 
            '-Weffc++',
            '-fdiagnostics-color=always', 
            '-I', '.misc/include', 
            self.filepath, 
            '-o', self.exe_filepath]
        res = subprocess.run(cmd, capture_output=True, text=True)
        print(res.stdout)
        print(res.stderr)
        if res.returncode != 0:
            raise Exception(f"Filed to execute command {cmd}")

        print(f"build {self.filepath} done - elapsed: {(datetime.now() - start_time)}")

    def execute(self, sample):
        cmd = [self.exe_filepath]
        proc = subprocess.Popen(cmd, 
                stdin=subprocess.PIPE,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE)
        out, err = proc.communicate(sample.input(), timeout=10)
        ret_code = proc.wait(timeout=10)
        if ret_code != 0:
            raise RuntimeError(f'solution returned wrong ret code: {ret_code}')
        if self.verbose and err:
            print(err.decode())
        return out

    def clean(self):
        os.remove(self.exe_filepath)


class TestSample(metaclass=abc.ABCMeta):
    def __init__(self, *args, **kwargs):
        super().__init__()
        self.output_type = kwargs.get('output_type', 'str')
        self.precision = kwargs.get('precision', 1e-6)

    @abc.abstractmethod
    def input(self):
        pass

    @abc.abstractmethod
    def ref_output(self):
        pass

    @abc.abstractmethod
    def validate(self, ans):
        pass

    def is_equal(self, a, b):
        if self.output_type == 'str':
            return a == b
        elif self.output_type == 'float':
            a = float(a.decode())
            b = float(b.decode())
            return abs(a - b) < self.precision
        else:
            raise NotImplementedError
            

class TxtSample(TestSample):
    def __init__(self, input_txt, output_txt, *args, **kwargs):
        super().__init__(self, *args, **kwargs)
        self.input_txt = input_txt
        self.output_txt = output_txt
        self.verbose = kwargs.get('verbose', False)

    def __repr__(self):
        return os.path.basename(self.input_txt)
    
    def input(self):
        with open(self.input_txt, 'rb') as f:
            return f.read()

    def ref_output(self):
        with open(self.output_txt, 'rb') as f:
            ref_lines = f.readlines()
        ref_lines = [l.strip() for l in ref_lines]
        return ref_lines

    def validate(self, ans):
        ans_lines = ans.split(b'\n')
        ans_lines = [l.strip() for l in ans_lines if l]

        ref_lines = self.ref_output()

        correct = True
        report = []
        for i, (a, b) in enumerate(zip(ans_lines, ref_lines)):
            correct &= self.is_equal(a, b)
        if self.verbose or not correct:
            report.append("Your answer: ")
            report.append(b'\n'.join(ans_lines).decode())
            report.append("Correct answer: ")
            report.append(b'\n'.join(ref_lines).decode())
        # report.append('CORRECT!' if correct else 'Wrong Answer')
        return correct, '\n'.join(report)


class TxtSampleWithoutOutput(TxtSample):
    def __init__(self, input_txt, output_txt=None, *args, **kwargs):
        super().__init__(self, output_txt, *args, **kwargs)
        self.input_txt = input_txt
        
    def ref_output(self):
        pass
    
    def validate(self, ans):
        report = []
        report.append("Your answer: ")
        report.append(ans.decode())
        return True, '\n'.join(report)


def find_samples(directory, *args, **kwargs):
    input_files = sorted(glob(os.path.join(directory, '*.in')))

    res = []
    for input_file in input_files:
        output_file = input_file.replace('.in', '.out')
        if not os.path.isfile(output_file):
            print('output not exist for sample input -', input_file)
            sample = TxtSampleWithoutOutput(input_file, None, *args, **kwargs)
        else:
            sample = TxtSample(input_file, output_file, *args, **kwargs)
        res.append(sample)
    return res


def create_solution(solution_filepath, *args, **kwargs):
    ext = os.path.splitext(solution_filepath)[-1]
    return {
            '.py': PySolution,
            '.cpp': CppSolution,
        }[ext](solution_filepath, *args, **kwargs)


def find_solution_file(directory, language):
    if language == 'auto':
        candidates = [os.path.join(directory, f'solution.{ext}') for ext in LANGUAGES]
        candidates = [f for f in candidates if os.path.isfile(f)]
        return max(candidates, key=os.path.getmtime)
    assert language in LANGUAGES
    filepath = os.path.join(directory, f'solution.{language}')
    assert os.path.isfile(filepath)
    return filepath

def find_settings_json(directory):
    settings_filepath = os.path.join(directory, 'settings.json')
    if not os.path.isfile(settings_filepath):
        return {}
    with open(settings_filepath, 'r') as f:
        return json.loads(f.read())


def run_test(problem, language, *args, **kwargs):
    directory = str(problem)
    kwargs.update(find_settings_json(directory))

    solution_filepath = find_solution_file(directory, language)
    solution = create_solution(solution_filepath, *args, **kwargs)
    solution.build()
    
    samples = find_samples(directory, *args, **kwargs)
    for sample in samples:
        start_time = datetime.now()
        ans = solution.execute(sample)
        elapsed = datetime.now() - start_time
        res, report = sample.validate(ans)
        if res:
            print(make_green(f'{sample} passed! - elapsed: {elapsed}'))
        else:
            print(make_red(f'{sample} failed! - elapsed: {elapsed}'))
        if (not res or kwargs.get('verbose', False)) and report:
            print(report)


def main():
    args = parser.parse_args()
    run_test(**vars(args))


if __name__ == '__main__':
    main()

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


class Solution(metaclass=abc.ABCMeta):
    def __init__(self, filepath, *args, **kwargs):
        super().__init__()
        self.filepath = filepath
        self.verbose = kwargs.get('verbose', False)
        self.build()
        
    @abc.abstractmethod
    def build(self):
        raise NotImplementedError

    @abc.abstractmethod
    def execute(self, test_input):
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


class CppSolution(Solution):
    def __init__(self, filepath, *args, **kwargs):
        super().__init__(filepath, *args, **kwargs)

    def build(self):
        start_time = datetime.now()
        exe_filepath = os.path.join(os.path.dirname(self.filepath), 'a.out')
        cmd = ['g++-11', '-std=c++17', '-Wall', '-Weffc++', self.filepath, '-o', exe_filepath]
        res = subprocess.run(cmd, check=True, capture_output=True, text=True)
        self.exe_filepath = exe_filepath
        print(res.stdout)
        print(res.stderr)
        print(f"build {self.filepath} done - elapsed: {(datetime.now() - start_time)}")

    def execute(self, sample):
        cmd = [self.exe_filepath]
        proc = subprocess.Popen(cmd, 
                stdin=subprocess.PIPE,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE)
        out, err = proc.communicate(sample.input())
        if self.verbose and err:
            print(err.decode())
        return out


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
        if self.output_type == 'float':
            return abs(float(a) - float(b)) < self.precision
        else:
            raise NotImplementedError
            

class TxtSample(TestSample):
    def __init__(self, input_txt, output_txt, *args, **kwargs):
        super().__init__(self, *args, **kwargs)
        self.input_txt = input_txt
        self.output_txt = output_txt

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

        res = True
        report = []
        for i, (a, b) in enumerate(zip(ans_lines, ref_lines)):
            correct = self.is_equal(a, b)
            res &= correct
            if not correct:
                report.append(f'case {i} - failed'
                f'\n\tcorrent ans: {b.decode()}'
                f'\n\tyour ans: {a.decode()}')
            else:
                report.append(f'case {i} - ok')
        return res, '\n'.join(report)


class TxtSampleWithoutOutput(TxtSample):
    def __init__(self, input_txt, output_txt=None, *args, **kwargs):
        super().__init__(self, output_txt, *args, **kwargs)
        self.input_txt = input_txt
        
    def ref_output(self):
        pass
    
    def validate(self, ans):
        ans_lines = ans.split(b'\n')
        ans_lines = [l.strip() for l in ans_lines if l]
        report = []
        for i, ans in enumerate(ans_lines):
            report.append(f'case {i} - {ans.decode()}')
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
    
    samples = find_samples(directory, *args, **kwargs)
    for sample in samples:
        start_time = datetime.now()
        ans = solution.execute(sample)
        elapsed = datetime.now() - start_time
        res, report = sample.validate(ans)
        if res:
            print(f'{sample} passed - elapsed: {elapsed}')
        else:
            print(f'{sample} failed - elapsed: {elapsed}')
        if (not res or kwargs.get('verbose', False)) and report:
            print(report)


def main():
    args = parser.parse_args()
    run_test(**vars(args))


if __name__ == '__main__':
    main()

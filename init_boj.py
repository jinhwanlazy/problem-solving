import os
import argparse
import time

import requests 
from bs4 import BeautifulSoup 


PROJECT_DIRPATH = os.path.dirname(os.path.abspath(__file__))
TMP_DIRPATH = os.path.join(PROJECT_DIRPATH, '.tmp')

parser = argparse.ArgumentParser(
        description='Download example input/outputs from boj website')
parser.add_argument(
        'pids', metavar='N', type=int, nargs='+', help='problem id')
parser.add_argument('--src', type=str, default='boj')
parser.add_argument('--verbose', '-v', action='store_true')

        
class Problem:
    def __init__(self, verbose):
        super().__init__()
        self.verbose = verbose

    def name(self):
        raise NotImplementedError

    def alt_name(self):
        return ""

    def url(self):
        raise NotImplementedError

    def dirpath(self):
        return os.path.join(PROJECT_DIRPATH, self.name())

    def examples(self):
        raise NotImplementedError

    def tags(self):
        raise NotImplementedError

    def get_page_(self):
        cache_filepath = os.path.join(TMP_DIRPATH, self.name())
        os.makedirs(os.path.dirname(cache_filepath), exist_ok=True)
        html = None
        if os.path.isfile(cache_filepath):
            with open(cache_filepath, 'r') as f:
                html = f.read()
        else:
            res = requests.get(self.url())
            assert res.status_code == 200
            html = res.text
        if html is not None:
            with open(cache_filepath, 'w') as f:
                f.write(html)
        if self.verbose:
            print(html)
        return html
    

class BojProblem(Problem):
    def __init__(self, pid, verbose):
        super().__init__(verbose)
        self.pid_ = pid
        self.name_ = f'boj_{pid}'
        self.url_ = f'https://www.acmicpc.net/problem/{pid}'

        self.page_ = self.get_page_()
        self.info_ = self.get_info_()

        self.name_ko_ = self.info_.get('titleKo', '')

    def name(self):
        return self.name_

    def alt_name(self):
        return self.name_ko_
    
    def url(self):
        return self.url_

    def examples(self):
        soup = BeautifulSoup(self.page_, "html.parser") 
        for i in range(1, 100):
            in_tag = soup.find(class_="sampledata", id=f'sample-input-{i}')
            out_tag = soup.find(class_="sampledata", id=f'sample-output-{i}')
            if in_tag is None and out_tag is None:
                break
            if in_tag is not None:
                in_tag = in_tag.text
            if out_tag is not None:
                out_tag = out_tag.text
            if self.verbose:
                print(f'in {i}...')
                print(in_tag)
                print(f'out {i}...')
                print(out_tag)

            yield in_tag, out_tag

    def tags(self):
        res = []
        for tag in self.info_.get('tags', []):
            for tagNames in tag.get('displayNames', []):
                if tagNames.get('language') == 'en' and tagNames.get('short'):
                    res.append(tagNames['short'])
        from pprint import pprint
        pprint(self.info_)
        return sorted(res)

    def get_info_(self):
        url = 'https://solved.ac/api/v3/problem/show'
        params = {'problemId': self.pid_}
        res = requests.get(url=url, params=params)
        if self.verbose:
            print(res.json())
        return res.json()


def init_problem(pid, src, verbose=False):
    cls = {
        'boj': BojProblem,
    }[src]

    problem = cls(pid, verbose)
    print(f'initializing problem {problem.name()}...')
    
    # download in/out examples
    dirpath = problem.dirpath()
    os.makedirs(dirpath, exist_ok=True)
    for i, (in_, out_) in enumerate(problem.examples()):
        in_filepath = os.path.join(dirpath, f'sample{i+1}.in')
        out_filepath = os.path.join(dirpath, f'sample{i+1}.out')
        if in_ is not None:
            with open(in_filepath, 'w') as f:
                f.write(in_)
        if out_ is not None:
            with open(out_filepath, 'w') as f:
                f.write(out_)

    # generate readme.md
    readme = f'''# [{src.upper()} {pid} {problem.alt_name() if problem.alt_name() else problem.name()}]({problem.url()})
tags: {', '.join(problem.tags())}
'''
    readme_filepath = os.path.join(problem.dirpath(), 'readme.md')
    if not os.path.isfile(readme_filepath) or len(open(readme_filepath).readlines()) <= 2:
        with open(readme_filepath, 'w') as f:
            f.write(readme)
    else:
        print("skipping generate readme.md..")


def main(pids=[], src='boj', *args, **kwargs):
    for i, pid in enumerate(pids):
        init_problem(pid, src, verbose=kwargs.get('verbose', False))
        if i < len(pids) - 1:
            time.sleep(5)
    
if __name__ == '__main__':
    args = parser.parse_args()
    main(**vars(args))

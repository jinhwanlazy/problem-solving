import os
import re

ALGORITHMS = [
]

PREFIX = [
    'boj', 'swea', 'leet',
]

PROJECT_DIRPATH = os.path.dirname(os.path.abspath(__file__))

def problems():
    dirnames = []
    for dirname in os.listdir(PROJECT_DIRPATH):
        if any(dirname.startswith(prefix) for prefix in PREFIX):
            dirnames.append(dirname)
    
    def natural_sort_key(s, _nsre=re.compile('([0-9]+)')):
        return [int(text) if text.isdigit() else text.lower()
                for text in _nsre.split(s)]
    
    dirnames.sort(key=natural_sort_key)
    return [os.path.join(PROJECT_DIRPATH, d) for d in dirnames]


def problems_with_desciptions(result):
    res = []
    for p in problems():
        readme_filepath = os.path.join(p, 'readme.md')
        if not os.path.isfile(readme_filepath):
            continue
        with open(readme_filepath, 'r') as f:
            readme_lines = f.readlines()
        if len(readme_lines) < 10:
            continue
        name = os.path.basename(p)
        res.append(f'[{name}]({name})')
    result.append(', '.join(res))
    

def main():
    result = []
    result.append(
''' # 설명이 있는 문제들
''')
    
    problems_with_desciptions(result)

    with open(os.path.join(PROJECT_DIRPATH, 'readme.md'), 'w') as f:
        f.write('\n'.join(result))

if __name__ == '__main__':
    main()




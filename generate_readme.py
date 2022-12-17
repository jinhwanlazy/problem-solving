import os
import re
from glob import glob
from dataclasses import dataclass
from typing import List

PREFIX = [
    'boj', 'swea', 'leet', 'cf', 'foobar',
]

ALGORITHMS = {
    # graph - shortest path
    'algdijkstra', 'algbellman', 'algspfa'

    # graph - flow & matching
    "algmcmf", 'algbipartite', 'algdinic', 'algedmondskarp',

    # graph
    'algunionfind', 'algtoposort', 'algtarjanscc',

    # number theory
    'algsieve', 'algxgcd', 'algmodpow',

    # string
    'algkmp', 'algpalindrome',

    # tree
    'clssegtree', 'clsfenwicktree',

    # 2d geometry
    'algconvexhull', 'algrotatingcalipers', 'algshoelace',

    # others
    'alglis', 'algfft', 'algbigint', 
}

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


def generate_problems_with_desciptions_md():
    def parse_name(lines):
        try:
            return re.search(r'\[(.+)\]', lines[0][2:]).group(1)
        except:
            return lines[0].strip()

    def parse_tags(lines):
        for line in lines:
            m = re.search(r'\-\-tags: (.*)-->', line)
            if m:
                return m.group(1)
        return ""

    def to_table(rows):
        res = []
        res.append('| Name | Tags |')
        res.append('| ---- | ---- |')
        for name, tag in rows:
            res.append(f'| {name} | {tag} |')
        return '\n'.join(res)

    rows = []
    for p in problems():
        readme_filepath = os.path.join(p, 'readme.md')
        if not os.path.isfile(readme_filepath):
            continue
        with open(readme_filepath, 'r') as f:
            readme_lines = f.readlines()
        if len(readme_lines) <= 2:
            continue
        name = parse_name(readme_lines)
        tags = parse_tags(readme_lines)
        loc = os.path.basename(p)
        rows.append((f'[{name}]({loc})',tags))
    return to_table(rows)


@dataclass
class SnippetInfo:
    keyword: str
    description: str
    filepath: str
    start: int
    end: int
    search_str: str
    used_in: List[str]


def parse_snippets():
    snippets_dirpath = os.path.join(PROJECT_DIRPATH, '.misc', 'snippets')
    snippets_filepaths = glob(os.path.join(snippets_dirpath, 'cpp_*.snippets'))
    res = []
    for snippet_filepath in snippets_filepaths:
        res.extend(parse_snippet_file(snippet_filepath))
    return res


def parse_snippet_file(filepath):
    with open(filepath, 'r') as f:
        lines = f.readlines()

    relpath = filepath.replace(PROJECT_DIRPATH, "")
    relpath = relpath if not relpath.startswith('/') else relpath[1:]

    res = []
    info = None
    for i, line in enumerate(lines):
        if info is None:
            if line.startswith('snippet '):
                m = re.match(r'^snippet\s(.*)\s"(.*)"$', line)
                info = SnippetInfo(m.group(1), m.group(2), relpath, i+1, -1, None, [])
                first_two_lines = []
            else:
                continue
        elif line.startswith('endsnippet'):
            if info.keyword in ALGORITHMS:
                info.search_str = re.sub(r'\s+', '', ''.join(first_two_lines))
                info.used_in.extend(find_snippet_usage(info))
                res.append(info)
            info = None
        else:
            if len(first_two_lines) < 2:
                first_two_lines.append(line)
            info.end = i+1
    return res

def find_snippet_usage(info):
    res = []
    for p in problems():
        solution_filepath = os.path.join(p, 'solution.cpp')
        if not os.path.isfile(solution_filepath):
            continue
        with open(solution_filepath, 'r') as f:
            solution = re.sub(r'\s+', '', f.read())
        if solution.find(info.search_str) != -1:
            res.append(os.path.basename(p))
    return res


def generate_list_of_snippets_md():
    def to_table(snippets):
        res = []
        res.append('| Keyword | Description | Used in |')
        res.append('| ------- | ----------- | ------- |')
        for s in snippets:
            used_in = ' '.join((f'[{name}]({name})' for name in s.used_in))
            res.append(f'| [{s.keyword}]({s.filepath}#L{s.start}) | {s.description} | {used_in} |')
        return '\n'.join(res)
        

    snippets_dirpath = os.path.join(PROJECT_DIRPATH, '.misc', 'snippets')
    snippets_filepaths = glob(os.path.join(snippets_dirpath, 'cpp_*.snippets'))
    res = []
    for snippet_filepath in snippets_filepaths:
        m = re.match(r'^cpp_(.*)\.snippets$', os.path.basename(snippet_filepath))
        if not m:
            continue
        category = m.group(1).upper().replace('_', ' ')
        snippets = parse_snippet_file(snippet_filepath)
        if not snippets:
            continue
        res.append(f'## {category}')
        res.append(to_table(snippets))
        res.append('')
        
    return '\n'.join(res)
    

def main():
    template_filepath = os.path.join(PROJECT_DIRPATH, '.misc', 'readme_template.md')
    with open(template_filepath, 'r') as f:
        template = f.read()
    print(template)

    template = template.replace(
            'SOLUTIONS_WITH_DESCRIPTION', 
            generate_problems_with_desciptions_md())
    template = template.replace(
            'LIST_OF_SNIPPETS',
            generate_list_of_snippets_md())

    with open(os.path.join(PROJECT_DIRPATH, 'readme.md'), 'w') as f:
        f.write(template)

    for info in parse_snippets():
        print(info)


if __name__ == '__main__':
    main()


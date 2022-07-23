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


def problems_with_desciptions():
    def parse_name(lines):
        return re.search(r'\[(.+)\]', lines[0][2:]).group(1)

    def parse_tags(lines):
        for line in lines:
            m = re.search(r'\-\-tags: (.*)-->', line)
            if m:
                return m.group(1)
        return ""

    def to_table(rows):
        res = []
        res.append('| name | tags |')
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
    

def main():
    template_filepath = os.path.join(PROJECT_DIRPATH, '.misc', 'readme_template.md')
    with open(template_filepath, 'r') as f:
        template = f.read()
    print(template)

    template = template.replace('SOLUTIONS_WITH_DESCRIPTION', problems_with_desciptions())

    with open(os.path.join(PROJECT_DIRPATH, 'readme.md'), 'w') as f:
        f.write(template)

if __name__ == '__main__':
    main()


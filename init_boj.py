import os
import argparse
import time

import requests 
from bs4 import BeautifulSoup 

parser = argparse.ArgumentParser(
        description='Download example input/outputs from boj website')
parser.add_argument(
        'pids', metavar='N', type=int, nargs='+', help='problem id')
parser.add_argument('--force', action='store_true')
parser.add_argument('--verbose', '-v', action='store_true')

url_base = 'https://www.acmicpc.net/problem/{pid}'

def get_page(pid, url, force=False):
    cache_filepath = os.path.join(os.path.dirname(__file__), '.tmp', str(pid))
    os.makedirs(os.path.dirname(cache_filepath), exist_ok=True)
    html = None
    if not force and os.path.isfile(cache_filepath):
        with open(cache_filepath, 'r') as f:
            html = f.read()
    else:
        res = requests.get(url)
        assert res.status_code == 200
        html = res.text
    if html is not None:
        with open(cache_filepath, 'w') as f:
            f.write(html)
    return html


def parse_examples(html):
    soup = BeautifulSoup(html, "html.parser") 
    for i in range(1, 100):
        in_tag = soup.find(class_="sampledata", id=f'sample-input-{i}')
        out_tag = soup.find(class_="sampledata", id=f'sample-output-{i}')
        if in_tag is None and out_tag is None:
            break
        if in_tag is not None:
            in_tag = in_tag.text
        if out_tag is not None:
            out_tag = out_tag.text
        yield in_tag, out_tag


def download(pid, url, force=False, verbose=False):
    print(f'downloading {url}...')
    page = get_page(pid, url, force)
    if verbose:
        print(page)
    examples = parse_examples(page)
    dirpath = f'boj_{pid}'
    os.makedirs(dirpath, exist_ok=True)
        
    for i, (in_, out_) in enumerate(examples):
        in_filepath = os.path.join(dirpath, f'sample{i+1}.in')
        out_filepath = os.path.join(dirpath, f'sample{i+1}.out')
        if in_ is not None:
            with open(in_filepath, 'w') as f:
                f.write(in_)
        if out_ is not None:
            with open(out_filepath, 'w') as f:
                f.write(out_)
    

def main(pids=[], *args, **kwargs):
    for i, pid in enumerate(pids):
        url = url_base.format(pid=pid)
        download(pid, url, force=kwargs.get('force'), verbose=kwargs.get('verbose'))
        if i < len(pids) - 1:
            time.sleep(5)
    

if __name__ == '__main__':
    args = parser.parse_args()
    main(**vars(args))

import string
alphabet = string.ascii_lowercase
table = {y: x for x, y in zip(alphabet, alphabet[::-1])}

def solution(encoded):
    encoded = list(encoded)
    for i, c in enumerate(encoded):
        encoded[i] = table.get(c, c)
    return ''.join(encoded)

if __name__ == '__main__':
    print(solution(input()))

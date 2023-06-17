a = input().strip()
b = input().strip()

import re
m = re.findall(b, a)
print(len(m))

import collections
import operator

def Solve(string, w):
  char_count = collections.defaultdict(int)
  for c in string:
    char_count[c] += 1
  
  char_count = [list(i) for i in char_count.items()]
  chars = set()
  res = []
  for _ in range(len(string)):
    char_count = sorted(char_count, key=operator.itemgetter(1))
    for i in range(len(char_count) - 1, len(char_count) - w - 1, -1):
      c, t = char_count[i]
      if c not in chars:
        if t <= 0:
          raise Exception("No more char to select")
        chars.add(c)
        res.append(c)
        char_count[i][1] -= 1
        break
    if len(chars) == w:
      chars.remove(res[-w])

  return res


import sys

if __name__ == "__main__":
  print Solve(sys.argv[1], int(sys.argv[2]))

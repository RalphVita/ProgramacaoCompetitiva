import re
import sys

#Lista de Entradas
for line in sys.stdin:
    print("YES" if re.search("h.*e.*l.*l.*o.*",line) else "NO")

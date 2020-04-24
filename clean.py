import sys

if len(sys.argv) < 2:
    print("Please pass file path as argument.")
    sys.exit()

txt = open(sys.argv[1])

total = 0

for line in txt:
    values = line.strip().split(" ")
    total += int(values[2])
    print(values[1], total)

import sys

# argv[1] = input file
# argv[2] = start number

start = int(sys.argv[2])
val = start
with open(sys.argv[1], 'r') as ifile:
    while val != start + 10:
        with open('run' + str(val) + '.log', 'w') as ofile:
            for i in range(0, 500):
                ofile.write(ifile.readline())
        val += 1

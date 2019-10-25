#! /usr/bin/env python3

import argparse
import sys

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Create hexadecimal range")
    parser.add_argument('start', help='start value')
    parser.add_argument('end', help='end value')
    parser.add_argument('--step', help='step size')

    args = parser.parse_args()
    start = int(args.start, 16)
    end = int(args.end, 16)
    step = 1

    if args.step != None:
        step = int(args.step, 16)

    for i in range(start, end + 1, step):
        sys.stdout.write(hex(i)[2:] + ' ')
    sys.stdout.write('\n')
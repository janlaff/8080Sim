#! /usr/bin/env python3

import argparse
import sys

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Sort hexadecimal range")
    parser.add_argument('values', nargs='+', help='hex range')

    args = parser.parse_args()

    hexVals = list(map(lambda x: int(x, 16), args.values))
    hexVals.sort()

    for value in hexVals:
        sys.stdout.write(hex(value)[2:] + ' ')
    sys.stdout.write('\n')

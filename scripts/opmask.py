#! /usr/bin/env python3

import argparse

def base64_encode(num):
    if num < 26:
        return chr(num + ord('A'))
    if num < 52:
        return chr(num + ord('a') - 26)
    if num < 62:
        return chr(num + ord('0') - 52)
    if num == 62:
        return '+'
    elif num == 63:
        return '/'
    else:
        raise Exception("Value too big")

def createBitMask(opcode_count, opcodes):
    if opcode_count % 6 != 0:
        bit_count = (opcode_count // 6 + 1) * 6
    else:
        bit_count = opcode_count

    bits = ['0'] * bit_count

    for opcode in opcodes:
        idx = int(opcode, 16)
        bits[idx] = '1'

    result = []

    for i in range(0, bit_count, 6):
        val = int(''.join(bits[i:i+6]), 2)
        result.append(base64_encode(val))

    return ''.join(result)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Create base64 encoded opcode map")
    parser.add_argument('--code-count', type=int, default=256, help='Number of existing opcodes (bitmask width)')
    parser.add_argument('-c', default=[], nargs='+', help='Opcodes in hex that should match with this mask')
    parser.add_argument('-i', action='store_true', help='Interactive mode')

    args = parser.parse_args()
    interactive = args.i

    try:
        if interactive:
            while True:
                opcodes = input("[*] Opcodes> ").split()
                print(createBitMask(args.code_count, opcodes))
        else:
            print(createBitMask(args.code_count, args.c))
    except KeyboardInterrupt:
        print('\n[*] Exiting...')
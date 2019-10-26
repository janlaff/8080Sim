#pragma once

/*
 *  Operand masks
 */

// Opcodes that have register A as operand
// 02 12 32 47 4f 57 5f 67 6f 77 7f 8f 97 9f a7 af b7 bf
constexpr auto mask_operand_a = "IAAgAAAAIAABAQEBAQEBAQABAQEBAQEBAAAAAAAAAAA";

// Opcodes that have register B as operand
// 40 48 50 58 60 68 70 78 80 88 90 98 a0 a8 b0 b8
constexpr auto mask_operand_b = "AAAAAAAAAACAgICAgICAgICAgICAgICAAAAAAAAAAAA";

// Opcodes that have register C as operand
// 41 49 51 59 61 69 71 79 81 89 91 99 a1 a9 b1 b9
constexpr auto mask_operand_c = "AAAAAAAAAABAQEBAQEBAQEBAQEBAQEBAAAAAAAAAAAA";

/*
 * Result masks
 */

// Opcodes that store the result in B
// 04 05 06 40 41 42 43 44 45 46 47
constexpr auto mask_store_b = "DgAAAAAAAAD/AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

/*
 * Logic masks
 */

// Opcodes that move value
// 01 02 06 0a 0e 11 12 16 1a 1e 21 26 2e 31 32 3a 3e 40 41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4e 4f 50 51 52 53 54 55 56 57 58 59 5a 5b 5c 5d 5e 5f 60 61 62 63 64 65 66 67 68 69 6a 6b 6c 6d 6e 6f 70 71 72 73 74 75 77 78 79 7a 7b 7c 7d 7e 7f
constexpr auto mask_mov = "YiJiIkICYCL////////9/wAAAAAAAAAAAAAAAAAAAAA";
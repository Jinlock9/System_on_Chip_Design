#include <iostream>
#include <cstdint>
#include <iomanip>

enum ALU_FUNC : unsigned short int {
    ALU_ADD     = 0,
    ALU_SUB     = 1,
    ALU_SLT     = 2,
    ALU_SLTU    = 3,
    ALU_AND     = 4,
    ALU_OR      = 5,
    ALU_XOR     = 6,
    ALU_SLL     = 7,
    ALU_SRL     = 8,
    ALU_SRA     = 9,
    ALU_MUL     = 10,
    ALU_MULH    = 11,
    ALU_MULHSU  = 12,
    ALU_MULHU   = 13,
    ALU_DIV     = 14,
    ALU_DIVU    = 15,
    ALU_REM     = 16,
    ALU_REMU    = 17
};

int32_t hls_alu(int32_t opa, int32_t opb, ALU_FUNC func);

int main() {
    int32_t opa, opb, result;

    // ALU_ADD
    opa = 10; opb = 5;
    result = hls_alu(opa, opb, ALU_ADD);
    std::cout << "ALU_ADD: " << result << " (Expected: 15)" << std::endl;

    // ALU_SUB
    result = hls_alu(opa, opb, ALU_SUB);
    std::cout << "ALU_SUB: " << result << " (Expected: 5)" << std::endl;

    // ALU_SLT (signed comparison)
    opa = -10; opb = 5;
    result = hls_alu(opa, opb, ALU_SLT);
    std::cout << "ALU_SLT: " << result << " (Expected: 1)" << std::endl;

    opa = 10; opb = 5;
    result = hls_alu(opa, opb, ALU_SLT);
    std::cout << "ALU_SLT: " << result << " (Expected: 0)" << std::endl;

    // ALU_SLTU (unsigned comparison)
    opa = 10; opb = 20;
    result = hls_alu(opa, opb, ALU_SLTU);
    std::cout << "ALU_SLTU: " << result << " (Expected: 1)" << std::endl;

    opa = 20; opb = 10;
    result = hls_alu(opa, opb, ALU_SLTU);
    std::cout << "ALU_SLTU: " << result << " (Expected: 0)" << std::endl;

    // ALU_AND
    opa = 6; opb = 3;
    result = hls_alu(opa, opb, ALU_AND);
    std::cout << "ALU_AND: " << result << " (Expected: 2)" << std::endl;

    // ALU_OR
    result = hls_alu(opa, opb, ALU_OR);
    std::cout << "ALU_OR: " << result << " (Expected: 7)" << std::endl;

    // ALU_XOR
    result = hls_alu(opa, opb, ALU_XOR);
    std::cout << "ALU_XOR: " << result << " (Expected: 5)" << std::endl;

    // ALU_SLL (shift left logical)
    opa = 5; opb = 1;
    result = hls_alu(opa, opb, ALU_SLL);
    std::cout << "ALU_SLL: " << result << " (Expected: 10)" << std::endl;

    // ALU_SRL (shift right logical)
    opa = 10; opb = 1;
    result = hls_alu(opa, opb, ALU_SRL);
    std::cout << "ALU_SRL: " << result << " (Expected: 5)" << std::endl;

    // ALU_SRA (shift right arithmetic)
    opa = -4; opb = 1;
    result = hls_alu(opa, opb, ALU_SRA);
    std::cout << "ALU_SRA: " << result << " (Expected: -2)" << std::endl;

    // ALU_MUL (unsigned multiply)
    opa = 5; opb = 3;
    result = hls_alu(opa, opb, ALU_MUL);
    std::cout << "ALU_MUL: " << result << " (Expected: 15)" << std::endl;

    // ALU_MULH (high signed multiply)
    opa = 100000; opb = 100000;
    result = hls_alu(opa, opb, ALU_MULH);
    std::cout << "ALU_MULH: " << result << " (Expected: 2)" << std::endl;

    // ALU_MULHSU (high signed-unsigned multiply)
    result = hls_alu(opa, opb, ALU_MULHSU);
    std::cout << "ALU_MULHSU: " << result << " (Expected: 2)" << std::endl;

    // ALU_MULHU (high unsigned multiply)
    result = hls_alu(opa, opb, ALU_MULHU);
    std::cout << "ALU_MULHU: " << result << " (Expected: 2)" << std::endl;

    // ALU_DIV (signed division)
    opa = 10; opb = 5;
    result = hls_alu(opa, opb, ALU_DIV);
    std::cout << "ALU_DIV: " << result << " (Expected: 2)" << std::endl;

    opa = -10; opb = 5;
    result = hls_alu(opa, opb, ALU_DIV);
    std::cout << "ALU_DIV: " << result << " (Expected: -2)" << std::endl;

    // ALU_DIVU (unsigned division)
    opa = 10; opb = 3;
    result = hls_alu(opa, opb, ALU_DIVU);
    std::cout << "ALU_DIVU: " << result << " (Expected: 3)" << std::endl;

    // ALU_REM (signed remainder)
    opa = 10; opb = 3;
    result = hls_alu(opa, opb, ALU_REM);
    std::cout << "ALU_REM: " << result << " (Expected: 1)" << std::endl;

    opa = -10; opb = 3;
    result = hls_alu(opa, opb, ALU_REM);
    std::cout << "ALU_REM: " << result << " (Expected: -1)" << std::endl;

    // ALU_REMU (unsigned remainder)
    opa = 10; opb = 3;
    result = hls_alu(opa, opb, ALU_REMU);
    std::cout << "ALU_REMU: " << result << " (Expected: 1)" << std::endl;

    // Default case
    result = hls_alu(opa, opb, static_cast<ALU_FUNC>(18));  // Invalid function
    std::cout << std::hex << "DEFAULT: " << result << " (Expected: 0xcafebabe)" << std::endl;

    return 0;
}

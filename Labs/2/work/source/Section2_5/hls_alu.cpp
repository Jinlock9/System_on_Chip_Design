#include <cstdint>

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

int32_t hls_alu(int32_t opa, int32_t opb, ALU_FUNC func) {
#pragma HLS INTERFACE s_axilite port=return bundle=CRTLS
#pragma HLS INTERFACE s_axilite port=opa bundle=CRTLS
#pragma HLS INTERFACE s_axilite port=opb bundle=CRTLS
#pragma HLS INTERFACE s_axilite port=func bundle=CRTLS

    int32_t result = 0;
    int64_t signed_mul, mixed_mul;
    uint64_t unsigned_mul;

    switch (func) {
        case ALU_ADD:
            result = opa + opb;
            break;
        case ALU_SUB:
            result = opa - opb;
            break;
        case ALU_SLT:
            result = (opa < opb) ? 1 : 0;
            break;
        case ALU_SLTU:
            result = (static_cast<uint32_t>(opa) < static_cast<uint32_t>(opb)) ? 1 : 0;
            break;
        case ALU_AND:
            result = opa & opb;
            break;
        case ALU_OR:
            result = opa | opb;
            break;
        case ALU_XOR:
            result = opa ^ opb;
            break;
        case ALU_SLL:
            result = opa << (opb & 0x1F);
            break;
        case ALU_SRL:
            result = static_cast<uint32_t>(opa) >> (opb & 0x1F);
            break;
        case ALU_SRA:
            result = opa >> (opb & 0x1F);
            break;
        case ALU_MUL:
            unsigned_mul = static_cast<uint64_t>(opa) * static_cast<uint64_t>(opb);
            result = static_cast<int32_t>(unsigned_mul);
            break;
        case ALU_MULH:
            signed_mul = static_cast<int64_t>(opa) * static_cast<int64_t>(opb);
            result = static_cast<int32_t>(signed_mul >> 32);
            break;
        case ALU_MULHSU:
            mixed_mul = static_cast<int64_t>(opa) * static_cast<uint64_t>(opb);
            result = static_cast<int32_t>(mixed_mul >> 32);
            break;
        case ALU_MULHU:
            unsigned_mul = static_cast<uint64_t>(opa) * static_cast<uint64_t>(opb);
            result = static_cast<int32_t>(unsigned_mul >> 32);
            break;
        case ALU_DIV:
            if (opb != 0)
                result = opa / opb;
            else
                result = 0;
            break;
        case ALU_DIVU:
            if (opb != 0)
                result = static_cast<uint32_t>(opa) / static_cast<uint32_t>(opb);
            else
                result = 0;
            break;
        case ALU_REM:
            if (opb != 0)
                result = opa % opb;
            else
                result = 0;
            break;
        case ALU_REMU:
            if (opb != 0)
                result = static_cast<uint32_t>(opa) % static_cast<uint32_t>(opb);
            else
                result = 0;
            break;
        default:
            result = 0xcafebabe;
            break;
    }

    return result;
}

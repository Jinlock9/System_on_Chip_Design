`timescale 1ns/100ps

// RISCV ISA SPEC
`define XLEN 32

//
// ALU function code input
// probably want to leave these alone
//
typedef enum logic [4:0] {
	ALU_ADD     = 5'h00,
	ALU_SUB     = 5'h01,
	ALU_SLT     = 5'h02,
	ALU_SLTU    = 5'h03,
	ALU_AND     = 5'h04,
	ALU_OR      = 5'h05,
	ALU_XOR     = 5'h06,
	ALU_SLL     = 5'h07,
	ALU_SRL     = 5'h08,
	ALU_SRA     = 5'h09,
	ALU_MUL     = 5'h0a,
	ALU_MULH    = 5'h0b,
	ALU_MULHSU  = 5'h0c,
	ALU_MULHU   = 5'h0d,
	ALU_DIV     = 5'h0e,
	ALU_DIVU    = 5'h0f,
	ALU_REM     = 5'h10,
	ALU_REMU    = 5'h11
} ALU_FUNC;

//
// The ALU
//
// given the command code CMD and proper operands A and B, compute the
// result of the instruction
//
module rtl_alu(
    input clk, reset, start,
	input [`XLEN-1:0] opa,
	input [`XLEN-1:0] opb,
	ALU_FUNC     func,

	output logic [`XLEN-1:0] result
);
	wire signed [`XLEN-1:0] signed_opa, signed_opb;
	wire signed [2*`XLEN-1:0] signed_mul, mixed_mul, signed_div, signed_rem;
	wire        [2*`XLEN-1:0] unsigned_mul, unsigned_div, unsigned_rem;

	logic [`XLEN-1:0] result_reg;
	logic [2*`XLEN-1:0] mult_reg;
	logic [`XLEN-1:0] div_reg;
	logic [`XLEN-1:0] rem_reg;

	logic done;

	assign signed_opa = opa;
	assign signed_opb = opb;

	assign signed_mul = signed_opa * signed_opb;
	assign unsigned_mul = opa * opb;
	assign mixed_mul = signed_opa * opb;

	assign signed_div = signed_opa / signed_opb;
	assign unsigned_div = opa / opb;
	assign signed_rem = signed_opa % signed_opb;
	assign unsigned_rem = opa % opb;
    
	// TODO: Complete ALU logic
	mult mult_0 (
		.clock(clock),
		.reset(reset),
		.mcand(opa), 
		.mplier(opb),
		.start(start),
		.product(mult_reg),
		.done(done)
	)

	always_comb begin
		case (func)
			ALU_ADD:    result_reg = opa + opb;
			ALU_SUB:    result_reg = opa - opb;
			ALU_SLT:    result_reg = signed_opa < signed_opb;
			ALU_SLTU:   result_reg = opa < opb;
			ALU_AND:    result_reg = opa & opb;
			ALU_OR:     result_reg = opa | opb;
			ALU_XOR:    result_reg = opa ^ opb;
			ALU_SLL:    result_reg = opa << opb[4:0];
			ALU_SRL:    result_reg = opa >> opb[4:0];
			ALU_SRA:    result_reg = signed_opa >>> opb[4:0];
			ALU_MUL:    result_reg = unsigned_mul[`XLEN-1:0];
			ALU_MULH:   result_reg = signed_mul[2*`XLEN-1:`XLEN];
			ALU_MULHSU: result_reg = mixed_mul[2*`XLEN-1:`XLEN];
			ALU_MULHU:  result_reg = unsigned_mul[2*`XLEN-1:`XLEN];
			ALU_DIV:    result_reg = signed_div[`XLEN-1:0];
			ALU_DIVU:   result_reg = unsigned_div[`XLEN-1:0];
			ALU_REM:    result_reg = signed_rem[`XLEN-1:0];
			ALU_REMU:   result_reg = unsigned_rem[`XLEN-1:0];
			default:    result_reg = `XLEN'hfacebeec;
		endcase
	end

	always_ff @(posedge clk) begin
		result <= result_reg;
	end

endmodule // alu

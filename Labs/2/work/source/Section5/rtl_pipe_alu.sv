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
    input clk,
    input [`XLEN-1:0] opa,
    input [`XLEN-1:0] opb,
    input [4:0] func,  

    output logic [`XLEN-1:0] result, 
    output logic done 
);

    logic [`XLEN-1:0] alu_result, mult_result, div_result;
    logic mult_done, div_done, alu_done;
    logic [2*`XLEN-1:0] mult_intermediate_result;
    logic [`XLEN-1:0] div_quotient, div_remainder;

    wire signed [`XLEN-1:0] signed_opa, signed_opb;
    assign signed_opa = opa;
    assign signed_opb = opb;

    logic internal_reset;
    assign internal_reset = 1'b0;

    mult mult_0 (
        .clock(clk),
        .reset(internal_reset),   
        .mcand(opa),              
        .mplier(opb),           
        .start(func == ALU_MUL || func == ALU_MULH || func == ALU_MULHSU || func == ALU_MULHU), 
        .product(mult_intermediate_result),
        .done(mult_done)
    );

    always_comb begin
        case (func)
            ALU_MUL: mult_result = mult_intermediate_result[`XLEN-1:0]; 
            ALU_MULH: mult_result = mult_intermediate_result[2*`XLEN-1:`XLEN];  
            ALU_MULHSU: mult_result = mult_intermediate_result[2*`XLEN-1:`XLEN];  
            ALU_MULHU: mult_result = mult_intermediate_result[2*`XLEN-1:`XLEN];  
            default: mult_result = `XLEN'b0;
        endcase
    end

    div div_0 (
        .clock(clk),
        .reset(internal_reset),    
        .dividend(opa),            
        .divisor(opb),            
        .start(func == ALU_DIV || func == ALU_DIVU || func == ALU_REM || func == ALU_REMU),  
        .quotient(div_quotient),
        .remainder(div_remainder),
        .done(div_done)
    );

    always_comb begin
        case (func)
            ALU_DIV: div_result = div_quotient;  
            ALU_DIVU: div_result = div_quotient;  
            ALU_REM: div_result = div_remainder;  
            ALU_REMU: div_result = div_remainder; 
            default: div_result = `XLEN'b0;
        endcase
    end

    always_comb begin
        case (func)
            ALU_ADD: alu_result = opa + opb;
            ALU_SUB: alu_result = opa - opb;
            ALU_SLT: alu_result = (signed_opa < signed_opb) ? 1 : 0;
            ALU_SLTU: alu_result = (opa < opb) ? 1 : 0;
            ALU_AND: alu_result = opa & opb;
            ALU_OR: alu_result = opa | opb;
            ALU_XOR: alu_result = opa ^ opb;
            ALU_SLL: alu_result = opa << opb[4:0];
            ALU_SRL: alu_result = opa >> opb[4:0];
            ALU_SRA: alu_result = signed_opa >>> opb[4:0];
            default: alu_result = `XLEN'hcafebabe; 
        endcase
    end

    always_comb begin
        done = 1'b0;
        case (func)
            ALU_MUL, ALU_MULH, ALU_MULHSU, ALU_MULHU: begin
                result = mult_result;
                done = mult_done;
            end
            ALU_DIV, ALU_DIVU, ALU_REM, ALU_REMU: begin
                result = div_result;
                done = div_done;
            end
            default: begin
                result = alu_result;
                done = 1'b1;
            end
        endcase
    end

endmodule

`define PIPESTAGE 8
`define BIT_WIDTH 8

// This is an 8 stage (9 depending on how you look at it) pipelined 
// multiplier that multiplies 2 64-bit integers and returns the low 64 bits 
// of the result.  This is not an ideal multiplier but is sufficient to 
// allow a faster clock period than straight *
// This module instantiates 8 pipeline stages as an array of submodules.
module mult(
	input clock, reset,
	input [2*`XLEN-1:0] mcand, mplier,
	input start,

	output [2*`XLEN-1:0] product,
	output done
);
	logic [2*`XLEN-1:0] mcand_out, mplier_out;
	logic [((`PIPESTAGE-1)*2*`XLEN)-1:0] internal_products, internal_mcands, internal_mpliers;
	logic [`PIPESTAGE-2:0] internal_dones;
	// TODO: instantiation of mult_stage

	mult_stage stages [`PIPESTAGE-1:0] (
		.clock(clock),
		.reset(reset),
		.start({internal_dones, start}),
		.product_in({internal_products, 64'h0}),
		.mplier_in({internal_mpliers, mplier}),
		.mcand_in({internal_mcands, mcand}),
		.done({done, internal_dones}),
		.product_out({product, internal_products}),
		.mplier_out({mplier_out, internal_mpliers}),
		.mcand_out({mcand_out, internal_mcands})
	);

endmodule

module mult_stage(
	input clock, reset, start,
	input [2*`XLEN-1:0] product_in, mplier_in, mcand_in,

	output logic done,
	output logic [2*`XLEN-1:0] product_out, mplier_out, mcand_out
);
	logic [2*`XLEN-1:0] prod_in_reg, partial_prod_reg;
	logic [2*`XLEN-1:0] partial_product, next_mplier, next_mcand;
	// TODO: combinational logics

	assign product_out = prod_in_reg + partial_prod_reg;
	assign partial_product = mplier_in[`PIPESTAGE-1:0] * mcand_in;

	assign next_mplier = {{{`PIPESTAGE}{1'b0}}, mplier_in[2*`XLEN-1:`PIPESTAGE]};
	assign next_mcand = {mcand_in[(2*`XLEN-1)-`PIPESTAGE:0], {{`PIPESTAGE}{1'b0}}};

	// synopsys sync_set_reset "reset"
	always_ff @(posedge clock) begin
		prod_in_reg      <= product_in;
		partial_prod_reg <= partial_product;
		mplier_out       <= next_mplier;
		mcand_out        <= next_mcand;
	end

	// synopsys sync_set_reset "reset"
	always_ff @(posedge clock) begin
		if(reset)
			done <= 1'b0;
		else
			done <= start;
	end
endmodule

module div(
    input clock, reset,
    input [`XLEN-1:0] dividend, divisor,
    input start,

    output [`XLEN-1:0] quotient, remainder,
    output done
);
    logic [`XLEN-1:0] dividends[`XLEN-1:0];
    logic [`XLEN-1:0] divisors[`XLEN-1:0];
    logic [`XLEN-1:0] quotients[`XLEN-1:0];
    logic [`XLEN-1:0] remainders[`XLEN-1:0];
    logic dones[`XLEN-1:0];

    genvar i;
    generate
        for (i = 0; i < `XLEN; i = i + 1) begin : div_stages
            div_stage stage (
                .clock(clock),
                .reset(reset),
                .start((i == 0) ? start : dones[i-1]),
                .dividend_in((i == 0) ? dividend : dividends[i-1]),
                .divisor_in((i == 0) ? divisor : divisors[i-1]),
                .quotient_in((i == 0) ? 32'b0 : quotients[i-1]),
                .remainder_in((i == 0) ? {31'b0, dividend[`XLEN-1]} : remainders[i-1]),

                .dividend_out(dividends[i]),
                .divisor_out(divisors[i]),
                .quotient_out(quotients[i]),
                .remainder_out(remainders[i]),
                .done(dones[i])
            );
        end
    endgenerate

    assign quotient = quotients[`XLEN-1];
    assign remainder = remainders[`XLEN-1] >> 1;
    assign done = dones[`XLEN-1];
endmodule

module div_stage (
    input clock, reset, start,
    input [`XLEN-1:0] dividend_in, divisor_in,
    input [`XLEN-1:0] quotient_in, remainder_in,

    output logic [`XLEN-1:0] dividend_out, divisor_out,
    output logic [`XLEN-1:0] quotient_out, remainder_out,
    output logic done
);
    logic [`XLEN-1:0] dividend_reg;
    logic [`XLEN-1:0] divisor_reg;
    logic [`XLEN-1:0] quotient_reg;
    logic [`XLEN-1:0] remainder_reg;

    always_comb begin
        if (remainder_in >= divisor_in) begin
            remainder_reg = remainder_in - divisor_in;
            quotient_reg  = (quotient_in << 1) | 1'b1;
        end else begin
            remainder_reg = remainder_in;
            quotient_reg  = quotient_in << 1;
        end
        dividend_reg  = dividend_in << 1;
        remainder_reg = (remainder_reg << 1) | dividend_reg[`XLEN-1];
        divisor_reg   = divisor_in;
    end

    always_ff @(posedge clock) begin
        dividend_out  <= dividend_reg;
        divisor_out   <= divisor_reg;
        quotient_out  <= quotient_reg;
        remainder_out <= remainder_reg;
    end

    always_ff @(posedge clock) begin
        if (reset) begin
            done <= 1'b0;
        end else begin
            done <= start;
        end
    end

endmodule
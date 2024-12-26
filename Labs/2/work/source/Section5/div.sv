`timescale 1ns/100ps

// RISCV ISA SPEC
`define XLEN 32

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
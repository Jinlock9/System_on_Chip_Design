module rtl_divider(
    input clock,
    input [15:0] a,
    input [15:0] b,
    output [31:0] div,
    output [31:0] mod
);

    reg [31:0] div_reg;
    reg [31:0] mod_reg;

    always @(posedge clock) begin
        div_reg <= a / b;
        mod_reg <= a % b;
    end

    assign div = div_reg;
    assign mod = mod_reg;

endmodule


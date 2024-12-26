`define HALF_CYCLE 250

`timescale 1ns/100ps

module testbench();

    logic [31:0] a, b;
    logic quit, clock, start, reset;

    logic [31:0] quotient, remainder;
    logic done;

    wire [31:0] expected_quotient = a / b;
    wire [31:0] expected_remainder = a % b;

    wire correct = ((expected_quotient === quotient) && (expected_remainder === remainder)) | ~done;

    // Instantiate the divisor module
    div div0(
        .clock(clock),
        .reset(reset),
        .dividend(a),
        .divisor(b),
        .start(start),
        .quotient(quotient),
        .remainder(remainder),
        .done(done)
    );

    // Check correctness on each clock cycle
    always @(posedge clock)
        #(`HALF_CYCLE-5) if (!correct && done) begin 
            $display("Incorrect at time %4.0f", $time);
            $display("Expected Quotient = %h, Actual Quotient = %h", expected_quotient, quotient);
            $display("Expected Remainder = %h, Actual Remainder = %h", expected_remainder, remainder);
            $finish;
        end

    // Generate clock signal
    always begin
        #`HALF_CYCLE;
        clock = ~clock;
    end

    // Task to wait until done is asserted (same as in multiplier testbench)
    task wait_until_done;
        forever begin : wait_loop
            @(posedge done);
            @(negedge clock);
            if(done) disable wait_until_done;
        end
    endtask

    // Testbench logic
    initial begin
        $dumpvars;
        $monitor("Time:%4.0f done:%b a:%h b:%h quotient:%h remainder:%h expected_quotient:%h expected_remainder:%h",
                 $time, done, a, b, quotient, remainder, expected_quotient, expected_remainder);

        a = 10;
        b = 3;
        reset = 1;
        clock = 0;
        start = 1;
        #2000;

        // Test case 1
        @(negedge clock);
        reset = 0;
        @(negedge clock);
        start = 0;
        wait_until_done();
        start = 1;

        // Test case 2: Dividing a negative number
        a = 15;
        b = 2;
        @(negedge clock);
        start = 0;
        wait_until_done();
        start = 1;

        // Test case 3: Large dividend and divisor
        a = 12345678;
        b = 123;
        @(negedge clock);
        start = 0;
        wait_until_done();
        start = 1;

        $finish;
    end

endmodule

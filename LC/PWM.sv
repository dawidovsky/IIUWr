module cir(
  input clk, 
  input [1:0] sel,
  input [15:0] d,
  output [15:0] cnt, cmp, top,
  output out
);
  always_ff @(posedge clk) 
    if (sel == 2'b11) cnt <= d;
  else if (top == 0 || cnt >= top) cnt <= 1'b0;
    else cnt <= cnt + 1'b1;

  always_ff @(posedge clk)
    if (sel == 2'b10) top <= d;
    else if (sel == 2'b01) cmp <= d;

  always_ff @(posedge clk) 
    if (cmp != 0 && (cnt == top || cnt < cmp - 1'b1)) out <= 1'b1;
  else if (cmp == 0 || cnt >= cmp - 1'b1) out <= 1'b0;

endmodule

module asd(
  input clk, 
  input [1:0] sel,
  input [15:0] d,
  output [15:0] cnt, cmp, top,
  output out
);
  cir c1(clk, sel, d, cnt, cmp, top, out); 
endmodule
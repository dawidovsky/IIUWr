// Write your modules here!
module circuit(
  input nrst, step, push, 
  input [1:0] op,
  input [15:0] d,
  output [15:0] out,
  output [9:0] cnt
);
  logic [15:0] mem [0:1023];
  
  always_ff @(posedge step) begin
    if(push)       		  mem[cnt] <= d;
    else if(op == 2'b01)  mem[cnt - 1] <= -mem[cnt - 1];
    else if(op == 2'b10)  mem[cnt - 2] <= mem[cnt - 1] + mem[cnt - 2];
    else if(op == 2'b11)  mem[cnt - 2] <= mem[cnt - 1] * mem[cnt - 2];
  end
  
  always_ff @(posedge step or negedge nrst) begin
    if(!nrst)   						cnt <= 0;
    else if(push)  						cnt <= cnt + 1;
    else if((op == 2'b10 || op == 2'b11) && cnt > 0) cnt <= cnt - 1;
  end
  
  always_ff @(posedge step) begin
    if(!nrst)   		 out <= 0;
    else if(push)        out <= d;
    else if(op == 2'b01) out <= -mem[cnt - 1];
    else if(op == 2'b10) out <= mem[cnt - 1] + mem[cnt - 2];
    else if(op == 2'b11) out <= mem[cnt - 1] * mem[cnt - 2];
    else                 out <= mem[cnt - 1];    
  end
endmodule

module simple (
  input nrst, clk, push,
  input [15:0] d,
  input [1:0] op,
  output [9:0] cnt,
  output [15:0] out
);
  circuit x(nrst, clk, push, op, d, out, cnt);
endmodule 
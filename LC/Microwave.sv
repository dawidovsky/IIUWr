  module circuit(
    input clk, nrst, door, start, finish,
    output heat, light, bell
  );
    logic [4:0] q;
    always_ff @(posedge clk or negedge nrst) begin
      if(!nrst) q <= 5'b00001;
      else begin // przejście 
        if(q[0]) begin  // closed
          q[0] <= door | (start & !door) ? 0 : 1;
          q[1] <= door ? 1 : 0; // => open
          q[2] <= start & !door ? 1 : 0; // => cook
        end
        else if(q[1]) begin  // open
          q[1] <= !door ? 0 : 1;
          q[0] <= !door ? 1 : 0; // => closed
        end
        else if(q[2]) begin  // cook
          q[2] <= door | (finish & !door) ? 0 : 1;
          q[3] <= door ? 1 : 0; // => pause
          q[4] <= finish & !door ? 1 : 0; // => bell
        end
        else if(q[3]) begin // pause
          q[3] <= door ? 1 : 0;
          q[2] <= door ? 0 : 1; // => cook
        end
        else if(q[4]) begin // bell
          q[4] <= !door ? 1 : 0;
          q[1] <= !door ? 0 : 1; // => open
        end
      end
    end
    logic [2:0] o;
    always_comb casez(q) // wyjście
      5'b????1 : o = 3'b000; // closed / nothing
      5'b???1? : o = 3'b100; // open / light
      5'b??1?? : o = 3'b110; // cook / light & heat 
      5'b?1??? : o = 3'b100; // pause / light
      5'b1???? : o = 3'b001; // bell / bell
      default  : o = 3'bxxx; 
    endcase
    assign light = o[2];
    assign heat  = o[1];
    assign bell  = o[0];
  endmodule

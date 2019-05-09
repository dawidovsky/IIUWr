module main(
  output [15:0] o,
  input [15:0] i,
);
  // zwykły bubbleSort
  logic [3:0] temp;
  integer ii,j;
  always_comb begin
    o = i;
    for (ii = 3; ii >= 0; ii = ii - 1) begin
      for (j = 0; j < ii; j = j + 1) begin
        if (o[4*j + 3: 4*j] > o[4*(j+1) + 3 : 4*(j+1)])
            begin
              temp = o[4*j + 3: 4*j];
              o[4*j + 3: 4*j] = o[4*(j+1) + 3 : 4*(j+1)];
              o[4*(j+1) + 3 : 4*(j+1)] = temp;
            end
      end
    end
  end
endmodule

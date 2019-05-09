module main(
  output [31:0] o,
  input [31:0] i,
);
  // zamieniam na kod naturalny w sposób jaki jest opisany na wikipedii:
  // 1.przyjmij pierwszą cyfrę kodu naturalnego równą pierwszej cyfrze kodu Graya
  // 2.każdą kolejną cyfrę oblicz jako XOR odpowiedniej cyfry kodu Graya i 
  // poprzednio wyznaczonej cyfry kodu naturalnego.
  integer ii;
  logic temp;
  always_comb begin
    o[31] = i[31]; 
    temp = i[31];
    for(ii = 30; ii >= 0; ii = ii - 1) begin
      o[ii] = temp ^ i[ii];
      temp = o[ii];
    end
  end
  
endmodule

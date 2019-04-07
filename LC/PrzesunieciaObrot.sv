module funnelShifter(
  input [7:0]a,b,
  input [3:0]n, 
  output [7:0]o
);
  
  logic [15:0]concat;
  
  assign concat = {a, b};
  assign o = concat >> n;
  
endmodule

module main(
  input [7:0]i,
  input [3:0]n,
  input ar, lr, rot,
  output [7:0]o
);
  
  logic [7:0]a, b, helpa;
  logic [3:0] newn;
  // wybór n - przy przenoszeniu w lewo jest to 8 - n 
  assign newn = lr ? (4'b1000 - n) : n;
  // wybór b - same zera lub wejście
  assign b = lr && !rot ? 8'b0 : i;
  // wybór zmiennej pomocniczej w a 
  // odpowiednio ustawia jedynki lub zera dla przesunięcia arytmetycznego
  assign helpa = i[7] ? 8'b11111111 : 8'b0;
  // wybór a:
  // wejście dla obrotu lub przesunięcia w lewo
  // zmienna pomocnicza dla przesunięcia arytmetycznego w prawo
  // same zera dla przesunięcia logicznego w prawo
  assign a = lr || rot ? i : ( ar ? helpa : 8'b0 );
  funnelShifter f1(a, b, newn, o);
endmodule

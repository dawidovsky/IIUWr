module gpsadder(
  input a, b, c,
  output s, g, p
);
  
  assign s = a ^ b ^ c;
  assign g = a & b;
  assign p = a | b;
  
endmodule

module c1adder(
  input g0, p0, c0,
  output c
);
  assign c = (p0 & c0) | g0;
endmodule

module c2adder(
  input g0, p0, g1, p1, c0,
  output c
);
  assign c = (p0 & p1 & c0) | (p1 & g0) | g1;
endmodule

module c3adder(
  input g0, p0, g1, p1, g2, p2, c0,
  output c
);
  assign c = (p0 & p1 & p2 & c0) | (p1 & p2 & g0) | (p2 & g1) | g2;
endmodule


module fouradder(
  input [3:0] a, b,
  input c0,
  output [3:0] s,
  output gs, ps
);
  
  logic [3:0] g, p, c;
  assign c[0] = c0;
  gpsadder g1(a[0], b[0], c[0], s[0], g[0], p[0]);
  c1adder ca1(g[0], p[0], c[0], c[1]);
  gpsadder g2(a[1], b[1], c[1], s[1], g[1], p[1]);
  c2adder ca2(g[0], p[0], g[1], p[1], c[0], c[2]);
  gpsadder g3(a[2], b[2], c[2], s[2], g[2], p[2]);
  c3adder ca3(g[0], p[0], g[1], p[1], g[2], p[2], c[0], c[3]);
  gpsadder g4(a[3], b[3], c[3], s[3], g[3], p[3]);
  assign ps = p[0] & p[1] & p[2] & p[3];
  assign gs = (p[1] & p[2] & p[3] & g[0]) | (p[2] & p[3] & g[1]) | (p[3] & g[2]) | g[3];
  
endmodule

module main(
  input [15:0] a, b,
  output [15:0] o
);
  logic [3:0] g, p;
  logic [3:0]a1, a2, a3, a4, b1, b2, b3, b4;
  logic [3:0]sum1, sum2, sum3, sum4;
  logic [3:0]c;
  assign c[0] = 0;
  assign {a1, a2, a3, a4} = a;
  assign {b1, b2, b3, b4} = b;
  fouradder f1(a4, b4, c[0], sum1, g[0], p[0]);
  c1adder c1(g[0], p[0], c[0], c[1]);
  fouradder f2(a3, b3, c[1], sum2, g[1], p[1]);
  c2adder c2(g[0], p[0], g[1], p[1], c[0], c[2]);
  fouradder f3(a2, b2, c[2], sum3, g[2], p[2]);
  c3adder c3(g[0], p[0], g[1], p[1], g[2], p[2], c[0], c[3]);
  fouradder f4(a1, b1, c[3], sum4, g[3], p[3]);
  assign o = {sum4, sum3, sum2, sum1};
  
endmodule
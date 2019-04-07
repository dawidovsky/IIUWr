module shift(
  input [3:0]i,
  input l,r,
  output [3:0]o
);
  
  logic nolr;
  nor (nolr, l, r);
  
  assign o[0] = (l && 1'b0) || (r && i[1]) || (nolr && i[0]);
  assign o[1] = (l && i[0]) || (r && i[2]) || (nolr && i[1]);
  assign o[2] = (l && i[1]) || (r && i[3]) || (nolr && i[2]);
  assign o[3] = (l && i[2]) || (r && 1'b0) || (nolr && i[3]);
  
endmodule
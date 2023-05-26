//
// Copyright (c) 2023 Sungkyunkwan University
//
// Authors:
// - Jungrae Kim <dale40@skku.edu>
module DMAC_INITIATOR 
(
    input   wire                clk,
    input   wire                rst_n,

    /* FIXME: Declare your input/output port here */

    // Configuration registers
    input    wire    [31:0]    src_addr_i, 
    input    wire    [31:0]    dst_addr_i,
    input    wire    [15:0]    byte_len_i, 
    input    wire              start_i, 
    output   wire              done_o, 

    // AMBA AXI interface  (AR Channel)
    output   wire    [31:0]    araddr_o,    // start address 
    output   wire    [3:0]     arlen_o,     // number of transfers 
    output   wire    [2:0]     arsize_o,    // number of bytes per transfer 
    output   wire    [1:0]     arburst_o,   // burst type 
    output   wire              arvalid_o,
    input    wire              arready_i,

    // AMBA AXI interface  (R Channel)
    input    wire    [31:0]    rdata_i,     // requested chunks of data    
    input    wire    [1:0]     rresp_i,     // whether read succeeded
    input    wire              rlast_i,     // whether last piece of data in burst
    input    wire              rvalid_i,     
    output   wire              rready_o,    

    // AMBA AXI interface (AW Channel)
    output   wire    [31:0]    awaddr_o,    // start address
    output   wire    [3:0]     awlen_o,     // number of transfers 
    output   wire    [2:0]     awsize_o,    // number of bytes per transfer
    output   wire    [1:0]     awburst_o,   // burst type 
    output   wire              awvalid_o, 
    input    wire              awready_i,

    // AMBA AXI interface  (W Channel)
    output   wire    [31:0]    wdata_o,     // chunks of data to write 
    output   wire    [3:0]     wstrb_o,     // send in strobe 
    output   wire              wlast_o,     // whether last piece of data in burst 
    output   wire              wvalid_o,
    input    wire              wready_i,

    // AMBA AXI interface  (B Channel)
    input    wire    [1:0]     bresp_i,
    input    wire              bvalid_i,
    output   wire              bready_o 

);

    /* FIXME: Write your code here (You may use FSM implementation here) */ 

    localparam          S_IDLE    = 3'd0,
                        S_RREQ    = 3'd1, 
                        S_RDATA   = 3'd2,
                        S_WREQ    = 3'd3, 
                        S_WDATA   = 3'd4, 
                        S_WAIT    = 3'd5; 
    
    reg     [2:0]       state,      state_n; 
    
    reg     [31:0]      src_addr,   src_addr_n; 
    reg     [31:0]      dst_addr,   dst_addr_n; 
    reg     [15:0]      cnt,        cnt_n; 
    reg     [3:0]       wcnt,       wcnt_n; 

    reg                 arvalid,
                        rready,
                        awvalid,
                        wvalid,
                        wlast,
                        done; 
    
    wire                fifo_full,
                        fifo_empty; 
    
    reg                 fifo_wren,
                        fifo_rden;
    
    wire    [31:0]      fifo_rdata;
    
    
    DMAC_FIFO    u_fifo
    (
        .clk           (clk),
        .rst_n         (rst_n),
        
        .full_o         (fifo_full),
        .wren_i         (fifo_wren), 
        .wdata_i        (rdata_i), 

        .empty_o        (fifo_empty),
        .rden_i         (fifo_rden), 
        .rdata_o        (fifo_rdata)
    ); 

    // Register updates for each clock 
    always_ff @(posedge clk)
        if(!rst_n) begin
            state        <=    S_IDLE; 
            
            src_addr     <=    32'd0;
            dst_addr     <=    32'd0; 
            cnt          <=    16'd0; 

            wcnt         <=    4'd0; 
        end else begin 
            state        <=    state_n; 

            src_addr     <=    src_addr_n; 
            dst_addr     <=    dst_addr_n;
            cnt          <=    cnt_n; 

            wcnt         <=    wcnt_n; 
        end
    
    // FSM 
    always_comb begin 
        state_n          =    state; 
        
        src_addr_n       =    src_addr;
        dst_addr_n       =    dst_addr;
        cnt_n            =    cnt;
        wcnt_n           =    wcnt;

        arvalid          =    1'b0;
        rready           =    1'b0;
        awvalid          =    1'b0; 
        wvalid           =    1'b0;
        wlast            =    1'b0;
        done             =    1'b0; 

        fifo_wren        =    1'b0;
        fifo_rden        =    1'b0; 

        case (state)
            S_IDLE: begin
            end
        endcase 
    end 

    // Output Assignments 
    assign arvalid_o    = arvalid;
    assign araddr_o     = src_addr;
    assign arlen_o      = (cnt >= 'd64) ? 4'hF : cnt[5:2]-4'h1; 
    assign arsize_o     = 3'b010; 
    assign arburst_o    = 2'b01; 
    assign arvalid_o    = arvalid; 

    assign rready       = rready & !fifo_full;
    
    assign awaddr_o     = dst_addr;
    assign awlen_o      = (cnt >= 'd64) ? 4'hF : cnt[5:2]-4'h1; 
    assign awsize_o     = 3'b010; 
    assign awburst_o    = 2'b01;
    assign awvalid_o    = awvalid;

    assign wdata_o      = fifo_rdata; 
    assign wstrb_o      = 4'b1111;
    assign wlast_o      = wlast;
    assign wvalid_o     = wvalid;

    assign bready_o     = 1'b1; 

    assign done_o       = done;

endmodule

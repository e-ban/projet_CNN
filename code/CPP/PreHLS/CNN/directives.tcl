//  Catapult University Version 10.1b/747384 (Production Release) Wed Nov  1 10:26:06 PDT 2017
//  
//  Copyright (c) Mentor Graphics Corporation, 1996-2017, All Rights Reserved.
//                        UNPUBLISHED, LICENSED SOFTWARE.
//             CONFIDENTIAL AND PROPRIETARY INFORMATION WHICH IS THE
//                 PROPERTY OF MENTOR GRAPHICS OR ITS LICENSORS
//  
//  Running on Linux smancini@ocaepc46 3.16.0-4-amd64 x86_64 aol
//  
//  Package information: SIFLIBS v23.1_2.0, HLS_PKGS v23.1_0.0, 
//                       DesignPad v2.78_1.0
//  
//  This version may only be used for academic purposes.  Some optimizations 
//  are disabled, so results obtained from this version may be sub-optimal.
//  
solution new -state initial
solution options defaults
solution file add ./parameters.h -type CHEADER
solution file add ./CNN.h -type CHEADER
solution file add ./types.h -type CHEADER
solution file add ./convolutionReLU.h -type CHEADER
solution file add ./display.h -type CHEADER
solution file add ./convolution.cpp -type C++
solution file add ./macros_CNN.h -type CHEADER
solution file add ./display.cpp -type C++
solution file add ./CNN.cpp -type C++
solution file add ./maxpool.cpp -type C++
solution file add ./perceptron.cpp -type C++
solution file add ./maxpool.h -type CHEADER
solution file add ./perceptron.h -type CHEADER
solution file add ./masks.h -type CHEADER
solution file add ./macroMask.h -type CHEADER
solution file add ./image.h -type CHEADER
solution file add ./imageNorm.h -type CHEADER
directive set -DESIGN_GOAL area
directive set -OLD_SCHED false
directive set -SPECULATE true
directive set -MERGEABLE true
directive set -REGISTER_THRESHOLD 256
directive set -MEM_MAP_THRESHOLD 32
directive set -LOGIC_OPT false
directive set -FSM_ENCODING none
directive set -REG_MAX_FANOUT 0
directive set -NO_X_ASSIGNMENTS true
directive set -SAFE_FSM false
directive set -ASSIGN_OVERHEAD 0
directive set -UNROLL no
directive set -IO_MODE super
directive set -ARRAY_SIZE 1024
directive set -REGISTER_IDLE_SIGNAL false
directive set -IDLE_SIGNAL {}
directive set -STALL_FLAG false
directive set -TRANSACTION_DONE_SIGNAL true
directive set -DONE_FLAG {}
directive set -READY_FLAG {}
directive set -START_FLAG {}
directive set -BLOCK_SYNC none
directive set -TRANSACTION_SYNC ready
directive set -DATA_SYNC none
directive set -RESET_CLEARS_ALL_REGS true
directive set -CLOCK_OVERHEAD 20.000000
directive set -OPT_CONST_MULTS use_library
directive set -CHARACTERIZE_ROM false
directive set -PROTOTYPE_ROM true
directive set -ROM_THRESHOLD 64
directive set -CLUSTER_ADDTREE_IN_COUNT_THRESHOLD 0
directive set -CLUSTER_OPT_CONSTANT_INPUTS true
directive set -CLUSTER_RTL_SYN false
directive set -CLUSTER_FAST_MODE false
directive set -CLUSTER_TYPE combinational
directive set -COMPGRADE fast
go new
directive set -DESIGN_HIERARCHY ImgProcTest
go compile
solution options set /Flows/Precision/addio false
solution library add mgc_Xilinx-ARTIX-7-2L_beh -- -rtlsyntool Precision -manufacturer Xilinx -family ARTIX-7 -speed -2L -part xc7a50tcsg324-2L
solution library add Xilinx_RAMS
go libraries
directive set -CLOCKS {clk {-CLOCK_PERIOD 10.0 -CLOCK_EDGE rising -CLOCK_UNCERTAINTY 0.0 -CLOCK_HIGH_TIME 5.0 -RESET_SYNC_NAME rst -RESET_ASYNC_NAME arst_n -RESET_KIND sync -RESET_SYNC_ACTIVE high -RESET_ASYNC_ACTIVE low -ENABLE_ACTIVE high}}
go assembly
go extract

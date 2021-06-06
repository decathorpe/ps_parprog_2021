CFLAGS=-std=gnu11 -Wall -Wextra

all: snippet1_all snippet2_all snippet3_all snippet4_all snippet5_all snippet6_all snippet7_all snippet8_all


snippet1_all: snippet1_orig_opto3 snippet1_orig_unopt snippet1_unr2_opto3 snippet1_unr2_unopt snippet1_unr4_opto3 snippet1_unr4_unopt snippet1_comp_opto3 snippet1_comp_unopt

snippet1_orig_opto3: main.c utils.c utils.h snippet1_orig.c
	cc $(CFLAGS) -O3 main.c utils.c snippet1_orig.c -o snippet1_orig_opto3

snippet1_orig_unopt: main.c utils.c utils.h snippet1_orig.c
	cc $(CFLAGS) -O0 main.c utils.c snippet1_orig.c -o snippet1_orig_unopt

snippet1_unr2_opto3: main.c utils.c utils.h snippet1_unr2.c
	cc $(CFLAGS) -O3 main.c utils.c snippet1_unr2.c -o snippet1_unr2_opto3

snippet1_unr2_unopt: main.c utils.c utils.h snippet1_unr2.c
	cc $(CFLAGS) -O0 main.c utils.c snippet1_unr2.c -o snippet1_unr2_unopt

snippet1_unr4_opto3: main.c utils.c utils.h snippet1_unr4.c
	cc $(CFLAGS) -O3 main.c utils.c snippet1_unr4.c -o snippet1_unr4_opto3

snippet1_unr4_unopt: main.c utils.c utils.h snippet1_unr4.c
	cc $(CFLAGS) -O0 main.c utils.c snippet1_unr4.c -o snippet1_unr4_unopt

snippet1_comp_opto3: main.c utils.c utils.h snippet1_orig.c
	cc $(CFLAGS) -O3 -funroll-loops main.c utils.c snippet1_orig.c -o snippet1_comp_opto3

snippet1_comp_unopt: main.c utils.c utils.h snippet1_orig.c
	cc $(CFLAGS) -O0 -funroll-loops main.c utils.c snippet1_orig.c -o snippet1_comp_unopt


snippet2_all: snippet2_orig_opto3 snippet2_orig_unopt snippet2_comp_opto3 snippet2_comp_unopt

snippet2_orig_opto3: main.c utils.c utils.h snippet2.c
	cc $(CFLAGS) -O3 -fno-align-loops main.c utils.c snippet2.c -o snippet2_orig_opto3

snippet2_orig_unopt: main.c utils.c utils.h snippet2.c
	cc $(CFLAGS) -O0 -fno-align-loops main.c utils.c snippet2.c -o snippet2_orig_unopt

snippet2_comp_opto3: main.c utils.c utils.h snippet2.c
	cc $(CFLAGS) -O3 -falign-loops main.c utils.c snippet2.c -o snippet2_comp_opto3

snippet2_comp_unopt: main.c utils.c utils.h snippet2.c
	cc $(CFLAGS) -O0 -falign-loops main.c utils.c snippet2.c -o snippet2_comp_unopt


snippet3_all: snippet3_orig_opto3 snippet3_orig_unopt snippet3_licm_opto3 snippet3_licm_unopt

snippet3_orig_opto3: main.c utils.c utils.h snippet3_orig.c
	cc $(CFLAGS) -O3 main.c utils.c snippet3_orig.c -o snippet3_orig_opto3

snippet3_orig_unopt: main.c utils.c utils.h snippet3_orig.c
	cc $(CFLAGS) -O0 main.c utils.c snippet3_orig.c -o snippet3_orig_unopt

snippet3_licm_opto3: main.c utils.c utils.h snippet3_licm.c
	cc $(CFLAGS) -O3 main.c utils.c snippet3_licm.c -o snippet3_licm_opto3

snippet3_licm_unopt: main.c utils.c utils.h snippet3_licm.c
	cc $(CFLAGS) -O0 main.c utils.c snippet3_licm.c -o snippet3_licm_unopt


snippet4_all: snippet4_orig_opto3 snippet4_orig_unopt snippet4_unsw_opto3 snippet4_unsw_unopt

snippet4_orig_opto3: main.c utils.c utils.h snippet4_orig.c
	cc $(CFLAGS) -O3 main.c utils.c snippet4_orig.c -o snippet4_orig_opto3

snippet4_orig_unopt: main.c utils.c utils.h snippet4_orig.c
	cc $(CFLAGS) -O0 main.c utils.c snippet4_orig.c -o snippet4_orig_unopt

snippet4_unsw_opto3: main.c utils.c utils.h snippet4_unsw.c
	cc $(CFLAGS) -O3 main.c utils.c snippet4_unsw.c -o snippet4_unsw_opto3

snippet4_unsw_unopt: main.c utils.c utils.h snippet4_unsw.c
	cc $(CFLAGS) -O0 main.c utils.c snippet4_unsw.c -o snippet4_unsw_unopt


snippet5_all: snippet5_orig_opto3 snippet5_orig_unopt snippet5_dist_opto3 snippet5_dist_unopt

snippet5_orig_opto3: main.c utils.c utils.h snippet5_orig.c
	cc $(CFLAGS) -O3 main.c utils.c snippet5_orig.c -o snippet5_orig_opto3

snippet5_orig_unopt: main.c utils.c utils.h snippet5_orig.c
	cc $(CFLAGS) -O0 main.c utils.c snippet5_orig.c -o snippet5_orig_unopt

snippet5_dist_opto3: main.c utils.c utils.h snippet5_dist.c
	cc $(CFLAGS) -O3 main.c utils.c snippet5_dist.c -o snippet5_dist_opto3

snippet5_dist_unopt: main.c utils.c utils.h snippet5_dist.c
	cc $(CFLAGS) -O0 main.c utils.c snippet5_dist.c -o snippet5_dist_unopt


snippet6_all: snippet6_orig_opto3 snippet6_orig_unopt snippet6_fuse_opto3 snippet6_fuse_unopt

snippet6_orig_opto3: main.c utils.c utils.h snippet6_orig.c
	cc $(CFLAGS) -O3 main.c utils.c snippet6_orig.c -o snippet6_orig_opto3

snippet6_orig_unopt: main.c utils.c utils.h snippet6_orig.c
	cc $(CFLAGS) -O0 main.c utils.c snippet6_orig.c -o snippet6_orig_unopt

snippet6_fuse_opto3: main.c utils.c utils.h snippet6_fuse.c
	cc $(CFLAGS) -O3 main.c utils.c snippet6_fuse.c -o snippet6_fuse_opto3

snippet6_fuse_unopt: main.c utils.c utils.h snippet6_fuse.c
	cc $(CFLAGS) -O0 main.c utils.c snippet6_fuse.c -o snippet6_fuse_unopt


snippet7_all: snippet7_orig_opto3 snippet7_orig_unopt snippet7_splt_opto3 snippet7_splt_unopt

snippet7_orig_opto3: main.c utils.c utils.h snippet7_orig.c
	cc $(CFLAGS) -O3 main.c utils.c snippet7_orig.c -o snippet7_orig_opto3

snippet7_orig_unopt: main.c utils.c utils.h snippet7_orig.c
	cc $(CFLAGS) -O0 main.c utils.c snippet7_orig.c -o snippet7_orig_unopt

snippet7_splt_opto3: main.c utils.c utils.h snippet7_splt.c
	cc $(CFLAGS) -O3 main.c utils.c snippet7_splt.c -o snippet7_splt_opto3

snippet7_splt_unopt: main.c utils.c utils.h snippet7_splt.c
	cc $(CFLAGS) -O0 main.c utils.c snippet7_splt.c -o snippet7_splt_unopt


snippet8_all: snippet8_orig_opto3 snippet8_orig_unopt snippet8_tile_opto3 snippet8_tile_unopt

snippet8_orig_opto3: main.c utils.c utils.h snippet8_orig.c
	cc $(CFLAGS) -O3 main.c utils.c snippet8_orig.c -o snippet8_orig_opto3

snippet8_orig_unopt: main.c utils.c utils.h snippet8_orig.c
	cc $(CFLAGS) -O0 main.c utils.c snippet8_orig.c -o snippet8_orig_unopt

snippet8_tile_opto3: main.c utils.c utils.h snippet8_tile.c
	cc $(CFLAGS) -O3 main.c utils.c snippet8_tile.c -o snippet8_tile_opto3

snippet8_tile_unopt: main.c utils.c utils.h snippet8_tile.c
	cc $(CFLAGS) -O0 main.c utils.c snippet8_tile.c -o snippet8_tile_unopt


.PHONY: clean
clean:
	rm -f snippet1_orig_* snippet1_unr2_* snippet1_unr4_* snippet1_comp_*
	rm -f snippet2_orig_* snippet2_comp_*
	rm -f snippet3_orig_* snippet3_licm_*
	rm -f snippet4_orig_* snippet4_unsw_*
	rm -f snippet5_orig_* snippet5_dist_*
	rm -f snippet6_orig_* snippet6_fuse_*
	rm -f snippet7_orig_* snippet7_splt_*
	rm -f snippet8_orig_* snippet8_tile_*


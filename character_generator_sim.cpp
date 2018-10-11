#include "Vcharacter_generator.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <time.h>

int main(int argc, char **argv)
{
	// pass command line args into verilator
	Verilated::commandArgs(argc, argv);
	
	// create instance of the translated verilog module
	Vcharacter_generator* cg = new Vcharacter_generator;
	
	// enable and set up trace
	Verilated::traceEverOn(true);
	VerilatedVcdC* tfp = new VerilatedVcdC;	
	cg->trace(tfp, 99);
	tfp->open("trace.vcd");
	
	printf("simulation has started...\n");
	clock_t begin = clock();
	
	for (int i = 0; i < 256*8; i++)
	{
		// set inputs
		cg->ascii = i >> 3;
		cg->row = i & 0x7;
		// posedge clock
		cg->pxlclk = 1;
		cg->eval();
		tfp->dump(i*10);
		
		// negedge clock
		cg->pxlclk = 0;
		cg->eval();
		tfp->dump(i*10+5);
	}
	
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	
	printf("simulation finished in %f seconds!\n", time_spent);
	tfp->close();
	delete tfp;
	delete cg;
	return 0;
}

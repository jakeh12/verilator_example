all:
	@verilator -Wall -trace --cc character_generator.v --exe character_generator_sim.cpp
	@make -s -j -C obj_dir -f Vcharacter_generator.mk Vcharacter_generator
	obj_dir/Vcharacter_generator

clean:
	rm -rf obj_dir
	rm trace.vcd

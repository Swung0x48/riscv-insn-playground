main: main.c asm.S makefile
	riscv64-linux-gnu-gcc -O main.c asm.S -o out -march=rv64gcv_zba -lm -static

inspect: out
	riscv64-linux-gnu-objdump -d out -M hex,no-aliases --show-raw-insn | less

run: out
	qemu-riscv64 -cpu rv64,v=true,zba=true,vlen=128 ./out


{
	"check deducing bounds from const, 1",
	.insns = {
		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_JMP_IMM(BPF_JSGE, BPF_REG_0, 1, 0),
		BPF_ALU64_REG(BPF_SUB, BPF_REG_0, BPF_REG_1),
		BPF_EXIT_INSN(),
	},
	.result = REJECT,
	.errstr = "R0 tried to subtract pointer from scalar",
},
{
	"check deducing bounds from const, 2",
	.insns = {
		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_JMP_IMM(BPF_JSGE, BPF_REG_0, 1, 1),
		BPF_EXIT_INSN(),
		BPF_JMP_IMM(BPF_JSLE, BPF_REG_0, 1, 1),
		BPF_EXIT_INSN(),
		BPF_ALU64_REG(BPF_SUB, BPF_REG_1, BPF_REG_0),
		BPF_EXIT_INSN(),
	},
	.result = ACCEPT,
	.retval = 1,
},
{
	"check deducing bounds from const, 3",
	.insns = {
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_JMP_IMM(BPF_JSLE, BPF_REG_0, 0, 0),
		BPF_ALU64_REG(BPF_SUB, BPF_REG_0, BPF_REG_1),
		BPF_EXIT_INSN(),
	},
	.result = REJECT,
	.errstr = "R0 tried to subtract pointer from scalar",
},
{
	"check deducing bounds from const, 4",
	.insns = {
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_JMP_IMM(BPF_JSLE, BPF_REG_0, 0, 1),
		BPF_EXIT_INSN(),
		BPF_JMP_IMM(BPF_JSGE, BPF_REG_0, 0, 1),
		BPF_EXIT_INSN(),
		BPF_ALU64_REG(BPF_SUB, BPF_REG_1, BPF_REG_0),
		BPF_EXIT_INSN(),
	},
	.result = ACCEPT,
},
{
	"check deducing bounds from const, 5",
	.insns = {
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_JMP_IMM(BPF_JSGE, BPF_REG_0, 1, 1),
		BPF_ALU64_REG(BPF_SUB, BPF_REG_0, BPF_REG_1),
		BPF_EXIT_INSN(),
	},
	.result = REJECT,
	.errstr = "R0 tried to subtract pointer from scalar",
},
{
	"check deducing bounds from const, 6",
	.insns = {
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_JMP_IMM(BPF_JSGE, BPF_REG_0, 0, 1),
		BPF_EXIT_INSN(),
		BPF_ALU64_REG(BPF_SUB, BPF_REG_0, BPF_REG_1),
		BPF_EXIT_INSN(),
	},
	.result = REJECT,
	.errstr = "R0 tried to subtract pointer from scalar",
},
{
	"check deducing bounds from const, 7",
	.insns = {
		BPF_MOV64_IMM(BPF_REG_0, ~0),
		BPF_JMP_IMM(BPF_JSGE, BPF_REG_0, 0, 0),
		BPF_ALU64_REG(BPF_SUB, BPF_REG_1, BPF_REG_0),
		BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_1,
			    offsetof(struct __sk_buff, mark)),
		BPF_EXIT_INSN(),
	},
	.result = REJECT,
	.errstr = "dereference of modified ctx ptr",
	.flags = F_NEEDS_EFFICIENT_UNALIGNED_ACCESS,
},
{
	"check deducing bounds from const, 8",
	.insns = {
		BPF_MOV64_IMM(BPF_REG_0, ~0),
		BPF_JMP_IMM(BPF_JSGE, BPF_REG_0, 0, 1),
		BPF_ALU64_REG(BPF_ADD, BPF_REG_1, BPF_REG_0),
		BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_1,
			    offsetof(struct __sk_buff, mark)),
		BPF_EXIT_INSN(),
	},
	.result = REJECT,
	.errstr = "dereference of modified ctx ptr",
	.flags = F_NEEDS_EFFICIENT_UNALIGNED_ACCESS,
},
{
	"check deducing bounds from const, 9",
	.insns = {
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_JMP_IMM(BPF_JSGE, BPF_REG_0, 0, 0),
		BPF_ALU64_REG(BPF_SUB, BPF_REG_0, BPF_REG_1),
		BPF_EXIT_INSN(),
	},
	.result = REJECT,
	.errstr = "R0 tried to subtract pointer from scalar",
},
{
	"check deducing bounds from const, 10",
	.insns = {
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_JMP_IMM(BPF_JSLE, BPF_REG_0, 0, 0),
		/* Marks reg as unknown. */
		BPF_ALU64_IMM(BPF_NEG, BPF_REG_0, 0),
		BPF_ALU64_REG(BPF_SUB, BPF_REG_0, BPF_REG_1),
		BPF_EXIT_INSN(),
	},
	.result = REJECT,
	.errstr = "math between ctx pointer and register with unbounded min value is not allowed",
},

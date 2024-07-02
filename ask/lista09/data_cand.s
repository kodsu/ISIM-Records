	.file	"data.c"
	.text
	.globl	array
	.bss
	.align 32
	.type	array, @object
	.size	array, 800
array:
	.zero	800
	.globl	bar
	.align 8
	.type	bar, @object
	.size	bar, 8
bar:
	.zero	8
	.globl	some
	.section	.data.rel,"aw"
	.align 32
	.type	some, @object
	.size	some, 38
some:
	.quad	weird
	.long	-3
	.zero	4
	.quad	abc
	.quad	foo
	.string	"efghi"
	.section	.rodata
	.type	abc, @object
	.size	abc, 4
abc:
	.string	"abc"
	.globl	foo
	.data
	.align 2
	.type	foo, @object
	.size	foo, 2
foo:
	.value	314
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits

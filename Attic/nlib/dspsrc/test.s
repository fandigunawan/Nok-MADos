	.TEXT

	st     #0,*(bls)	@ test in test

@	ret
loopey:
	b loopey	

	.DATA
bls:
	.short 0x1234
	.short 0x9999

	.END

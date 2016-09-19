
[PATCH]
Description = Hack to integrate MADos into nokia flashes via 5E0 table
Creator     = g3gg0


[SCRIPT]
5E0: 5E0_space = 10
#
# 3330 should be:
#
#CLC: MADos_startup = 0x00200000 + 0x00290041
#
#
CLC: MADos_startup = 0x00200000 + 0x00140040
A5E: foo = MADos_startup
 
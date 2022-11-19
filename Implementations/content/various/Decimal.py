/**
 * Description: Arbitrary-precision decimals
 */

from decimal import *

ctx = getcontext()
ctx.prec = 28
print(Decimal(1) / Decimal(7)) # 0.1428571428571428571428571429
print(ctx.power(Decimal(10),-30)) # 1E-30
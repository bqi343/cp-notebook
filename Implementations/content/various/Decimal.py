/**
 * Description: Arbitrary-precision decimals
 * Source: https://docs.python.org/3/library/decimal.html
 */

from decimal import *

getcontext().prec = 100 # how many digits of precision
print(Decimal(1) / Decimal(7)) # 0.142857142857...
print(Decimal(10) ** -100) # 1E-100
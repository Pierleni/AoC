import sys
sys.path.append("../")
import libpy.polishReverse as pr

expression = "8/2(2+2)"
exp = pr.parsing(expression)
result = pr.resolve(exp)

print(result)
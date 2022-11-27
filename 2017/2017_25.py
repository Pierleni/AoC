# Begin in state A.
# Perform a diagnostic checksum after 12134527 steps.
#
# In state A:
#   If the current value is 0:
#     - Write the value 1.
#     - Move one slot to the right.
#     - Continue with state B.
#   If the current value is 1:
#     - Write the value 0.
#     - Move one slot to the left.
#     - Continue with state C.
#
# In state B:
#   If the current value is 0:
#     - Write the value 1.
#     - Move one slot to the left.
#     - Continue with state A.
#   If the current value is 1:
#     - Write the value 1.
#     - Move one slot to the right.
#     - Continue with state C.
#
# In state C:
#   If the current value is 0:
#     - Write the value 1.
#     - Move one slot to the right.
#     - Continue with state A.
#   If the current value is 1:
#     - Write the value 0.
#     - Move one slot to the left.
#     - Continue with state D.
#
# In state D:
#   If the current value is 0:
#     - Write the value 1.
#     - Move one slot to the left.
#     - Continue with state E.
#   If the current value is 1:
#     - Write the value 1.
#     - Move one slot to the left.
#     - Continue with state C.
#
# In state E:
#   If the current value is 0:
#     - Write the value 1.
#     - Move one slot to the right.
#     - Continue with state F.
#   If the current value is 1:
#     - Write the value 1.
#     - Move one slot to the right.
#     - Continue with state A.
#
# In state F:
#   If the current value is 0:
#     - Write the value 1.
#     - Move one slot to the right.
#     - Continue with state A.
#   If the current value is 1:
#     - Write the value 1.
#     - Move one slot to the right.
#     - Continue with state E.

import touring_machine

tm = touring_machine.T_Machine(12134527)

tm.run()
tm.tape[tm.cursor] = f"[{tm.tape[tm.cursor]}]"
print(tm.steps, tm.state,tm.tape,tm.cursor)




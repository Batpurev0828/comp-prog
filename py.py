def minimal_first_move(N):
    # Fibonacci sequence F1=1, F2=2, ...
    fibs = [1,2]
    while fibs[-1] <= N:
        fibs.append(fibs[-1] + fibs[-2])
    # greedy Zeckendorf
    rem = N
    used = []
    i = len(fibs)-1
    while rem > 0:
        while fibs[i] > rem:
            i -= 1
        used.append(fibs[i])
        rem -= fibs[i]
    return min(used)

# Examples:
# N=1 -> 1
# N=2 -> 2
# N=3 -> 3
# N=4 -> 1  (4 = 3 + 1 -> smallest summand 1)
# N=7 -> 2  (7 = 5 + 2 -> answer 2)

for i in range(1, 30):
    print(minimal_first_move(i))

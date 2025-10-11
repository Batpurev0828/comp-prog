import sys
from collections import defaultdict

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    
    n = int(data[0])
    m = int(data[1])
    matrix = []
    index = 2
    for i in range(n):
        row = list(map(int, data[index:index+m]))
        index += m
        matrix.append(row)
        
    steps = []
    for _ in range(1000):
        all_same = True
        first_val = matrix[0][0]
        for i in range(n):
            for j in range(m):
                if matrix[i][j] != first_val:
                    all_same = False
                    break
            if not all_same:
                break
        if all_same:
            break
            
        freq_overall = defaultdict(int)
        for i in range(n):
            for j in range(m):
                val = matrix[i][j]
                freq_overall[val] += 1
                
        if not freq_overall:
            break
            
        x = max(freq_overall.items(), key=lambda item: item[1])[0]
        
        best_op = None
        best_increase = -10**9
        
        for i in range(n):
            freq_row = defaultdict(int)
            for j in range(m):
                freq_row[matrix[i][j]] += 1
            if not freq_row:
                continue
            max_freq = max(freq_row.values())
            modes = [val for val, count in freq_row.items() if count == max_freq]
            if len(modes) == 1:
                new_val = modes[0]
                current_x = 0
                for j in range(m):
                    if matrix[i][j] == x:
                        current_x += 1
                new_x = m if new_val == x else 0
                increase = new_x - current_x
                if increase > best_increase:
                    best_increase = increase
                    best_op = ('R', i, new_val)
                    
        for j in range(m):
            freq_col = defaultdict(int)
            for i in range(n):
                freq_col[matrix[i][j]] += 1
            if not freq_col:
                continue
            max_freq = max(freq_col.values())
            modes = [val for val, count in freq_col.items() if count == max_freq]
            if len(modes) == 1:
                new_val = modes[0]
                current_x = 0
                for i in range(n):
                    if matrix[i][j] == x:
                        current_x += 1
                new_x = n if new_val == x else 0
                increase = new_x - current_x
                if increase > best_increase:
                    best_increase = increase
                    best_op = ('C', j, new_val)
                    
        if best_op is None:
            print("Impossible")
            return
            
        op_type, idx, new_val = best_op
        if op_type == 'R':
            for j in range(m):
                matrix[idx][j] = new_val
            steps.append(('R', idx+1))
        else:
            for i in range(n):
                matrix[i][idx] = new_val
            steps.append(('C', idx+1))
    else:
        print("Impossible")
        return
        
    print(len(steps))
    for op in steps:
        print(f"{op[0]} {op[1]}")
        
if __name__ == "__main__":
    main()
def createREF(A, b):
    size = len(A)
    for row in range(size):
        pivot = -1
        for col in range(row,size):
            if abs(A[col][row]) > 0.001:
                if pivot == -1:
                    pivot = col
                elif pivot != -1:
                    k = A[pivot][row] / A[col][row]
                    for i in range(size):
                        A[col][i] *= k
                        A[col][i] -= A[pivot][i]
                    b[col] *= k
                    b[col] -= b[pivot]
        if pivot != -1:
            tmp = A[row].copy()
            A[row] = A[pivot].copy()
            A[pivot] = tmp.copy()
            b[row], b[pivot] = b[pivot], b[row]
    return (A,b)

def substitution(A, b):
    size = len(A)
    res = [0] * size
    par = []
    for _ in range(size):
        par.append([0] * size)
    parameterized = False
    for row in range(size - 1,-1,-1):
        row_res = b[row]
        for col in range(row + 1, size):
            row_res -= A[row][col] * res[col]
        if parameterized:
            for col in range(row + 1, size):
                for param in range(col, size):
                    print(col, param)
                    par[param][row] -= A[row][col] * par[col][param]
        if A[row][row] == 0:
            if abs(row_res) < 0.001:
                parameterized = True
                par[row][row] = 1
            else:
                return None
        else:
            res[row] = row_res / A[row][row]
    if parameterized:
        return (res, par)
    return (res, None)


def elimination(A,b):
    A, b = createREF(A,b)
    print(A)
    return (substitution(A, b))

print(elimination([
    [1,1,-6],
    [1,4,-1],
    [3,-1,-1]
    ],
    [-9,16,-13]))

print(elimination([
    [0,2,6],
    [1,-3,2],
    [-1,4,1]
    ], [14,5,2]))

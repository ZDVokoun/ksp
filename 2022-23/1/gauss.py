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
    for i in range(size):
        par.append([0] * size)
    parameterized = False
    for i in range(size - 1,-1,-1):
        row_res = b[i]
        for j in range(i + 1, size):
            row_res -= A[i][j] * res[j]
        if parameterized:
            pass
        if A[i][i] == 0:
            if abs(row_res) < 0.001:
                parameterized = True
                par[i][i] = 1
            else:
                return None
        else:
            res[i] = row_res / A[i][i]
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

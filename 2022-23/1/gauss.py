def createREF(A, b):
    h = len(A)
    w = len(A[0])
    for c in range(w):
        pivot = -1
        for r in range(c,h):
            if abs(A[r][c]) > 0.001:
                if pivot == -1:
                    pivot = r
                elif pivot != -1:
                    k = A[pivot][c] / A[r][c]
                    for i in range(w):
                        A[r][i] *= k
                        A[r][i] -= A[pivot][i]
                    b[r] *= k
                    b[r] -= b[pivot]
        if pivot != -1:
            tmp = A[c].copy()
            A[c] = A[pivot].copy()
            A[pivot] = tmp.copy()
    return (A,b)

def transposition(A):
    h = len(A)
    w = len(A[0])
    newA = []
    for r in range(h):
        newA.append([])
        for _ in range(w):
            newA[r].append(0)
    for r in range(h):
        for c in range(w):
            newA[r][c] = A[c][r]
    return newA

def elimination(A,b):
    nA, b = createREF(A,b)
    nnA = transposition(nA)
    return createREF(nnA,b)

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

def create_REF(A, b):
    """Convert matrix A and vector b to REF"""
    size = len(A)
    for col in range(size):
        pivot = -1
        # Find a row with pivot with the right index
        for row in range(col,size):
            if abs(A[row][col]) > 0.001:
                if pivot == -1:
                    pivot = row
                elif pivot != -1:
                    k = A[pivot][col] / A[row][col]
                    for i in range(size):
                        A[row][i] *= k
                        A[row][i] -= A[pivot][i]
                    b[row] *= k
                    b[row] -= b[pivot]
        # Swap lines when needed
        if pivot != -1 and pivot != col:
            tmp = A[col].copy()
            A[col] = A[pivot].copy()
            A[pivot] = tmp.copy()
            b[col], b[pivot] = b[pivot], b[col]
    return (A,b)

def substitution(A, b):
    """Backsubstitution for REF matrices without non-basic columns"""
    size = len(A)
    res = [0] * size
    for row in range(size - 1,-1,-1):
        row_res = b[row]
        for col in range(row + 1, size):
            row_res -= A[row][col] * res[col]
        if A[row][row] == 0:
            return None
        else:
            res[row] = row_res / A[row][row]
    return res


def elimination(A,b):
    A, b = create_REF(A,b)
    res = substitution(A, b)
    return res

def main():
    d = int(input())
    A = []
    b = []
    for _ in range(d):
        line = [int(i) for i in input().strip().split()]
        A.append(line[0:d])
        b.append(line[d])
    res = elimination(A, b)
    if res is None:
        print("N")
        return
    print("J")
    print(" ".join([str(i) for i in res]))

if __name__ == "__main__":
    main()

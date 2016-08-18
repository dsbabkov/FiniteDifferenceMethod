#include "TridiagonalMatrixAlgorithm.h"
#include <cassert>

using namespace arma;

vec solveTridiagonal(const mat &matrix, const vec &vector)
{
    assert(matrix.n_cols == matrix.n_rows);
    assert(matrix.n_cols == vector.n_elem);
    assert(vector.n_elem >= 2);

    vec modifiedMainDiagonal(vector.n_elem);
    vec result(vector.n_elem);

    modifiedMainDiagonal[0] = matrix.at(0,0);
    result[0] = vector[0];

    for (uword i = 1; i < vector.n_elem; ++i){
        const double ratio = matrix.at(i, i - 1) / modifiedMainDiagonal[i - 1];
        modifiedMainDiagonal[i] = matrix.at(i, i) - ratio * matrix.at(i - 1, i);
        result[i] = vector[i] - ratio * result[i - 1];
    }

    uword n = vector.n_elem - 1;
    result[n] /= modifiedMainDiagonal[n];

    for (uword i = n - 1; i < n; --i){   // while not overflow
        result[i] = (result[i] - result[i + 1] * matrix.at(i, i + 1)) / modifiedMainDiagonal[i];
    }

    return result;
}

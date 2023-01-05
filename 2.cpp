#include <iostream>
#include <omp.h>
#include <stdexcept>
#include <vector>

int main()
{
    int r1, c1, r2, c2;
    std::cout << "Enter r1 c1 r2 c2 ";
    std::cin >> r1 >> c1 >> r2 >> c2;
    if (r2 != c1) {
        throw std::invalid_argument("r2 and c1 do not match");
    }

    // Use std::vector instead of malloc
    std::vector<int> m1(r1 * c1, 0);
    std::vector<int> m2(r2 * c2, 0);
    std::vector<int> r(r1 * c2, 0);

    // Initialize matrices
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            m1[c1 * i + j] = i + j;
        }
    }
    for (int i = 0; i < r2; i++) {
        for (int j = 0; j < c2; j++) {
            m2[c2 * i + j] = i + j;
        }
    }
    double t = omp_get_wtime();
    #pragma omp parallel for num_threads(1)
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            for (int k = 0; k < r2; k++) {
                r[c2 * i + j] += m1[c1 * i + k] * m2[c2 * k + j];
            }
        }
    }
    t = omp_get_wtime() - t;

    std::cout << "Done, t=" << t << '\n';

    return 0;
}

#include <iostream>
#include <random>
#include <chrono>
#include <cstring>

double f(double x1, double x2) {
    return (x1 * x1 + x2 - 11) * (x1 * x1 + x2 - 11) + (x1 + x2 * x2 - 7) * (x1 + x2 * x2 - 7);
}

int my_rand_disc(int n){
    static long long int seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine generator(seed);
    static std::uniform_int_distribution<int> distribution(0, n - 1);
    return distribution(generator);
}

double my_rand(){
    static long long int seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine generator(seed);
    static std::uniform_real_distribution<double> distribution(-0.5, 0.5);
    return distribution(generator);
}

double parameter_tweak(double x, double g) {
    double t = my_rand() * g * x;
    return x + t;
}

int main() {
    int iteration = 0;
    int count = 0;
    int successes = 0;
    double g = 0.1;
    int n = 2;
    double *x_curr = new double[n];
    double *x_new = new double[n];
    x_curr[0] = -2;
    x_curr[1] = -2;
    double m_curr = f(x_curr[0], x_curr[1]);
    while (iteration < 10000 && g > 0.000001) {
        int choice = my_rand_disc(n);
        double v_new = parameter_tweak(x_curr[choice], g);
        memcpy(x_new, x_curr, sizeof(double) * n);
        x_new[choice] = v_new;
        double m_new = f(x_new[0], x_new[1]);
        if (m_new < m_curr) {
            double * tmp = x_new;
            x_new = x_curr;
            x_curr = tmp;
            m_curr = m_new;
            ++successes;
        }
        if (count == 100) {
            count = 0;
            if (successes < 5) {
                g /= 10;
            }
            successes = 0;
        }
        std::cout << iteration << " " << g << " " << x_curr[0] << " " << x_curr[1] << " " << m_curr << "\n";
        ++iteration;
        ++count;
    }
    std::cout << iteration << "\n";
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 10; // Размерность графа
const int AntCount = 10; // Количество муравьев
const int MaxIterations = 1000; // Максимальное количество итераций
const double EvaporationRate = 0.1; // Коэффициент испарения феромонов
const double MaxPheromone = 0.9;
const double MinPheromone = 0.2;
const double Alpha = 1.0; // Вес феромона
const double Beta = 2.0; // Вес эвристической информации

vector<vector<double>> pheromones(N, vector<double>(N, MinPheromone)); // Инициализация феромонов

// Матрица смежности
vector<vector<double>> graph = {
    {0, 2, 3, 4, 1, 2, 7, 3, 1, 5},
    {2, 0, 4, 1, 3, 5, 2, 1, 6, 4},
    {3, 4, 0, 2, 5, 1, 3, 2, 5, 6},
    {4, 1, 2, 0, 6, 2, 4, 5, 1, 3},
    {1, 3, 5, 6, 0, 3, 2, 4, 7, 2},
    {2, 5, 1, 2, 3, 0, 6, 2, 3, 4},
    {7, 2, 3, 4, 2, 6, 0, 5, 2, 1},
    {3, 1, 2, 5, 4, 2, 5, 0, 4, 2},
    {1, 6, 5, 1, 7, 3, 2, 4, 0, 5},
    {5, 4, 6, 3, 2, 4, 1, 2, 5, 0}
};

vector<int> bestPath;
double bestPathLength = numeric_limits<double>::max();

double calculatePathLength(const vector<int>& path) {
    double length = 0.0;
    for (int i = 0; i < N - 1; ++i) {
        length += graph[path[i]][path[i + 1]];
    }
    length += graph[path[N - 1]][path[0]]; // Замыкаем цикл
    return length;
}

void updatePheromones() {
    // Испарение феромонов
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            pheromones[i][j] *= (1.0 - EvaporationRate);
        }
    }

    // Обновление феромонов на лучшем пути
    for (int i = 0; i < N - 1; ++i) {
        pheromones[bestPath[i]][bestPath[i + 1]] += 1.0 / bestPathLength;
        pheromones[bestPath[i + 1]][bestPath[i]] += 1.0 / bestPathLength;
    }
    pheromones[bestPath[N - 1]][bestPath[0]] += 1.0 / bestPathLength;
    pheromones[bestPath[0]][bestPath[N - 1]] += 1.0 / bestPathLength;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            double value = pheromones[i][j];
            if (value < MinPheromone)
            {
                pheromones[i][j] = MinPheromone;
            }
            if (value > MaxPheromone)
            {
                pheromones[i][j] = MaxPheromone;
            }
        }
    }
}

void antColonyOptimization() {
    for (int iter = 0; iter < MaxIterations; ++iter) {
        for (int ant = 0; ant < AntCount; ++ant) {
            vector<int> path(N);
            for (int i = 0; i < N; ++i) {
                path[i] = i;
            }
            random_shuffle(path.begin() + 1, path.end()); // Перемешиваем путь, начиная с индекса 1

            double pathLength = calculatePathLength(path);

            // Проверка, является ли текущий путь лучшим
            if (pathLength < bestPathLength) {
                bestPathLength = pathLength;
                bestPath = path;
            }
        }

        updatePheromones();

        // Вывод лучшего пути на каждой итерации
        cout << "Iteration " << iter + 1 << ": Best Path Length = " << bestPathLength << endl;
        cout << "Best Path: ";
        for (int i = 0; i < N; ++i) {
            cout << bestPath[i] << " ";
        }
        cout << endl;
    }
}

int main() {
    antColonyOptimization();

    return 0;
}
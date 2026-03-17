#include "crystallize.h"
#include <algorithm>
#include <chrono>
#include <queue>
#include <random>
#include <vector>

Crystallize::Crystallize(uint64_t crystals_count) : crystals_count_(crystals_count) {
}

void Crystallize::Apply(Image &image) {
    size_t n = image.GetHeight();
    size_t m = image.GetWidth();
    std::mt19937 rnd(std::chrono::system_clock::now().time_since_epoch().count());
    std::vector<std::pair<size_t, size_t>> pixels(n * m);
    size_t index = 0;
    for (size_t x = 0; x < n; ++x) {
        for (size_t y = 0; y < m; ++y) {
            pixels[index++] = {x, y};
        }
    }
    std::ranges::shuffle(pixels, rnd);
    std::vector<std::pair<size_t, size_t>> crystals(
        pixels.begin(), pixels.begin() + std::min(static_cast<size_t>(crystals_count_), pixels.size()));
    std::vector<std::vector<size_t>> dist(n, std::vector<size_t>(m, SIZE_T_MAX));
    std::vector<std::vector<size_t>> parent(n, std::vector<size_t>(m, crystals.size() + 1));
    std::queue<std::pair<size_t, size_t>> q;
    for (size_t i = 0; i < crystals.size(); ++i) {
        auto [x, y] = crystals[i];
        dist[x][y] = 0;
        parent[x][y] = i;
        q.emplace(x, y);
    }
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        std::vector<std::pair<size_t, size_t>> neighbours;
        if (x > 0) {
            size_t ux = x - 1;
            size_t uy = y;
            neighbours.emplace_back(ux, uy);
        }
        if (y > 0) {
            size_t ux = x;
            size_t uy = y - 1;
            neighbours.emplace_back(ux, uy);
        }
        if (x + 1 < n) {
            size_t ux = x + 1;
            size_t uy = y;
            neighbours.emplace_back(ux, uy);
        }
        if (y + 1 < m) {
            size_t ux = x;
            size_t uy = y + 1;
            neighbours.emplace_back(ux, uy);
        }
        for (auto [ux, uy] : neighbours) {
            if (dist[ux][uy] > dist[x][y] + 1) {
                dist[ux][uy] = dist[x][y] + 1;
                parent[ux][uy] = parent[x][y];
                q.emplace(ux, uy);
            }
        }
    }
    for (size_t x = 0; x < n; ++x) {
        for (size_t y = 0; y < m; ++y) {
            auto [px, py] = crystals[parent[x][y]];
            image.SetPixel(x, y, image.GetPixel(px, py));
        }
    }
}

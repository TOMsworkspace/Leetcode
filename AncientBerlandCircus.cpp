#include <iostream>
using namespace std;

int main()
{
    double pi = 3.1415926;
    double x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1;
    cin >> x2 >> y2;
    cin >> x3 >> y3;

    int v1x, v1y, v2x, v2y, v3x, v3y;
    v1x = x1 - x2;
    v1y = y1 - y2;
    v2x = x2 - x3;
    v2y = y2 - y3;
    v3x = x1 - x3;
    v3y = y1 - y3;

    int l1 = v1x * v1x + v1y * v1y;
    int l2 = v2x * v2x + v2y * v2y;
    int l3 = v3x * v3x + v3y * v3y;

    double alpha;
    double len;
    if (l1 == l2)
    {
        alpha = acos(-(v1x * v2x + v1y * v2y) / (sqrt(l1) * sqrt(l2)));
        ;
        len = l1;
    }
    else if (l1 == l3)
    {
        alpha = acos((v1x * v3x + v1y * v3y) / (sqrt(l1) * sqrt(l3)));
        len = l1;
    }
    else
    {
        alpha = acos((v2x * v3x + v2y * v3y) / (sqrt(l2) * sqrt(l3)));
        len = l2;
    }

    alpha = max(pi - alpha, alpha);

    double square = len / 2.0 * tan(alpha / 2) * pi / (pi - alpha);

    printf("%.6f", square);
    return 0;
}
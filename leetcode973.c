#include <stdlib.h>

typedef struct {
    int x;
    int y;
    long long dist;
} Point;

long long distanceSq(Point p) {
    return p.dist;
}

void swap(Point* a, Point* b) {
    Point temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Point* points, int left, int right) {
    long long pivot = points[right].dist;
    int i = left;

    for (int j = left; j < right; j++) {
        if (points[j].dist <= pivot) {
            swap(&points[i], &points[j]);
            i++;
        }
    }

    swap(&points[i], &points[right]);
    return i;
}

void quickSelect(Point* points, int left, int right, int k) {
    while (left < right) {
        int pivotIndex = partition(points, left, right);

        if (pivotIndex == k) {
            return;
        } else if (pivotIndex < k) {
            left = pivotIndex + 1;
        } else {
            right = pivotIndex - 1;
        }
    }
}

int** kClosest(int** points, int pointsSize, int* pointsColSize,
               int k, int* returnSize, int** returnColumnSizes) {

    Point* arr = (Point*)malloc(pointsSize * sizeof(Point));

    for (int i = 0; i < pointsSize; i++) {
        arr[i].x = points[i][0];
        arr[i].y = points[i][1];
        arr[i].dist = (long long)points[i][0] * points[i][0]
                    + (long long)points[i][1] * points[i][1];
    }

    quickSelect(arr, 0, pointsSize - 1, k - 1);

    int** result = (int**)malloc(k * sizeof(int*));
    *returnColumnSizes = (int*)malloc(k * sizeof(int));
    *returnSize = k;

    for (int i = 0; i < k; i++) {
        result[i] = (int*)malloc(2 * sizeof(int));
        result[i][0] = arr[i].x;
        result[i][1] = arr[i].y;
        (*returnColumnSizes)[i] = 2;
    }

    free(arr);
    return result;
}

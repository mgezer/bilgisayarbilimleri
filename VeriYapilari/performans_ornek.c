#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Rastgele tam sayılardan oluşan dizi oluşturma fonksiyonu
void generate_random_array(int *arr, int length) {
    for (int i = 0; i < length; i++) {
        arr[i] = rand() % 100 + 1;
    }
}

// Zaman ölçüm fonksiyonu
double measure_time(void (*algorithm)(int*, int), int *arr, int size) {
    clock_t start, end;
    start = clock();
    algorithm(arr, size);
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

// Quick Sort algoritması
void quick_sort(int *arr, int size) {
    // Eğer dizinin boyutu 1 veya daha az ise, sıralamaya gerek yok
    if (size <= 1) return;
    
    // Pivot olarak dizinin ilk elemanını seç
    int pivot = arr[0];
    // Sol ve sağ işaretçileri tanımla
    int left = 0, right = size - 1;
    
    // Sol işaretçi sağ işaretçiyi geçene kadar devam et
    while (left < right) {
        // Sağdan sola doğru, pivot'tan küçük veya eşit eleman bul
        while (arr[right] > pivot && left < right) right--;
        // Eğer bulunduysa, bu elemanı sol tarafa taşı
        if (left < right) arr[left++] = arr[right];
        
        // Soldan sağa doğru, pivot'tan büyük eleman bul
        while (arr[left] <= pivot && left < right) left++;
        // Eğer bulunduysa, bu elemanı sağ tarafa taşı
        if (left < right) arr[right--] = arr[left];
    }
    
    // Pivot'u ortada kalan boş yere yerleştir
    arr[left] = pivot;
    
    // Pivot'un sol tarafını recursive olarak sırala
    quick_sort(arr, left);
    // Pivot'un sağ tarafını recursive olarak sırala
    quick_sort(arr + left + 1, size - left - 1);
}

// Selection Sort algoritması
void selection_sort(int *arr, int size) {
    // Dizinin ilk elemanından başlayarak size-1'e kadar ilerle
    for (int i = 0; i < size - 1; i++) {
        // Şu anki minimum elemanın indeksini i olarak kabul et
        int min_idx = i;
        
        // i+1'den başlayarak dizinin geri kalanını tara
        for (int j = i + 1; j < size; j++) {
            // Eğer daha küçük bir eleman bulunursa
            if (arr[j] < arr[min_idx]) {
                // Yeni minimum indeksi güncelle
                min_idx = j;
            }
        }
        
        // En küçük elemanı, taranmamış kısmın ilk elemanıyla değiştir
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

// Bubble Sort algoritması
void bubble_sort(int *arr, int size) {
    // Dış döngü: Tüm diziyi size-1 kez tarar
    for (int i = 0; i < size - 1; i++) {
        // İç döngü: Dizinin sıralanmamış kısmını tarar
        for (int j = 0; j < size - i - 1; j++) {
            // Eğer mevcut eleman bir sonraki elemandan büyükse
            if (arr[j] > arr[j + 1]) {
                // İki elemanın yerini değiştir
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    srand(time(NULL));  // Rastgele sayı üreteci için seed

    int sizes[] = {10, 20, 50, 100, 1000, 10000, 100000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("Size\tQuick Sort\tBubble Sort\tSelection Sort\n");

    for (int i = 0; i < num_sizes; i++) {
        int size = sizes[i];
        int *arr = (int*)malloc(size * sizeof(int));

        generate_random_array(arr, size);
        double quick_time = measure_time(quick_sort, arr, size);

        generate_random_array(arr, size);
        double bubble_time = measure_time(bubble_sort, arr, size);

        generate_random_array(arr, size);
        double selection_time = measure_time(selection_sort, arr, size);

        printf("%d\t%.6f\t%.6f\t%.6f\n", size, quick_time, bubble_time, selection_time);

        free(arr);
    }

    return 0;
}

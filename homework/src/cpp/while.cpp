/*
 * Einfache Testfälle für Kontrollfluss (while) in C++
 *
 */


int main() {
    // simple while-loop
    bool a = true;
    while (a) {
        print_bool(a);  // 1
        a = false;
    }

    // more complex loop
    int i = 0;
    int arr[5];
    while (i<5) {
        arr[i] = i + 1;
        i = i + 1;
    }
    print_int(arr[0]);  // 1
    print_int(arr[1]);  // 2
    print_int(arr[2]);  // 3
    print_int(arr[3]);  // 4
    print_int(arr[4]);  // 5


    return 0;
}

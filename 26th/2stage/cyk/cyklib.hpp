#include <iostream>
#include <cstdint>
#include <cstdlib>

bool __ended = false;
size_t __n, __counter = 0;
uint64_t *__tab;

void __single_shift() {
    // pomocnicza funkcja, ktorej zawodnik nie powinien uzywac
    if(__n <= 0) {
        std::cout << "Blad! N powinno byc dodatnie, gdy odpalamy single_shift()." << std::endl;
        exit(1);
    }
    uint64_t tmp = __tab[0];
    for(size_t i = 0; i < __n - 1; ++i) {
        __tab[i] = __tab[i+1];
    }
    __tab[__n-1] = tmp;
}
	

void __init() {
    // pomocnicza funkcja, ktorej zawodnik nie powinien uzywac
    if(__ended) {
        std::cout << "Nie mozesz juz zadawac zapytan! Zakoncz program po udzieleniu odpowiedzi." << std::endl;
        exit(1);
    }
    static bool done = false;
    if(done) {
        return;
    }
    done = true;

    size_t x0;
    std::cin >> __n >> x0;

    __tab = new uint64_t[__n];
    for(size_t i = 0; i < __n; ++i) {
        std::cin >> __tab[i];
    }
    for(size_t i = 0; i < x0; ++i) {
        __single_shift();
    }
}

long long circular_shift(int x) {
    if(x < 0 || x > 1000 * 1000 * 1000) {
        std::cout << "Bledna wartosc przesuniecia!" << std::endl;
        exit(1);
    }
    __init();

    __counter += 1;
    if(__counter > 100) {
        std::cout << "Za duzo zapytan!" << std::endl;
        exit(1);
    }
    for(int i = 0; i < x; ++i) {
        __single_shift();
    }

    return __tab[0];
}

void give_answer(int ans) {
    __init();
    __ended = true;

    if(ans == (int) __n) {
        std::cout << "Hurra, poprawny wynik: " << ans << std::endl;
    } else {
        std::cout << "Zle! Wypisano: " << ans << " a oczekiwano: " << __n << std::endl;
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

#define MAX_LINES 1000
#define MAX_LEN 256

char lines[MAX_LINES][MAX_LEN];
int line_count = 1;
char filename[100] = "untitled.txt";

// Fungsi untuk mendeteksi bahasa berdasarkan ekstensi file
void detect_language_and_theme(char *fn, char *lang) {
    char *ext = strrchr(fn, '.');
    if (!ext) {
        strcpy(lang, "Plain Text");
        return;
    }
    if (strcmp(ext, ".py") == 0) strcpy(lang, "Python Script");
    else if (strcmp(ext, ".c") == 0 || strcmp(ext, ".h") == 0) strcpy(lang, "C Source");
    else if (strcmp(ext, ".cpp") == 0) strcpy(lang, "C++ Source");
    else if (strcmp(ext, ".html") == 0 || strcmp(ext, ".htm") == 0) strcpy(lang, "HTML Document");
    else if (strcmp(ext, ".css") == 0) strcpy(lang, "CSS Stylesheet");
    else if (strcmp(ext, ".js") == 0) strcpy(lang, "JavaScript");
    else if (strcmp(ext, ".sh") == 0) strcpy(lang, "Bash/Shell Script");
    else if (strcmp(ext, ".json") == 0) strcpy(lang, "JSON Data");
    else if (strcmp(ext, ".java") == 0) strcpy(lang, "Java Source");
    else sprintf(lang, "%s File", ext + 1); // Otomatis mengenali ekstensi lainnya
}

void save_file() {
    FILE *f = fopen(filename, "w");
    if (f == NULL) return;
    for (int i = 0; i < line_count; i++) {
        fprintf(f, "%s\n", lines[i]);
    }
    fclose(f);
}

void load_file() {
    FILE *f = fopen(filename, "r");
    if (f == NULL) return;
    line_count = 0;
    while (fgets(lines[line_count], MAX_LEN, f) && line_count < MAX_LINES) {
        // Hapus karakter newline di akhir string
        lines[line_count][strcspn(lines[line_count], "\n")] = 0;
        line_count++;
    }
    if (line_count == 0) {
        strcpy(lines[0], "");
        line_count = 1;
    }
    fclose(f);
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        strcpy(filename, argv[1]);
    }

    // Inisialisasi ncurses
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    // Inisialisasi Warna (Tema Biru Modern)
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);  // Warna teks editor
    init_pair(2, COLOR_BLACK, COLOR_CYAN);  // Warna Bar Atas & Bawah

    load_file();

    int cx = 0, cy = 0;
    int ch;
    char lang_type[50];
    detect_language_and_theme(filename, lang_type);

    while (1) {
        clear();
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);

        // 1. Render Top Bar (Informasi File & Deteksi Bahasa)
        attron(COLOR_PAIR(2));
        move(0, 0);
        for (int i = 0; i < max_x; i++) printw(" ");
        mvprintw(0, 1, " NOV EDITOR v1.0 | File: %s | Mode: %s", filename, lang_type);
        attroff(COLOR_PAIR(2));

        // 2. Render Isi File
        attron(COLOR_PAIR(1));
        for (int i = 0; i < line_count; i++) {
            if (i < max_y - 2) {
                mvprintw(i + 1, 0, "%s", lines[i]);
            }
        }
        attroff(COLOR_PAIR(1));

        // 3. Render Bottom Bar
        attron(COLOR_PAIR(2));
        move(max_y - 1, 0);
        for (int i = 0; i < max_x; i++) printw(" ");
        mvprintw(max_y - 1, 1, " [CTRL+S] Save File  |  [CTRL+X] Exit Editor");
        attroff(COLOR_PAIR(2));

        // Pindahkan kursor ke posisi mengetik
        move(cy + 1, cx);
        refresh();

        ch = getch();

        // Logika Tombol Kontrol
        if (ch == 24) { // CTRL + X untuk Keluar
            break;
        } 
        else if (ch == 19) { // CTRL + S untuk Simpan
            save_file();
        } 
        else if (ch == KEY_BACKSPACE || ch == 127 || ch == 8) { // Backspace
            if (cx > 0) {
                memmove(&lines[cy][cx - 1], &lines[cy][cx], strlen(&lines[cy][cx]) + 1);
                cx--;
            } else if (cy > 0) {
                cx = strlen(lines[cy - 1]);
                strcat(lines[cy - 1], lines[cy]);
                for (int i = cy; i < line_count - 1; i++) {
                    strcpy(lines[i], lines[i + 1]);
                }
                line_count--;
                cy--;
            }
        } 
        else if (ch == '\n' || ch == KEY_ENTER) { // Enter
            if (line_count < MAX_LINES) {
                for (int i = line_count; i > cy + 1; i--) {
                    strcpy(lines[i], lines[i - 1]);
                }
                strcpy(lines[cy + 1], &lines[cy][cx]);
                lines[cy][cx] = '\0';
                cy++;
                cx = 0;
                line_count++;
            }
        } 
        else if (ch >= 32 && ch <= 126) { // Karakter Huruf/Angka/Simbol
            if (strlen(lines[cy]) < MAX_LEN - 1) {
                memmove(&lines[cy][cx + 1], &lines[cy][cx], strlen(&lines[cy][cx]) + 1);
                lines[cy][cx] = ch;
                cx++;
            }
        }
    }

    endwin();
    return 0;
}

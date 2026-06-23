# 🌌 NOV - Terminal Text Editor v1.0

**NOV** adalah aplikasi teks editor berbasis terminal (CLI) yang sangat ringan, cepat, dan minimalis. Ditulis langsung menggunakan **bahasa C** dan memanfaatkan pustaka **ncurses** untuk menghasilkan antarmuka visual yang modern di dalam terminal Anda.

Dikembangkan secara resmi oleh **Antherpic Technologies © 2026**.

---

## 🚀 Cara Instalasi di Berbagai Sistem Operasi

Aplikasi ini bisa dijalankan di sistem operasi apa pun yang memiliki terminal dan compiler C (`gcc` atau `clang`). Ikuti perintah di bawah ini sesuai dengan sistem operasi yang Anda gunakan:

### 1. Android (Termux)
Buka Termux Anda, lalu salin dan jalankan perintah ini:
```bash
# Install komponen yang dibutuhkan
pkg install git clang ncurses-dev -y

# Clone repository langsung dari github Antherpic
git clone [https://github.com/Antherpic/Nov-Code-Editor-Version-1.0.git](https://github.com/Antherpic/Nov-Code-Editor-Version-1.0.git)
cd Nov-Code-Editor-Version-1.0

# Kompilasi kode C menjadi file biner siap pakai
clang nov.c -lncurses -o nov

# Pindahkan ke folder sistem agar bisa dipanggil dari mana saja
mv nov $PREFIX/bin/


LINUX

# Install compiler dan library ncurses
sudo apt update
sudo apt install git gcc libncurses5-dev libncursesw5-dev -y

# Clone repository
git clone [https://github.com/Antherpic/Nov-Code-Editor-Version-1.0.git](https://github.com/Antherpic/Nov-Code-Editor-Version-1.0.git)
cd Nov-Code-Editor-Version-1.0

# Kompilasi kode
gcc nov.c -lncurses -o nov

# Pindahkan ke direktori bin global sistem Linux
sudo mv nov /usr/local/bin/

MAC OS

# Install ncurses lewat brew
brew install ncurses

# Clone repository
git clone [https://github.com/Antherpic/Nov-Code-Editor-Version-1.0.git](https://github.com/Antherpic/Nov-Code-Editor-Version-1.0.git)
cd Nov-Code-Editor-Version-1.0

# Kompilasi kode
gcc nov.c -lncurses -o nov

# Pindahkan ke folder biner global Mac
sudo mv nov /usr/local/bin/


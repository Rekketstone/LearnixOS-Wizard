# LearnixOS-Wizard
Startup wizard for LearnixOS

### Dependencies:
- gtkmm-4.0
- c++ compiler (clang or gcc)

### Compiling steps:
```bash
gcc++ wiz.cpp `pkg-config --cflags --libs gtkmm-4.0` -o wizard
# or
clang++ wiz.cpp `pkg-config --cflags --libs gtkmm-4.0` -o wizard
```

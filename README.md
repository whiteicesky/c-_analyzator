Для корректной работоспособности проекта необходимо использование
wxWidgets - бесплатной кроссплатформенной библиотеки с открытым кодом
для создания приложений с GUI (Графическим интерфейсом пользователя)

Для начала работы необходимо установить wxWidgets:
1) Откройте PowerShell.
2) cd C:\Users\Admin\Desktop
3) git clone https://github.com/microsoft/vcpkg
4) cd vcpkg
5) .\bootstrap-vcpkg.bat
6).\vcpkg integrate install
7) .\vcpkg install wxwidgets:x64-windows

Создай проект и подключи main.cpp:
Visual Studio → File → New → Project → Empty Project (C++).
Platform: x64 (вверху в VS: Debug|x64).
В Solution Explorer: правый клик по проекту → Add → Existing Item... → выбери C:\Users\Admin\Desktop\1\main.cpp.
В свойствах проекта: Linker → System → SubSystem → Windows (/SUBSYSTEM:WINDOWS).
Запусти:
Build → Build Solution (Ctrl+Shift+B).
Debug → Start Without Debugging (Ctrl+F5).
Должно открыться окно “Анализатор текста…”.
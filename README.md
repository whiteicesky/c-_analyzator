# Анализатор текста на C++

## Описание
- GUI-приложение на C++ с использованием wxWidgets.
- Подсчитывает количество символов (с пробелами и без), слов и предложений в введённом тексте.
- Умеет считать вхождения заданного слова (регистр игнорируется) или символа (регистр учитывается).

## Требования
- Windows
- Microsoft Visual Studio
- Установленная библиотека wxWidgets

## Установка
 - Для корректной работоспособности проекта необходимо использование
wxWidgets - бесплатной кроссплатформенной библиотеки с открытым кодом
для создания приложений с GUI (Графическим интерфейсом пользователя)

Для начала работы необходимо установить wxWidgets:
Откройте PowerShell.
  
'cd C:\Users\Admin\Desktop'
   
'''git clone https://github.com/microsoft/vcpkg'''
   
'''cd vcpkg'''
   
'''.\bootstrap-vcpkg.bat'''

'''.\vcpkg integrate install'''

'''.\vcpkg install wxwidgets:x64-windows'''

Создай проект и подключи main.cpp:
Visual Studio → File → New → Project → Empty Project (C++).
Platform: x64 (вверху в VS: Debug|x64).
В Solution Explorer: правый клик по проекту → Add → Existing Item... → выбери C:\Users\Admin\Desktop\1\main.cpp.
В свойствах проекта: Linker → System → SubSystem → Windows (/SUBSYSTEM:WINDOWS).
Запусти:
Build → Build Solution (Ctrl+Shift+B).
Debug → Start Without Debugging (Ctrl+F5).
Должно открыться окно “Анализатор текста…”.

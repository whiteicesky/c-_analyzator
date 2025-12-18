#include <wx/wx.h> // подключаем главный заголовок wxWidgets для работы с GUI
#include <string> // подключаем библиотеку std::string для хранения текста
#include <sstream> // подключаем строковые потоки для разбиения текста на слова
#include <algorithm> // подключаем алгоритмы стандартной библиотеки
#include <cctype> // подключаем функции для работы с символами

std::string to_lower_copy(const std::string& source) { // создаём копию строки с переводом в нижний регистр
    std::string lowered = source; // сохраняем исходную строку в отдельной переменной
    std::transform(lowered.begin(), lowered.end(), lowered.begin(), [](unsigned char ch) { // проходим по каждому символу и применяем преобразование
        return static_cast<char>(std::tolower(ch)); // переводим текущий символ в нижний регистр
        }); // завершаем выполнение std::transform для всей строки
    return lowered; // возвращаем полученную строку в нижнем регистре
} // конец функции to_lower_copy

int count_chars_with_spaces(const std::string& text) { // считаем символы с пробелами
    return static_cast<int>(text.size()); // возвращаем размер строки как количество символов
} // конец функции count_chars_with_spaces

int count_chars_without_spaces(const std::string& text) { // считаем символы без пробелов
    int count = 0; // создаём счётчик символов без пробелов
    for (char ch : text) { // перебираем каждый символ текста
        if (ch != ' ') { // проверяем, что символ не является пробелом
            ++count; // увеличиваем счётчик для непустого символа
        } // конец проверки на пробел
    } // конец цикла по символам
    return count; // возвращаем количество символов без пробелов
} // конец функции count_chars_without_spaces

int count_words(const std::string& text) { // считаем количество слов
    bool in_word = false; // флаг, показывающий, находимся ли внутри слова
    int count = 0; // создаём счётчик слов
    for (char ch : text) { // перебираем каждый символ
        if (ch == ' ') { // проверяем, встретился ли пробел
            in_word = false; // сбрасываем флаг, если вышли из слова
        }
        else { // если символ не пробел
            if (!in_word) { // проверяем, начали ли мы новое слово
                ++count; // увеличиваем счётчик при входе в новое слово
                in_word = true; // отмечаем, что находимся внутри слова
            } // конец проверки начала слова
        } // конец ветвления по пробелу
    } // конец цикла по символам
    return count; // возвращаем количество слов
} // конец функции count_words

int count_sentences(const std::string& text) { // считаем количество предложений
    int count = 1; // создаём счётчик предложений
    for (char ch : text) { // перебираем каждый символ
        if (ch == '.' || ch == '!' || ch == '?') { // проверяем, является ли символ знаком конца предложения
            ++count; // увеличиваем счётчик при нахождении конца предложения
        } // конец проверки на знак завершения
    } // конец цикла по символам
    return count; // возвращаем количество предложений
} // конец функции count_sentences

int count_word_occurrences(const std::string& text, const std::string& word) { // считаем количество вхождений полного слова
    if (word.empty()) { // проверяем, что искомое слово не пустое
        return 0; // возвращаем ноль, если слово не задано
    } // конец проверки на пустую строку
    std::string lowered_text = to_lower_copy(text); // переводим исходный текст в нижний регистр
    std::string lowered_word = to_lower_copy(word); // переводим искомое слово в нижний регистр
    std::istringstream stream(lowered_text); // создаём строковый поток для разбиения текста по пробелам
    std::string current; // переменная для текущего слова из потока
    int count = 0; // счётчик вхождений слова
    while (stream >> current) { // читаем каждое слово из потока
        if (current == lowered_word) { // сравниваем текущее слово с искомым
            ++count; // увеличиваем счётчик при совпадении
        } // конец проверки совпадения слов
    } // конец цикла по словам
    return count; // возвращаем количество найденных вхождений
} // конец функции count_word_occurrences

int count_char_occurrences(const std::string& text, char ch) { // считаем количество вхождений символа
    int count = 0; // создаём счётчик символа
    for (char current : text) { // перебираем каждый символ текста
        if (current == ch) { // проверяем совпадение с искомым символом
            ++count; // увеличиваем счётчик при совпадении
        } // конец проверки совпадения
    } // конец цикла по символам
    return count; // возвращаем количество вхождений символа
} // конец функции count_char_occurrences

class TextAnalyzerFrame : public wxFrame { // создаём класс окна приложения, наследуемый от wxFrame
public: // открытая секция класса
    TextAnalyzerFrame() // конструктор окна без параметров
        : wxFrame(nullptr, wxID_ANY, "Анализатор текста", wxDefaultPosition, wxSize(600, 500)) { // инициализируем базовый класс заголовком, позицией и размером
        wxPanel* panel = new wxPanel(this, wxID_ANY); // создаём панель для размещения элементов
        wxBoxSizer* main_sizer = new wxBoxSizer(wxVERTICAL); // создаём вертикальный сайзер для общего размещения

        wxStaticText* intro = new wxStaticText(panel, wxID_ANY, "Введите текст, затем выберите режим и нажмите кнопку:"); // добавляем поясняющий текст
        main_sizer->Add(intro, 0, wxALL | wxEXPAND, 5); // помещаем пояснение в сайзер с отступом

        wxStaticText* text_label = new wxStaticText(panel, wxID_ANY, "Текст для анализа:"); // метка для поля ввода текста
        main_sizer->Add(text_label, 0, wxLEFT | wxRIGHT | wxTOP, 5); // добавляем метку с отступами

        input_text_ctrl_ = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(-1, 120), wxTE_MULTILINE); // создаём многострочное поле для текста
        main_sizer->Add(input_text_ctrl_, 1, wxALL | wxEXPAND, 5); // добавляем поле с расширением по ширине и высоте

        wxStaticText* mode_label = new wxStaticText(panel, wxID_ANY, "Режим подсчёта:"); // метка для выбора режима
        main_sizer->Add(mode_label, 0, wxLEFT | wxRIGHT | wxTOP, 5); // добавляем метку с отступами

        wxArrayString modes; // создаём массив строк для вариантов режима
        modes.Add("Слово"); // добавляем вариант подсчёта слова
        modes.Add("Символ"); // добавляем вариант подсчёта символа
        mode_choice_ = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, modes); // создаём выпадающий список режимов
        mode_choice_->SetSelection(0); // выставляем выбор по умолчанию на подсчёт слова
        main_sizer->Add(mode_choice_, 0, wxALL | wxEXPAND, 5); // добавляем список в сайзер

        wxStaticText* search_label = new wxStaticText(panel, wxID_ANY, "Введите слово или символ для поиска:"); // метка для поля поиска
        main_sizer->Add(search_label, 0, wxLEFT | wxRIGHT | wxTOP, 5); // добавляем метку

        search_input_ = new wxTextCtrl(panel, wxID_ANY); // создаём однострочное поле ввода для слова или символа
        main_sizer->Add(search_input_, 0, wxALL | wxEXPAND, 5); // добавляем поле в сайзер

        wxButton* analyze_button = new wxButton(panel, wxID_ANY, "Рассчитать"); // создаём кнопку запуска анализа
        main_sizer->Add(analyze_button, 0, wxALL | wxEXPAND, 5); // добавляем кнопку с растяжением по ширине

        wxStaticText* stats_title = new wxStaticText(panel, wxID_ANY, "Статистика:"); // метка заголовка статистики
        main_sizer->Add(stats_title, 0, wxLEFT | wxRIGHT | wxTOP, 5); // добавляем метку заголовка

        stats_output_ = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY); // создаём поле для вывода статистики в режиме только чтение
        main_sizer->Add(stats_output_, 1, wxALL | wxEXPAND, 5); // добавляем поле статистики с расширением

        wxStaticText* result_title = new wxStaticText(panel, wxID_ANY, "Результат поиска:"); // метка заголовка результатов поиска
        main_sizer->Add(result_title, 0, wxLEFT | wxRIGHT | wxTOP, 5); // добавляем метку результатов

        result_output_ = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY); // создаём поле для вывода результата поиска
        main_sizer->Add(result_output_, 0, wxALL | wxEXPAND, 5); // добавляем поле результата в сайзер

        panel->SetSizer(main_sizer); // устанавливаем сайзер для панели

        analyze_button->Bind(wxEVT_BUTTON, &TextAnalyzerFrame::OnAnalyze, this); // привязываем обработчик нажатия кнопки к методу класса
    } // конец конструктора TextAnalyzerFrame

private: // закрытая секция класса
    void OnAnalyze(wxCommandEvent&) { // обработчик нажатия кнопки расчёта
        std::string input_text = input_text_ctrl_->GetValue().ToStdString(); // получаем текст из многострочного поля в std::string
        int chars_with_spaces = count_chars_with_spaces(input_text); // вычисляем символы с пробелами
        int chars_without_spaces = count_chars_without_spaces(input_text); // вычисляем символы без пробелов
        int words = count_words(input_text); // вычисляем количество слов
        int sentences = count_sentences(input_text); // вычисляем количество предложений

        wxString stats_text; // создаём строку wxString для вывода статистики
        stats_text << "Символов с пробелами: " << chars_with_spaces << "\n"; // добавляем строку с количеством символов с пробелами
        stats_text << "Символов без пробелов: " << chars_without_spaces << "\n"; // добавляем строку с количеством символов без пробелов
        stats_text << "Количество слов: " << words << "\n"; // добавляем строку с количеством слов
        stats_text << "Количество предложений: " << sentences << "\n"; // добавляем строку с количеством предложений
        stats_output_->SetValue(stats_text); // выводим сформированную статистику в поле

        int selection = mode_choice_->GetSelection(); // получаем выбранный режим подсчёта
        std::string search_value = search_input_->GetValue().ToStdString(); // получаем введённое слово или символ

        if (selection == 0) { // проверяем, выбран ли режим поиска слова
            if (search_value.empty()) { // проверяем, задано ли слово
                wxMessageBox("Введите слово для поиска.", "Ошибка", wxICON_WARNING | wxOK, this); // показываем предупреждение об отсутствии слова
                return; // прекращаем обработку при отсутствии слова
            } // конец проверки пустого слова
            int occurrences = count_word_occurrences(input_text, search_value); // считаем вхождения слова
            wxString result_text; // создаём строку результата
            result_text << "Слово встречается: " << occurrences << " раз(а)."; // формируем текст результата для слова
            result_output_->SetValue(result_text); // выводим результат в поле
        }
        else if (selection == 1) { // проверяем, выбран ли режим поиска символа
            if (search_value.empty()) { // проверяем, задан ли символ
                wxMessageBox("Введите символ для поиска.", "Ошибка", wxICON_WARNING | wxOK, this); // показываем предупреждение об отсутствии символа
                return; // прекращаем обработку при отсутствии символа
            } // конец проверки пустого символа
            char target_char = search_value[0]; // берём первый символ введённой строки
            int occurrences = count_char_occurrences(input_text, target_char); // считаем вхождения символа
            wxString result_text; // создаём строку результата
            result_text << "Символ '" << target_char << "' встречается: " << occurrences << " раз(а)."; // формируем текст результата для символа
            result_output_->SetValue(result_text); // выводим результат в поле
        }
        else { // обработка некорректного выбора режима
            wxMessageBox("Выберите режим подсчёта (слово или символ).", "Ошибка", wxICON_WARNING | wxOK, this); // показываем предупреждение о неверном режиме
        } // конец ветвления по режиму
    } // конец функции OnAnalyze

    wxTextCtrl* input_text_ctrl_ = nullptr; // указатель на поле ввода текста
    wxChoice* mode_choice_ = nullptr; // указатель на список выбора режима
    wxTextCtrl* search_input_ = nullptr; // указатель на поле ввода слова или символа
    wxTextCtrl* stats_output_ = nullptr; // указатель на поле вывода статистики
    wxTextCtrl* result_output_ = nullptr; // указатель на поле вывода результата
}; // конец класса TextAnalyzerFrame

class TextAnalyzerApp : public wxApp { // создаём класс приложения, наследуемый от wxApp
public: // открытая секция класса
    bool OnInit() override { // переопределяем метод инициализации приложения
        TextAnalyzerFrame* frame = new TextAnalyzerFrame(); // создаём экземпляр главного окна
        frame->Show(true); // показываем окно пользователю
        return true; // сообщаем системе, что инициализация прошла успешно
    } // конец метода OnInit
}; // конец класса TextAnalyzerApp

wxIMPLEMENT_APP(TextAnalyzerApp); // макрос, определяющий точку входа и создающий экземпляр приложения

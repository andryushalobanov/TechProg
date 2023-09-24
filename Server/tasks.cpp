#include "tasks.h"


QString to_binary(int n, int bits) {
    QString res;
    for (int i = bits - 1; i >= 0; i--) {
        res += (n & (1 << i)) ? '1' : '0';
    }
    return res;
}

int twoToRandomPower() {
    int value = QRandomGenerator::global()->bounded(2, 5);
    return qPow(2, value);
}

std::vector<bool> randomFunctionValues(int length) {
    std::vector<bool> function_values;
    for (int i; i < length; i++) {
        function_values.push_back(QRandomGenerator::global()->generateDouble() > 0.5);
    }
    return function_values;
}

QString vectorToString(std::vector<bool> functionValues) {
    QString result;
    for (auto value: functionValues) {
        result += value ? '1' : '0';
    }
    return result;
}





QString сalc_sdnf(std::vector<bool> f) {
    QString result;
    int n = log2(f.size());
    bool first_term = true;
    for (int i = 0; i < int(f.size()); ++i) {
    if (f[i]) {
        if (!first_term) {
            result += "+";
        } else {
            first_term = false;
        }
        QString binary = to_binary(i, n);
        for (int j = 0; j < n; ++j) {
            if (binary[j] == '0') {
                result += QString("!x%1").arg(j + 1);
            } else {
                result += QString("x%1").arg(j + 1);
            }
            if (j < n - 1) {
                //result += "&";
                result += ""; //&
            }
        }
    }
}
if (first_term) {
    result += "0";
}
return result;
}

QString calc_sknf(std::vector<bool> f) {
    QString result;
    int n = log2(f.size());
    bool first_term = true;
    for (int i = 0; i < int(f.size()); ++i) {
        if (!f[i]) {
            if (!first_term) {
                result += ""; //&
            } else {
                first_term = false;
            }
            QString binary = to_binary(i, n);
            result += "(";
            for (int j = 0; j < n; ++j) {
                if (binary[j] == '0') {
                    result +=  QString("x%1").arg(j + 1);
                } else {
                    result += QString("!x%1").arg(j + 1);
                }
                if (j < n - 1) {
                    result += "+";
                }
            }
            result += ")";
        }
    }
    if (first_term) {
        result += "1";
    }
    return result;
}


QString karno_map(std::vector<bool> f) {

    std::vector<std::vector<bool>> map(4, std::vector<bool>(4));

    // заполняем карту Карно
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            map[i][j] = f[i * 4 + j];
        }
    }

    // обрабатываем строки
    for (int i = 0; i < 4 - 2; ++i) {
        for (int j = 0; j < 4; j += 4) {
            std::swap(map[i][j + 2], map[i][j + 3]);
        }
    }

    // обрабатываем последние две строки
    for (int j = 0; j < 4; j += 4) {
        std::swap(map[4 - 2][j + 2], map[4 - 2][j + 3]);
        std::swap(map[4 - 1][j + 2], map[4 - 1][j + 3]);
    }
    std::swap(map[4 - 2], map[4 - 1]);

    // формируем строку для вывода
    QString output;
    for (const auto& row : map) {
        for (bool b : row) {
            output += b ? '1' : '0';
        }
        output += "\\";
    }

    return output;
}




QVariantMap TaskManukyan() {
    QVariantMap task;
    int length = twoToRandomPower();
    std::vector<bool> functionValues = randomFunctionValues(length);
    QString answer = сalc_sdnf(functionValues);
        task["text"] = QString("Найдите СДНФ по данному вектору значений: %1")
              .arg(vectorToString(functionValues));
    task["answer"] = answer;
    return task;
}


QVariantMap TaskPanteleev() {

    QVariantMap task;
    int n = twoToRandomPower(); // Генерируем случайное значение n от 2^1 до 2^4
    std::vector<bool> functionValues = randomFunctionValues(n); // Создаем вектор
    QString answer = calc_sknf(functionValues);
    task["text"] = QString("Найдите СКНФ по данному вектору значений: %1")
                       .arg(vectorToString(functionValues));
    task["answer"] = answer;
    return task;

}

QVariantMap TaskMihailov() {
    QVariantMap task;
    int length = 16;
    std::vector<bool> functionValues = randomFunctionValues(length);
    QString answer = karno_map(functionValues);

    task["text"] = QString("Найдите карту Карно по данному вектору значений: %1\n\nВ ответе строки таблицы разделяйте через '\'")
                       .arg(vectorToString(functionValues));
    task["answer"] = answer;
    return task;
}





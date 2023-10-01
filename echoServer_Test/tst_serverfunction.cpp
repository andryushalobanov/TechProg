#include <QtTest>
#include <vector>
#include <../server/tasks.cpp>
#include <../server/tasks.h>

class serverfunction : public QObject
{
    Q_OBJECT

public:
    serverfunction();

private slots:
    void test_case_Manukyan_sdnf();
    void test_case_Panteleev_sknf();
    void test_case_Mikhailov_karno();
};

void serverfunction::test_case_Manukyan_sdnf()
{
    std::vector<bool> input =  {0, 1, 0, 1, 0, 1, 1, 1};
    QVERIFY(сalc_sdnf(input) == "!x1!x2x3+!x1x2x3+x1!x2x3+x1x2!x3+x1x2x3");
}

void serverfunction::test_case_Panteleev_sknf()
{
    std::vector<bool> input =  {0, 1, 0, 1, 0, 1, 1, 1};
    QVERIFY(calc_sknf(input) == "(x1+x2+x3)(x1+!x2+x3)(!x1+x2+x3)");
}

void serverfunction::test_case_Mikhailov_karno()
{
    std::vector<bool> input =  {0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};
    QVERIFY(karno_map(input) == "0110\\0111\\0111\\0110\\");
}

QTEST_APPLESS_MAIN(serverfunction)
#include "tst_serverfunction.moc"

#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>

// 23. Составить   программу  поиска  записи  с  включением  в
// сильно   ветвящемся   Б - дереве   порядка  N.Б - дерево  должно
// храниться и обрабатываться в файле с прямым доступом(13).

// Коды клавиш
#define KEY_UP 72
#define KEY_DOWN 80
#define ENTER 13
#define BACKSPACE 8

// Константы для изменения конфигурации программы
const int TREE_DEGREE = 2;
const int MAX_RECORD_LENGTH = 32;
const int MAX_LEVEL = 5;

const int MAX_VISIBLE_TREE_LINES = 25;

// Константа, используемая в программе(менять не рекомендуется)
const int MAX_PAGE_LENGTH = MAX_LEVEL + 1 + 2 + MAX_RECORD_LENGTH * TREE_DEGREE * 2;

struct Record
{
public:
    int number;
    std::string info;
    std::string to_string()
    {
        return std::to_string(number) + " " + info;
    }
    bool operator < (const Record& record) const
    {
        return number < record.number;
    }
};

std::ostream& operator << (std::ostream& os, const Record& record)
{
    return os << record.number << " " << record.info;
}

struct Page
{
public:
    int level;
    std::vector<Record> records;
    Page()
    {
        level = 0;
        records = {};
    }

    Page(int l, const Record& r)
    {
        level = l;
        records = { r };
    }

    std::string to_string()
    {
        std::ostringstream result;
        for (int i = 0; i < level; i++)
        {
            result << "-";
        }
        for (Record record : records)
        {
            result << record << " ";
        }
        return result.str();
    }
};

std::ostream& operator << (std::ostream& os, const Page& page)
{
    std::string levelMark;
    for (int i = 0; i < page.level; i++)
    {
        levelMark += "-";
    }
    std::ostringstream recordsString;
    for (Record r : page.records)
    {
        recordsString << r << " ";
    }
    if (page.level == 0)
    {
        return os << recordsString.str();
    }
    return os << levelMark << " " << recordsString.str();
}

std::string PageToString(const Page& page)
{
    std::ostringstream stream;
    if (page.level > 0)
    {
        for (int i = 0; i < page.level; i++)
        {
            stream << "-";
        }
        stream << " ";
    }
    for (Record record : page.records)
    {
        stream << record << " ";
    }
    return stream.str();
}

Page StringToPage(const std::string& str)
{
    Page page;
    std::istringstream strStream(str);
    if (str[0] == '-')
    {
        std::string levelMark;
        strStream >> levelMark;
        page.level = levelMark.length();
    }
    std::string num, info;
    while (strStream >> num >> info)
    {
        Record newRecord = { std::stoi(num), info };
        page.records.push_back(newRecord);
    }
    return page;
}

Page ReadPage(const std::string& fileName, int elementLineNumber)
{
    std::fstream file;
    file.open(fileName, std::ios_base::in);
    file.seekg(elementLineNumber * (MAX_PAGE_LENGTH + 1));
    char buffer[MAX_PAGE_LENGTH];
    file.read(buffer, MAX_PAGE_LENGTH);
    file.close();
    std::string strPage(buffer);
    if (strPage.empty() || strPage.find_first_not_of(' ') == std::string::npos) {
        return Page();
    }
    Page currentPage = StringToPage(strPage);
    return currentPage;
}

void WritePage(const std::string& fileName, int elementLineNumber, const Page& page)
{
    std::fstream file;
    file.open(fileName, std::ios::in | std::ios::out | std::ios::ate);
    std::string newPageStr = PageToString(page);
    char newBuffer[MAX_PAGE_LENGTH](MAX_PAGE_LENGTH, ' ');
    std::copy(newPageStr.begin(), newPageStr.end(), newBuffer);
    file.seekp(elementLineNumber * (MAX_PAGE_LENGTH + 1));
    file.write(newBuffer, MAX_PAGE_LENGTH - 2);
    file.write("\r\n", 2);
    file.close();
}

bool ElementIsLeaf(const std::string& fileName, int elementLineNumber)
{
    Page currentPage = ReadPage(fileName, elementLineNumber);
    Page nextPage = ReadPage(fileName, elementLineNumber + 1);
    return currentPage.level >= nextPage.level;
}

Record FindMiddle(std::vector<Record>& records, const Record& record)
{
    Record middle;
    if (records[TREE_DEGREE - 1] < record)
    {
        if (records[TREE_DEGREE] < record)
        {
            middle = records[TREE_DEGREE];
            records[TREE_DEGREE] = record;
            return middle;
        }
        return record;
    }
    middle = records[TREE_DEGREE - 1];
    records[TREE_DEGREE - 1] = record;
    std::sort(records.begin(), records.end());
    return middle;
}

int GetParent(const std::string& fileName, int childLineNumber)
{
    if (childLineNumber == 0)
    {
        return -1; // No parent, element is root
    }
    Page childPage = ReadPage(fileName, childLineNumber);
    int parentLineNumber = childLineNumber - 1;
    Page parentPage = ReadPage(fileName, parentLineNumber);
    while (parentPage.level >= childPage.level && parentLineNumber > 0)
    {
        parentLineNumber--;
        parentPage = ReadPage(fileName, parentLineNumber);
    }
    return parentLineNumber;
}

int GetCertainChild(const std::string& fileName, int parentLineNumber, int childNum)
{
    if (ElementIsLeaf(fileName, parentLineNumber))
    {
        return parentLineNumber;
    }
    int coundOfChilds = 1;
    Page parentPage = ReadPage(fileName, parentLineNumber);
    int childLineNumber = parentLineNumber + 1;
    Page childPage = ReadPage(fileName, childLineNumber);
    while (coundOfChilds < childNum && childPage.records.size() > 0)
    {
        childLineNumber++;
        childPage = ReadPage(fileName, childLineNumber);
        if (childPage.level == parentPage.level + 1)
        {
            coundOfChilds++;
        }
    }
    return childLineNumber;
}

void AddRecordToPage(Page& page, const Record& record)
{
    if (page.records.size() < TREE_DEGREE * 2)
    {
        page.records.push_back(record);
        std::sort(page.records.begin(), page.records.end());
    }
}

void InsertPageWithoutReplace(const std::string& fileName, int lineToInsert, const Page& page, int levelIncrement)
{
    int currentLine = lineToInsert;
    Page nextPage = ReadPage(fileName, lineToInsert);
    Page temp = nextPage;
    temp.level += levelIncrement;
    WritePage(fileName, currentLine++, page);
    while (nextPage.records.size() > 0)
    {
        nextPage = ReadPage(fileName, currentLine);
        WritePage(fileName, currentLine++, temp);
        temp = nextPage;
        temp.level += levelIncrement;
    }
}

void InsertElementWithOverflow(const std::string& fileName, int pageNumber, const Record& record)
{
    Page currentPage = ReadPage(fileName, pageNumber);
    Record middle = FindMiddle(currentPage.records, record);

    Page page1, page2;
    page1.level = currentPage.level;
    page2.level = currentPage.level;
    for (int i = 0; i < TREE_DEGREE; i++)
    {
        AddRecordToPage(page1, currentPage.records[i]);
        AddRecordToPage(page2, currentPage.records[i + TREE_DEGREE]);
    }

    int parentLineNumber = GetParent(fileName, pageNumber);

    if (ElementIsLeaf(fileName, pageNumber) && pageNumber > 0)
    {
        WritePage(fileName, pageNumber, page1);
        InsertPageWithoutReplace(fileName, pageNumber + 1, page2, 0);
    }
    else
    {
        if (pageNumber == 0) // root
        {
            Page newRoot;
            AddRecordToPage(newRoot, middle);
            InsertPageWithoutReplace(fileName, 0, newRoot, 1);
            page1.level++;
            page2.level++;
            pageNumber++;
        }
        WritePage(fileName, pageNumber, page1);
        int page2LineNumber = GetCertainChild(fileName, pageNumber, TREE_DEGREE + 2);
        if (page2LineNumber > pageNumber)
        {
            InsertPageWithoutReplace(fileName, page2LineNumber, page2, 0);
        }
        else // root was the only element
        {
            WritePage(fileName, pageNumber + 1, page2);
        }
    }

    if (pageNumber == 0)
    {
        return;
    }

    Page parentPage = ReadPage(fileName, parentLineNumber);

    if (parentPage.records.size() == TREE_DEGREE * 2)
    {
        InsertElementWithOverflow(fileName, parentLineNumber, middle);
    }
    else
    {
        AddRecordToPage(parentPage, middle);
        WritePage(fileName, parentLineNumber, parentPage);
    }
}

void FindOrInsertElement(const std::string& fileName, int treeElement)
{
    std::fstream file;
    int currentLine = 0;
    bool foundOrInserted = false;
    while (!foundOrInserted)
    {
        Page currentPage = ReadPage(fileName, currentLine);
        for (Record record : currentPage.records)
        {
            if (record.number == treeElement)
            {
                std::cout << "Element found. Info: " << record.info << std::endl;
                foundOrInserted = true;
                _getch();
                break;
            }
        }
        if (foundOrInserted)
        {
            break;
        }
        if (ElementIsLeaf(fileName, currentLine))
        {
            std::string info;
            std::cout << "Enter info: ";
            std::cin >> info;
            Record record = { treeElement, info };
            if (currentPage.records.size() < TREE_DEGREE * 2)
            {
                std::string recordStr = currentPage.to_string();
                AddRecordToPage(currentPage, record);
                WritePage(fileName, currentLine, currentPage);
                foundOrInserted = true;
            }
            else
            {
                // Разделение страницы
                InsertElementWithOverflow(fileName, currentLine, record);
                foundOrInserted = true;
            }
        }
        else
        {
            int delta = 1;
            for (Record record : currentPage.records)
            {
                if (record.number > treeElement)
                {
                    break;
                }
                delta++;
            }
            currentLine = GetCertainChild(fileName, currentLine, delta);
        }
    }
}

void DrawTree(const std::string& fileName, int startPos)
{
    Page page;
    std::string pageStr;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(console, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(console, &cursorInfo);
    SetConsoleTextAttribute(console, BACKGROUND_GREEN | BACKGROUND_BLUE);
    std::cout << "Use arrows to move tree field of view." << std::endl;
    SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED);
    system("COLOR ");
    for (int i = 0; i < MAX_VISIBLE_TREE_LINES; i++)
    {
        page = ReadPage(fileName, startPos + i);
        std::cout << page << std::endl;
    }
    page = ReadPage(fileName, startPos + MAX_VISIBLE_TREE_LINES);
    if (page.records.size() > 0)
    {
        std::cout << "...";
    }
    std::cout << std::endl;
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

int GetTreeSize(const std::string& fileName)
{
    int curPos = 0;
    Page page = ReadPage(fileName, curPos);
    while (page.records.size() > 0)
    {
        curPos++;
        page = ReadPage(fileName, curPos);
    }
    return curPos;
}

void WorkWithTree(const std::string& fileName, bool& toExit)
{
    std::fstream file(fileName);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open " + fileName);
    }
    int treeElement = 1;
    int currentPos = 0;
    int currentTreeSize = 0;
    std::string recordStr;
    while (treeElement > 0)
    {
        bool finishedWriting = false;
        recordStr = "";
        while (!finishedWriting)
        {
            system("CLS");
            currentTreeSize = GetTreeSize(fileName);
            DrawTree(fileName, currentPos);
            std::cout << "Enter record to seek: " << recordStr;
            int c = _getch();

            if (c == 0 || c == 224) {
                c = _getch();
                switch (c) {
                case KEY_UP:
                    if (currentPos > 0) {
                        currentPos--;
                    }
                    break;
                case KEY_DOWN:
                    if (currentPos < currentTreeSize - MAX_VISIBLE_TREE_LINES) {
                        currentPos++;
                    }
                    break;
                }
            }
            else {
                switch (c) {
                case BACKSPACE:
                    if (recordStr.size() > 0) {
                        recordStr.erase(recordStr.size() - 1, 1);
                    }
                    break;
                case ENTER:
                    finishedWriting = true;
                    std::cout << std::endl;
                    break;
                default:
                    recordStr += c;
                    break;
                }
            }
        }
        treeElement = std::stoi(recordStr);

        if (treeElement)
        {
            FindOrInsertElement(fileName, treeElement);
        }
        else
        {
            toExit = true;
            throw std::runtime_error("Wrong input or 0. Press any key to exit program.");
        }
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    bool toExit = false;
    while (!toExit)
    {
        system("CLS");
        try
        {
            std::cout << "Enter file name: ";
            std::string fileName;
            std::cin >> fileName;
            WorkWithTree(fileName, toExit);
        }
        catch (std::exception e)
        {
            std::cout << e.what() << std::endl;
            _getch();
        }
    }
    return EXIT_SUCCESS;
}

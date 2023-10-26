#pragma once
#include "BasicWidget.h"
#include"Configure.h"
#include"PushButton.h"
class Table :
    public BasicWidget
{
public:
    Table(int row = 0, int col = 0);
    ~Table();
    void clear() { m_datas.clear(); }
    void setRowCount(int row);
    void setColCount(int col);
    int rowCount()const { return m_datas.size(); }
    int colCount()const { return m_cols; }
    void setHeader(const std::string& header);
    void insertData(const std::string& data);

    void show();
    void drawTableGrid();
    void drawButton();
    void drawTableData();
    void drawHeader();
    static std::vector<std::string> split(std::string str, char separator = '\t');

    void updatePage();

    void event()override;
private:
    int m_rows;
    int m_cols;

    int m_gridW;
    int m_gridH;

    int m_tw;
    int m_th;

    std::string m_header;
    std::vector<std::string> m_datas;

private:
    int m_curPage;//当前
    int m_maxPage;//最大
    int m_extraData;

    PushButton* m_prevBtn;
    PushButton* m_nextBtn;
    PushButton* m_firstBtn;
    PushButton* m_lastBtn;
};


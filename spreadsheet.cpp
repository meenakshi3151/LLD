#include<bits/stdc++.h>
using namespace std;

class Spreadsheet{
    public:
    int findcellrowindex(string cell) {
        return stoi(cell.substr(1)) - 1;
    }
    int findcellcolindex(string cell) {
        return cell[0]-'A';
    }
    int findindexofplus(string exp) {
    for (int i = 0; i < exp.size(); i++) {
        if (exp[i] == '+') return i;
    }
    return -1;
}
    vector<vector<int>> sheet;
    Spreadsheet(int rows) {
        vector<vector<int>> excelsheet(rows, vector<int>(26, 0));
        sheet=excelsheet;
    }
    void setcell(string cell, int value) {
        int cellrow = findcellrowindex(cell);
        int cellcol = findcellcolindex(cell);
        sheet[cellrow][cellcol]=value;
    }
    void resetcell(string cell, int value) {
        int cellrow = findcellrowindex(cell);
        int cellcol = findcellcolindex(cell);
        sheet[cellrow][cellcol]=value;
    }
    int getcell(string cell) {
        int cellrow = findcellrowindex(cell);
        int cellcol = findcellcolindex(cell);
        return sheet[cellrow][cellcol];
    }
    int calcexp(string exp){
        int ind = findindexofplus(exp);
        string cell1 = exp.substr(1, ind-1);
        string cell2 = exp.substr(ind+1);
        int cellvalue1 = getcell(cell1);
        int cellvalue2 = getcell(cell2);
        return cellvalue2+cellvalue1;
    }
 };
 
 int main() {
     int rows;
     cin>>rows;
     Spreadsheet* sheet = new Spreadsheet(rows);
     sheet->setcell("B23", 100);
     sheet->setcell("A21", 100);
     int value = sheet->getcell("A21");
     cout<<"value at A21: "<<value<<endl;
     int exp = sheet->calcexp("=B23+A21");
     cout<<"value of exp: "<<exp<<endl;
     sheet->resetcell("A21", 200);
     int val = sheet->getcell("A21");
     cout<<"value at A21: "<<val<<endl;
     return 0;
 }
 
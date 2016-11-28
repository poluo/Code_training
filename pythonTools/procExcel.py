import xlrd
import re
import os
#from openpyxl import load_workbook
#wb = load_workbook('1.xlsx')
#print(wb.get_sheet_names())
#ws=wb['AVL 162003120.00-49']

#检查位号
def check_pos_mark(table1,table2):
        #位号比较,ptable1 必须相等
        print("位号检查，可能有问题的会打印出来，以供检查,")
        print("还有些小问题，等待完善：")
        ptable1=set(table1.get_col(7))
        ptable2=set(table2.get_col(8))
        #print(ptable2)
        ptable2=table2.proc_cell(ptable2)
        #print(ptable2)
        tmp=ptable1-ptable2&ptable1
        if tmp!=set():
            print(tmp)
        else:
            pass
#检查用量填写
def check_usage(table):
    num=table.num_row
    print("用量填写检查，可能有问题的会打印出来，以供检查：")
    for i in range(2,num+1):
        val=table.rd_cell(i,8)
        usage=table.rd_cell(i,7)
        if isinstance(val,str) and isinstance(usage,float):
            length=len(re.split(',',val))
            if usage!=length*1000.0:
                print(val,end="")
                print(usage,end="   ")        


            
class procExcel(object):
    """docstring for procExcel"""
    def __init__(self,file_name,sheet_name):
        self.wb=xlrd.open_workbook(file_name)
        self.ws=self.wb.sheet_by_name(sheet_name)
        self.num_row=self.ws.nrows
        self.num_col=self.ws.ncols
        print('row: %d col: %d' % (self.num_row,self.num_col))
    #读取单元格内数，第几行第几列
    def rd_cell(self,num_row,num_col):
        return self.ws.cell_value(num_row-1,num_col-1)
    #获取整列的值,去除重复数，返回数组
    def get_col(self,num_col):
        tmp_list=self.ws.col_values(num_col-1)
        #ret_list=list(set(tmp_list))
        ret_list={}.fromkeys(tmp_list).keys()
        return ret_list
    #处理单元格内逗号
    def proc_cell(slef,table):
        table=list(table)
        for cell in table:
            if isinstance(cell,str):
                if ',' in cell:
                    tmp=re.split(',',cell)
                    table.remove(cell)
                    table=table+tmp
        return set(table)
    #获取整行的值,返回数组
    def get_row(self,num_row):
        return self.ws.row_values(num_row-1)
    
    

if __name__=='__main__':
    mytable1=procExcel('1.xlsx','AVL 162003120.00-49')
    mytable2=procExcel('A.xlsx','A')
    check_pos_mark(mytable1,mytable2)
    check_usage(mytable2)
    os.system("pause")
    
    

    

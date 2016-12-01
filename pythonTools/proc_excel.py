import xlrd
import re
import os
import logging

#检查位号
def check_pos_mark(table1,table2):
        #位号比较,ptable1 必须相等
        logging.warning("位号检查，可能有问题的会打印出来，以供检查,")
        logging.warning("还有些小问题，等待完善：")
        ptable1=set(table1.get_col_with_filter(7))
        ptable2=set(table2.get_col_with_filter(8))
        logging.debug("table1 cell:\n{0}".format(ptable1))
        ptable2=proc_list(ptable2)
        logging.debug("table2 cell:\n{0}".format(ptable2))
        diff_patern1=ptable1-ptable2&ptable1
        diff_patern2=ptable2-ptable2&ptable1
        if diff_patern1!=set() or diff_patern2!=set():
            logging.warning("两个表中不相同的地方:")
            if diff_patern1!=set():
                logging.warning(diff_patern1)
            if diff_patern2!=set():
                logging.warning(diff_patern2)
        else:
            logging.warning("似乎没什么问题")
#检查用量填写
def check_usage(table):
    num=table.num_row
    logging.warning("用量填写检查，可能有问题的会打印出来，以供检查：")
    for i in range(2,num+1):
        val=table.rd_cell(i,8)
        usage=table.rd_cell(i,7)
        if isinstance(val,str) and isinstance(usage,float):
            length=len(re.split(',',val))
            if usage!=length*1000.0:
                logging.warning("{0}:{1}  ".format(val,usage))    


def get_source_type_and_mark_number(source_table):
    '''获取源excel文件中mark_number(标号)对应的type(厂商和型号)，一个标号对应多个type，返回字典'''
    num=source_table.num_row
    ret={}
    for i in range(9,num):
        line=source_table.get_row(i)[3:6]
        if line[0]=="":
            continue
        if line[0] in ret:
            adict=ret[line[0]]
            adict[line[1]]=line[2]
        else:
            adict={line[1]:line[2]}
        ret[line[0]]=adict

    
    return ret

def check_type_and_mark_number(source_table,target_table):
    '''获取目标excel中mark_number(标号)对应的type(厂商和型号)，一个标号对应一个type,返回字典'''
    source_dict=get_source_type_and_mark_number(source_table)
    #logging.debug("source excel:\n")
    #logging.debug(source_dict)
    num=target_table.num_row
    ret_dict={}
    invalid_list=[]
    vendor_dict={'NXP':'NXP','PANJ':'PANJIT','VISH':'VISHAY','KOA':'KOA SPEER','NXP':'NXP','OMRO':'OMRON','HF':'HONG FA','PANA':'PANASONIC','NICH':'NICHICON','RUBY':'RUBYCON','EPCO':'EPCOS','ELIT':'ELITE','HPC':'HOLY STONE','TDK':'TDK','AVX':'AVX','KEME':'KEMET','MURA':'MURATA','SAMS':'SAMSUNG','WALS':'WALSIN','YAGE':'YAGEO'}
    for i in range(2,num+1):
        tmp_str=target_table.rd_cell(i,5)
        if '_' in tmp_str and '\\' in tmp_str:
            model=re.split('_',tmp_str).pop()
            vendor=tmp_str[0:tmp_str.index('\\')]
            try:
                vendor=vendor_dict[vendor]
            except KeyError as e:
                print(vendor)
                continue
            mark_number=target_table.rd_cell(i,8)
            if not isinstance(mark_number,str):
                continue
            if ',' in mark_number:
                mark_number=re.split(',',mark_number)
                for sub_number in mark_number:
                    if sub_number in source_dict:
                        adict=source_dict[sub_number]
                        if vendor in adict:
                            if model_is_match(model,adict[vendor].upper()):
                                pass
                            else:
                                logging.debug("型号可能有问题 {0} {1} {2} ".format(sub_number,vendor,model))
                                invalid_list.append(mark_number)
                                break
                        else:
                            logging.debug("制造商可能有问题{0} {1} ".format(sub_number,vendor))
                            invalid_list.append(mark_number)
                            break
                    else:
                        logging.debug("标号可能有问题 {0} ".format(sub_number))
                        invalid_list.append(mark_number)
                        break

            else:
                if mark_number in source_dict:
                    adict=source_dict[mark_number]
                    if vendor in adict:
                        if model_is_match(model,adict[vendor].upper()):
                            pass
                        else:
                            logging.debug("型号可能有问题 {0} {1} {2} ".format(mark_number,vendor,model))
                            invalid_list.append(mark_number)
                    else:
                        logging.debug("制造商可能有问题{0} {1} ".format(mark_number,vendor))
                        invalid_list.append(mark_number)
                else:
                    logging.debug("标号可能有问题 {0} ".format(mark_number))
                    invalid_list.append(mark_number)
                
           
        else:
            #cell is invalid
            pass
    #logging.debug(invalid_list)


def model_is_match(src,tar):
    src=src.replace(' ','')
    tar=tar.replace(' ','')
    tmp=tar
    if '^' in tmp:
        tmp=tar.replace('^','.')
        if None==re.match(tmp,src):
            return False
        else:
            return True
    elif '*' in tmp:
        tmp=tar.replace('*','.')
        if None==re.match(tmp,src):
            return False
        else:
            return True
    elif '*' in src:
        tmp=src.replace('*','.')
        if None==re.match(tmp,tar):
            return False
        else:
            return True
    else:
        if None==re.match(tmp,src):
            return False
        else:
            return True


def check_priority(source_table):
    MARK_NUMVER_COL_NUMBER=8
    PRIORITY_COL_NUMBER=10
    mark_number_dict={}
    invalid_list=[]
    mark_number_list=source_table.get_col_no_filter(MARK_NUMVER_COL_NUMBER)
    for num in mark_number_list:
        if num=="" or not isinstance(num,str):
            continue
        elif "," in num:
            alist=re.split(',',num)
            for i in alist:
                if i in mark_number_dict:
                    mark_number_dict[i]=mark_number_dict[i]+1
                else:
                    mark_number_dict[i]=1
        else:
            if num in mark_number_dict:
                mark_number_dict[num]=mark_number_dict[num]+1
            else:
                mark_number_dict[num]=1
    
    cal=lambda x:(1+x)*x/2
    for k,v in mark_number_dict.items():
        mark_number_dict[k]=cal(mark_number_dict[k])
    #logging.debug(mark_number_list)
    #logging.debug('\n')
    #logging.debug(mark_number_dict)

    for i in range(2,source_table.num_row+1):
        tmp_mark=source_table.rd_cell(i,MARK_NUMVER_COL_NUMBER)
        if tmp_mark=="" or not isinstance(tmp_mark,str):
            continue
        tmp_priority=source_table.rd_cell(i,PRIORITY_COL_NUMBER)
        if tmp_priority=="":
            tmp_priority=1
        if ',' in tmp_mark:
            tmp_mark=re.split(',',tmp_mark)
            for number in tmp_mark:
                mark_number_dict[number]=mark_number_dict[number]-tmp_priority
        else:
            mark_number_dict[tmp_mark]=mark_number_dict[tmp_mark]-tmp_priority
    for k,v in mark_number_dict.items():
        if v!=0:
            invalid_list.append(k)
    logging.debug(u"优先级检查，可能有错误的:\n{0}".format(invalid_list))

#将数组内含逗号的元素分开为多个元素，返回集合
def proc_list(table):
    table=list(table)
    for cell in table:
        if isinstance(cell,str):
            if ',' in cell:
                tmp=re.split(',',cell)
                table.remove(cell)
                table=table+tmp
    return set(table)
class ProcExcel(object):
    """docstring for procExcel"""
    def __init__(self,file_name,sheet_name):
        self.wb=xlrd.open_workbook(file_name)
        self.ws=self.wb.sheet_by_name(sheet_name)
        self.num_row=self.ws.nrows
        self.num_col=self.ws.ncols
        #print('row: %d col: %d' % (self.num_row,self.num_col))
    #读取单元格值，第几行第几列
    def rd_cell(self,num_row,num_col):
        return self.ws.cell_value(num_row-1,num_col-1)
    #获取整列的值,去除重复数，返回数组
    def get_col_with_filter(self,num):
        tmp_list=self.ws.col_values(num-1)
        #ret_list=list(set(tmp_list))
        ret_list={}.fromkeys(tmp_list).keys()
        return ret_list
    #获取整列的值,不去除重复数，返回数组
    def get_col_no_filter(self,num):
        tmp_list=self.ws.col_values(num-1)
        return tmp_list
    #获取整行的值,返回数组
    def get_row(self,num):
        return self.ws.row_values(num-1)
    

if __name__=='__main__':
    logging.basicConfig(level=logging.DEBUG,
                format='%(message)s',
                datefmt='%S',
                filename='debug.txt',
                filemode='w')
    console = logging.StreamHandler()
    console.setLevel(logging.INFO)
    formatter = logging.Formatter('%(message)s')
    console.setFormatter(formatter)
    logging.getLogger('').addHandler(console)
    source_excel=ProcExcel('1.xlsx','AVL 162003120.00-49')
    target_excel=ProcExcel('A.xlsx','A')
    check_pos_mark(source_excel,target_excel)
    check_usage(target_excel)
    check_type_and_mark_number(source_excel,target_excel)
    check_priority(target_excel)

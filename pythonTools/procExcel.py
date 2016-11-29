import xlrd,re,os,logging
#from openpyxl import load_workbook
#wb = load_workbook('1.xlsx')
#print(wb.get_sheet_names())
#ws=wb['AVL 162003120.00-49']

#检查位号
def check_pos_mark(table1,table2):
        #位号比较,ptable1 必须相等
        logging.warning("位号检查，可能有问题的会打印出来，以供检查,")
        logging.warning("还有些小问题，等待完善：")
        ptable1=set(table1.get_col(7))
        ptable2=set(table2.get_col(8))
        logging.debug("table1 cell:\n{0}".format(ptable1))
        ptable2=table2.proc_cell(ptable2)
        logging.debug("table2 cell:\n{0}".format(ptable2))
        tmp1=ptable1-ptable2&ptable1
        tmp2=ptable2-ptable2&ptable1
        if tmp1!=set() or tmp2!=set():
            logging.warning("两个表中不相同的地方:\n{0}\n{1}".format(tmp1,tmp2))
        else:
            pass
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

def get_part_num_struct(table):
    num=table.num_row
    ret={}
    for i in range(9,num):
        line=mytable1.get_row(i)
        line=line[3:6]
        print(line)
        if line[0] in ret:
            alist=ret[line[0]]
        else:
            alist=[] 
        tmp={}
        tmp[line[1]]=line[2]
        alist.append(tmp)
        ret[line[0]]=alist
    logging.debug(pat)
    return pat
def get_des(table):
    num=table.num_row
    ret={}
    for i in range(2,num):
        des=table.rd_cell(i,5)
        if '_' in des:
            des=re.split('_',des)
            des=des[len(des)-1]
            pos=table.rd_cell(i,8)
            if ',' in pos:
                pos=re.split(',',pos)
                for j in len(pos):
                    ret[pos]=des
            else:
                ret[pos]=des
    return ret

class procExcel(object):
    """docstring for procExcel"""
    def __init__(self,file_name,sheet_name):
        self.wb=xlrd.open_workbook(file_name)
        self.ws=self.wb.sheet_by_name(sheet_name)
        self.num_row=self.ws.nrows
        self.num_col=self.ws.ncols
        #print('row: %d col: %d' % (self.num_row,self.num_col))
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
    #logging.debug("directory moved from {0} to {1}".format(event.src_path,event.dest_path))
    mytable1=procExcel('1.xlsx','AVL 162003120.00-49')
    mytable2=procExcel('A.xlsx','A')
    check_pos_mark(mytable1,mytable2)
    check_usage(mytable2)
    #os.system("pause")
    #get_part_num_struct(mytable1)
    #s1="IKOHHSK^OLJ"
    #s1.replace('^','.')
    #if None==re.match(s1,s2):
       # pass
    #else:
        #pass

    
        
    
    

    

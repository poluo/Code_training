from os.path import basename
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.application import MIMEApplication
import smtplib
class send_email():
    email_obj= MIMEMultipart('alternative')
    def __init__(self):
         self.mail_host='smtp.163.com'
         self.mail_user='ckfg0779@163.com'
         self.mail_passwd='ckfg0779'
    def send(self):
        try:
            server = smtplib.SMTP_SSL(self.mail_host,465)  
            server.connect(self.mail_host)  
            server.login(self.mail_user,self.mail_passwd)  
            server.sendmail(self.mail_user,self.email_obj['To'], self.email_obj.as_string())  
            server.close()  
            return True  
        except Exception as e:  
            print(e)
            return False
    #structure new message with subject ,from describer and send to who list
    def new_email(self,sub='test',from_des='python',to_list='xxx@email.com'):
        self.email_obj['Subject'] = sub
        self.email_obj['From'] = from_des
        self.email_obj['To'] = ";".join(to_list)

    #structure txt messsage
    def txt_message(self,content):
        self.email_obj.attach(MIMEText(content))
    #structure html messsage
    def html_message(self,content,describer_text):
        content='<a href="'+content+'"> '+describer_text+'</a>'
        msg2 = MIMEText(content,_subtype='html',_charset='utf8')
        self.email_obj.attach(msg2)
    #structure att messsage
    def attachment_message(self,filename):
        msg3 = MIMEApplication(open(filename, 'rb').read(), Name=basename(filename))
        msg3["Content-Type"] = 'application/octet-stream'
        msg3["Content-Disposition"] = 'attachment; filename='+basename(filename)
        self.email_obj.attach(msg3)
        
if __name__=='__main__':
    sub='title one'
    sender='python'
    receivers=['mufovassedd-6072@yopmail.com']
    mail_obj=send_email()
    mail_obj.new_email(sub,sender,receivers)
    
    mail_obj.html_message('http://www.cnblogs.com/xiaowuyi','link')
    mail_obj.attachment_message('d:\\cmd.c')
    # According to RFC 2046, the last part of a multipart message, in this case
    # the HTML message, is best and preferred.
    mail_obj.txt_message('describer')
    mail_obj.attachment_message('d:\\megre.c')
    if mail_obj.send():
        print('发送成功')
    else:
        print('发送失败')


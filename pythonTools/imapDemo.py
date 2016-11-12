import imaplib
import email
import os
def parse_email(msg, i):
    """Parse email message and save content & attachments to file
    
    :param msg: mail message
    :param i: ordinal number
    """
    #global result_file
    
    # Parse and save email content and attachments
    for part in msg.walk():
        if not part.is_multipart():
            filename = part.get_filename()
            content = part.get_payload(decode=True)
            
            if filename:  # Attachment
                # Decode filename
                pass
            else:  # Main content
                print(content)

count=0
mail_obj=imaplib.IMAP4_SSL('imap.163.com',993)
mail_obj.login('ckfg0779@163.com','ckfg0779')
mail_obj.select('INBOX')
typ,data=mail_obj.search(None, 'ALL')
for num in data[0].split():
    try:
        typ, data = mail_obj.fetch(num,'(RFC822)')
        msg = email.message_from_string(data[0][1].decode('utf-8'))
        count=count+1
        parse_email(msg,count)
        
    except Exception as e:
        print("get a msg error:",e)
print('ok')
mail_obj.logout()
#mail_obj.close()

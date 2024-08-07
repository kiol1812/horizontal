import os
import smtplib
from dotenv import load_dotenv

load_dotenv()

account = os.getenv("gmail_account")
api_key = os.getenv("gmail_api_key")

smtp = smtplib.SMTP('smtp.gmail.com', 587)
smtp.ehlo()
smtp.starttls()
smtp.login(account, api_key)
from_addr = account
to_addr   = account
msg = "Subject:from py script\nHello World"
status = smtp.sendmail(from_addr, to_addr, msg)

if status == {}:
    print("successful")
else:
    print("failed")

smtp.quit()
